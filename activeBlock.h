#pragma once

#include "blockDefs.h"
#include "gameRenderer.h"
#include "playfield.h"

class ActiveBlock {
    public:
        ActiveBlock(uint x, uint y, BlockType type);
        bool checkInBounds(uint playfieldWidth, uint playfieldHeight);
        bool checkPlayfield(Playfield * playfield);
        bool moveDown(Playfield * playfield);
        bool moveLeft(Playfield * playfield);
        bool moveRight(Playfield * playfield);
        bool rotate(Playfield * playfield);
        void render(GameRenderer * gameRenderer);
        void setBlockType(BlockType type);
        void resetPos(uint x, uint y, Playfield * playfield);
        void getBlockPos(uint * x, uint * y, int i);
        BlockType getBlockType();
    private:
        uint m_xPos;
        uint m_yPos;
        BlockType m_blockType;
};
