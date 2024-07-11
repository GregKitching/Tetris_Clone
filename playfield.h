#pragma once

#include "gameRenderer.h"

#include <vector>

class Playfield {
    public:
        Playfield(const uint w, const uint h);
        uint getWidth();
        uint getHeight();
        bool blockInPos(const uint w, const uint h);
        void render(GameRenderer * gameRenderer);
        void setBlock(const uint w, const uint h, const bool state);
        int clearRows();
    private:
        void copyRowAbove(uint row);
        uint m_width;
        uint m_height;
        std::vector<bool> m_blocks;
};
