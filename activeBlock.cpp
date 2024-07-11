#include "activeBlock.h"
//#include "utils.h"

ActiveBlock::ActiveBlock(uint x, uint y, BlockType type): m_xPos(x), m_yPos(y), m_blockType(type) {}

bool ActiveBlock::checkInBounds(uint playfieldWidth, uint playfieldHeight) {
    uint x, y;
    for (int i = 0; i < 4; ++i) {
        getBlockPos(&x, &y, i);
        if (x < 0 || x >= playfieldWidth || y < 0 || y >= playfieldHeight) {
            //printf("a\n");
            return false;
        }
    }
    return true;
}

bool ActiveBlock::checkPlayfield(Playfield * playfield) {
    uint x, y;
    for (int i = 0; i < 4; ++i) {
        getBlockPos(&x, &y, i);
        if (playfield->blockInPos(x, y)) {
            //printf("b\n");
            return false;
        }
    }
    return true;
}

bool ActiveBlock::moveDown(Playfield * playfield) {
    m_yPos--;
    //printf("yPos: %d\n", m_yPos);
    if (!(checkInBounds(playfield->getWidth(), playfield->getHeight()) && checkPlayfield(playfield))) {
        m_yPos++;
        return false;
    }
    return true;
}

bool ActiveBlock::moveLeft(Playfield * playfield) {
    m_xPos--;
    if (!(checkInBounds(playfield->getWidth(), playfield->getHeight()) && checkPlayfield(playfield))) {
        m_xPos++;
        return false;
    }
    return true;
}

bool ActiveBlock::moveRight(Playfield * playfield) {
    m_xPos++;
    if (!(checkInBounds(playfield->getWidth(), playfield->getHeight()) && checkPlayfield(playfield))) {
        m_xPos--;
        return false;
    }
    return true;
}

bool ActiveBlock::rotate(Playfield * playfield) {
    BlockType originalBlockType = m_blockType;
    int bt = (int) m_blockType;
    bt++;
    if (bt % 4 == 0) {
        bt -= 4;
    }
    m_blockType = (BlockType) bt;
    if (!(checkInBounds(playfield->getWidth(), playfield->getHeight()) && checkPlayfield(playfield))) {
        m_blockType = originalBlockType;
        return false;
    }
    return true;
}

void ActiveBlock::render(GameRenderer * gameRenderer) {
    uint x, y;
    for (int i = 0; i < 4; ++i) {
        getBlockPos(&x, &y, i);
        //printf("x: %d, y: %d\n", x, y);
        gameRenderer->renderBlock(x, y, "block");
    }
}

void ActiveBlock::setBlockType(BlockType type) {
    m_blockType = type;
}

void ActiveBlock::resetPos(uint x, uint y, Playfield * playfield) {
    m_xPos = x;
    m_yPos = y;
    for (int i = 0; i < 2; ++i) {
        if (!(checkInBounds(playfield->getWidth(), playfield->getHeight()))) {
            m_yPos --;
        }
    }
}

BlockType ActiveBlock::getBlockType() {
    return m_blockType;
}

void ActiveBlock::getBlockPos(uint* x, uint* y, int i) {
    *x = m_xPos + blockForms.at((int)m_blockType).blocks.at(i).m_x;
    *y = m_yPos + blockForms.at((int)m_blockType).blocks.at(i).m_y;
    //printf("x: %d, y: %d\n", *x, *y);
}
