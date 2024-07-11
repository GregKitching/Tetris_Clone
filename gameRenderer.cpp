#include "gameRenderer.h"

#include <SDL_stdinc.h>
#include <string>

const int screenWidth = 256;
const int screenHeight = 320;

GameRenderer::GameRenderer() {
    m_srcRect.x = 0;
    m_srcRect.y = 0;
    m_srcRect.w = 16;
    m_srcRect.h = 16;
    m_dstRect.x = 0;
    m_dstRect.y = 0;
    m_dstRect.w = 16;
    m_dstRect.h = 16;
}

bool GameRenderer::init() {
    m_window = NULL;
    m_renderer = NULL;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        return false;
    }
    if (TTF_Init() < 0) {
        return false;
    }
    m_font = TTF_OpenFont("/home/greg/projects/tetris/Fonts/OpenSans-Regular.ttf", 16);
    m_window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    if (m_window == NULL) {
        return false;
    }
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (m_renderer == NULL) {
        return false;
    }
    SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    m_textColour.r = 0xff;
    m_textColour.g = 0xff;
    m_textColour.b = 0xff;
    m_textColour.a = 0xff;
    setText("0");
    return true;
}

void GameRenderer::quit() {
    for (auto i = m_sprites.begin(); i != m_sprites.end(); ++i) {
        SDL_DestroyTexture(i->second);
    }
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    TTF_Quit();
    SDL_Quit();
}

void GameRenderer::renderBlock(uint x, uint y, const std::string & texture) {
    m_dstRect.x = x << 4;
    m_dstRect.y = screenHeight - (y << 4) - 16;
    m_dstRect.w = 16;
    m_dstRect.h = 16;
    SDL_RenderCopy(m_renderer, m_sprites[texture], &m_srcRect, &m_dstRect);
}

void GameRenderer::setText(const std::string & text) {
    SDL_Surface * textSurface = TTF_RenderText_Solid(m_font, text.c_str(), m_textColour);
    m_scoreCntr.m_texture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
    m_scoreCntr.m_w = textSurface->w;
    m_scoreCntr.m_h = textSurface->h;
    SDL_FreeSurface(textSurface);
}

void GameRenderer::renderText(uint x, uint y) {
    m_dstRect.x = x;
    m_dstRect.y = screenHeight - y;
    m_dstRect.w = m_scoreCntr.m_w;
    m_dstRect.h = m_scoreCntr.m_h;
    SDL_RenderCopy(m_renderer, m_scoreCntr.m_texture, NULL, &m_dstRect);
}

void GameRenderer::renderStart() {
    SDL_RenderClear(m_renderer);
    m_dstRect.x = 160;
    m_dstRect.y = 0;
    m_dstRect.w = 96;
    m_dstRect.h = 320;
    SDL_SetRenderDrawColor(m_renderer, 0x7f, 0x7f, 0x7f, 0xff);
    SDL_RenderFillRect(m_renderer, &m_dstRect);
    SDL_SetRenderDrawColor(m_renderer, 0xff, 0xff, 0xff, 0xff);
    m_dstRect.w = 16;
    m_dstRect.h = 16;
}

void GameRenderer::renderEnd() {
    SDL_RenderPresent(m_renderer);
}

bool GameRenderer::loadSprite(const std::string & name) {
    SDL_Texture * sprite = NULL;
    std::string fileName = "/home/greg/projects/tetris/Sprites/" + name + ".bmp";
    SDL_Surface * surface = NULL;
    surface = SDL_LoadBMP(fileName.c_str());
    if (surface == NULL) {
        return false;
    }
    sprite = SDL_CreateTextureFromSurface(m_renderer, surface);
    if (sprite == NULL) {
        SDL_FreeSurface(surface);
        return false;
    }
    m_sprites[name] = sprite;
    return true;
}

uint GameRenderer::getNumSprites() {
    return m_sprites.size();
}
