#pragma once

namespace utils {

static unsigned int posToIndex(const unsigned int w, const unsigned int h, const unsigned int width) {
    return (h * width) + w;
}

static void indexToPos(const unsigned int index, unsigned int * w, unsigned int * h, const unsigned int width) {
    *h = index / width;
    *w = index % width;
}

}
