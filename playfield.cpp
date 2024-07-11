#include "playfield.h"
#include "utils.h"

Playfield::Playfield(const uint w, const uint h) {
    m_width = w;
    m_height = h;
    for (uint i = 0; i < w * h; ++i) {
        m_blocks.push_back(false);
    }
}

uint Playfield::getWidth() {
    return m_width;
}

uint Playfield::getHeight() {
    return m_height;
}

bool Playfield::blockInPos(const uint w, const uint h) {
    return m_blocks.at(utils::posToIndex(w, h, m_width));
}

void Playfield::render(GameRenderer * gameRenderer) {
    uint x, y;
    for (int i = 0; i < m_blocks.size(); ++i) {
        if (m_blocks.at(i)) {
            utils::indexToPos(i, &x, &y, m_width);
            gameRenderer->renderBlock(x, y, "block");
        }
    }
}

void Playfield::setBlock(const uint w, const uint h, const bool state) {
    printf("%u\n", utils::posToIndex(w, h, m_width));
    m_blocks.at(utils::posToIndex(w, h, m_width)) = state;
}

int Playfield::clearRows() {
    int rowsCleared = 0;
    for (int i = 0; i < m_height; ++i) {
        bool r = true;
        for (int j = 0; j < m_width; ++j) {
            r &= m_blocks.at(utils::posToIndex(j, i, m_width));
        }
        if (r) {
            rowsCleared++;
            for (int j = i; j < m_height - 1; ++j) {
                copyRowAbove(j);
            }
            for (int j = 0; j < m_width; ++j) {
                m_blocks.at(utils::posToIndex(j, m_height - 1, m_width)) = false;
            }
            i--;
        }
    }
    return rowsCleared;
}

void Playfield::copyRowAbove(uint row) {
    for (int i = 0; i < m_width; ++i) {
        m_blocks.at(utils::posToIndex(i, row, m_width)) = m_blocks.at(utils::posToIndex(i, row + 1, m_width));
    }
}
