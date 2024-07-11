#include "gameRenderer.h"
#include "playfield.h"
#include "activeBlock.h"
#include "blockDefs.h"

#include <chrono>
#include <ratio>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <unistd.h>

static bool s_running, s_rendering;

static int s_moveCntrVal = 64;

static const int s_moveCntrValFast = 4;

static int s_moveCntr = 0;

SDL_Event e;

GameRenderer gameRenderer;

Playfield playfield(10, 20);
ActiveBlock activeBlock(0, 0, BLOCKTYPE_LONG_R0);
ActiveBlock nextBlock(13, 17, BLOCKTYPE_LONG_R0);

bool upFlag = false;
bool downFlag = false;
bool leftFlag = false;
bool rightFlag = false;
bool uFlag = false;

bool fastDrop = false;

int score = 0;
int linesCleared = 0;

void createNewBlock() {
    activeBlock.setBlockType(nextBlock.getBlockType());
    nextBlock.setBlockType((BlockType)(rand() % 28));
    activeBlock.resetPos(5, 20, &playfield);
}

void debugPlayfield() {
    printf("__________\n");
    for (int y = 19; y >= 0; --y) {
        for (int x = 0; x < 10; ++x) {
            if (playfield.blockInPos(x, y)) {
                printf("*");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void keyFunc() {
    if (s_rendering) {
        while(SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                printf("quit\n");
                s_rendering = false;
            } else if (e.type == SDL_KEYDOWN) {
                switch(e.key.keysym.sym) {
                    case SDLK_UP:
                        upFlag = true;
                        break;
                    case SDLK_DOWN:
                        if (e.key.repeat == 0) {
                            downFlag = true;
                        }
                        break;
                    case SDLK_LEFT:
                        leftFlag = true;
                        break;
                    case SDLK_RIGHT:
                        rightFlag = true;
                        break;
                    case SDLK_u:
                        uFlag = true;
                        break;
                    default:
                        break;
                }
            } else if (e.type == SDL_KEYUP) {
                switch(e.key.keysym.sym) {
                    case SDLK_UP:
                        upFlag = false;
                        break;
                    case SDLK_DOWN:
                        downFlag = false;
                        fastDrop = false;
                        break;
                    case SDLK_LEFT:
                        leftFlag = false;
                        break;
                    case SDLK_RIGHT:
                        rightFlag = false;
                        break;
                    case SDLK_u:
                        uFlag = false;
                        break;
                    default:
                        break;
                }
            }
        }
        s_running = s_rendering;
    }
}

void logicFunc() {
    if (upFlag) {
        activeBlock.rotate(&playfield);
        upFlag = false;
    }
    if (leftFlag && !rightFlag) {
        activeBlock.moveLeft(&playfield);
        leftFlag = false;
    }
    if (rightFlag && !leftFlag) {
        activeBlock.moveRight(&playfield);
        rightFlag = false;
    }
    if (downFlag) {
        fastDrop = true;
        s_moveCntr = s_moveCntrValFast;
        downFlag = false;
    }
    s_moveCntr--;
    if (uFlag) {
        debugPlayfield();
        uFlag = false;
    }
    if (s_moveCntr <= 0) {
        if (!activeBlock.moveDown(&playfield)) {
            uint x, y;
            for (int i = 0; i < 4; ++i) {
                activeBlock.getBlockPos(&x, &y, i);
                playfield.setBlock(x, y, true);
                //printf("x: %u, y: %u\n", x, y);
            }
            int l = playfield.clearRows();
            linesCleared += l;
            s_moveCntrVal = 64 - ((linesCleared / 10) * 4);
            if (s_moveCntrVal < 4) {
                s_moveCntrVal = 4;
            }
            score += 100 * l;
            gameRenderer.setText(std::to_string(score));
            createNewBlock();
            if (!activeBlock.checkPlayfield(&playfield)) {
                printf("Game over\n");
                s_rendering = false;
                s_running = false;
            }
        }
        if (fastDrop) {
            s_moveCntr = s_moveCntrValFast;
        } else {
            s_moveCntr = s_moveCntrVal;
        }
    }
}

void renderFunc() {
    if (s_rendering) {
        gameRenderer.renderStart();
        playfield.render(&gameRenderer);
        activeBlock.render(&gameRenderer);
        nextBlock.render(&gameRenderer);
        gameRenderer.renderText(170, 160);
        gameRenderer.renderEnd();
    }
}

int main(int argc, char **argv) {
    s_running = true;
    s_rendering = true;
    s_moveCntr = s_moveCntrVal;
    srand(time(NULL));
    bool a = gameRenderer.init();
    gameRenderer.loadSprite("block");
    std::chrono::microseconds frameDuration(16666);
    nextBlock.setBlockType((BlockType)(rand() % 28));
    createNewBlock();
    while (s_running) {
        std::chrono::time_point<std::chrono::high_resolution_clock> t1 = std::chrono::high_resolution_clock::now();
        keyFunc();
        logicFunc();
        renderFunc();
        std::chrono::time_point<std::chrono::high_resolution_clock> t2 = std::chrono::high_resolution_clock::now();
        std::chrono::microseconds timeDiff = std::chrono::duration_cast<std::chrono::microseconds>(frameDuration - (t2 - t1));
        int sleepTime = (int)(timeDiff.count());
        if (sleepTime >= 0) {
            usleep(sleepTime);
        }
    }
    gameRenderer.quit();
    return 0;
}
