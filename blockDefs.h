#pragma once

#include <array>

enum BlockType {
    BLOCKTYPE_LONG_R0 = 0,
    BLOCKTYPE_LONG_R1,
    BLOCKTYPE_LONG_R2,
    BLOCKTYPE_LONG_R3,

    BLOCKTYPE_L_R0,
    BLOCKTYPE_L_R1,
    BLOCKTYPE_L_R2,
    BLOCKTYPE_L_R3,

    BLOCKTYPE_L_BKWDS_R0,
    BLOCKTYPE_L_BKWDS_R1,
    BLOCKTYPE_L_BKWDS_R2,
    BLOCKTYPE_L_BKWDS_R3,

    BLOCKTYPE_N_R0,
    BLOCKTYPE_N_R1,
    BLOCKTYPE_N_R2,
    BLOCKTYPE_N_R3,

    BLOCKTYPE_N_BKWDS_R0,
    BLOCKTYPE_N_BKWDS_R1,
    BLOCKTYPE_N_BKWDS_R2,
    BLOCKTYPE_N_BKWDS_R3,

    BLOCKTYPE_T_R0,
    BLOCKTYPE_T_R1,
    BLOCKTYPE_T_R2,
    BLOCKTYPE_T_R3,

    BLOCKTYPE_SQUARE_R0,
    BLOCKTYPE_SQUARE_R1,
    BLOCKTYPE_SQUARE_R2,
    BLOCKTYPE_SQUARE_R3,
};

struct BlockPos {
    int m_x;
    int m_y;
    BlockPos(int x, int y): m_x(x), m_y(y) {}
};

struct BlockForm {
    std::array<BlockPos, 4> blocks;
    BlockForm(BlockPos a, BlockPos b, BlockPos c, BlockPos d): blocks({a, b, c, d}) {}
};

const std::array<BlockForm, 28> blockForms = {
    BlockForm(BlockPos(0, 0), BlockPos(0, 1), BlockPos(0, -1), BlockPos(0, -2)),
    BlockForm(BlockPos(0, 0), BlockPos(1, 0), BlockPos(-1, 0), BlockPos(-2, 0)),
    BlockForm(BlockPos(0, 0), BlockPos(0, 1), BlockPos(0, -1), BlockPos(0, -2)),
    BlockForm(BlockPos(0, 0), BlockPos(1, 0), BlockPos(-1, 0), BlockPos(-2, 0)),

    BlockForm(BlockPos(0, 0), BlockPos(0, 1), BlockPos(0, -1), BlockPos(1, -1)),
    BlockForm(BlockPos(0, 0), BlockPos(1, 0), BlockPos(-1, 0), BlockPos(-1, -1)),
    BlockForm(BlockPos(0, 0), BlockPos(0, 1), BlockPos(0, -1), BlockPos(-1, 1)),
    BlockForm(BlockPos(0, 0), BlockPos(1, 0), BlockPos(-1, 0), BlockPos(1, 1)),

    BlockForm(BlockPos(0, 0), BlockPos(0, 1), BlockPos(0, -1), BlockPos(-1, -1)),
    BlockForm(BlockPos(0, 0), BlockPos(1, 0), BlockPos(-1, 0), BlockPos(-1, 1)),
    BlockForm(BlockPos(0, 0), BlockPos(0, 1), BlockPos(0, -1), BlockPos(1, 1)),
    BlockForm(BlockPos(0, 0), BlockPos(1, 0), BlockPos(-1, 0), BlockPos(1, -1)),

    BlockForm(BlockPos(0, 0), BlockPos(0, -1), BlockPos(1, 0), BlockPos(1, 1)),
    BlockForm(BlockPos(0, 0), BlockPos(-1, 0), BlockPos(0, -1), BlockPos(1, -1)),
    BlockForm(BlockPos(0, 0), BlockPos(0, 1), BlockPos(-1, 0), BlockPos(-1, -1)),
    BlockForm(BlockPos(0, 0), BlockPos(1, 0), BlockPos(0, 1), BlockPos(-1, 1)),

    BlockForm(BlockPos(0, 0), BlockPos(0, -1), BlockPos(-1, 0), BlockPos(-1, 1)),
    BlockForm(BlockPos(0, 0), BlockPos(-1, 0), BlockPos(0, 1), BlockPos(1, 1)),
    BlockForm(BlockPos(0, 0), BlockPos(0, 1), BlockPos(1, 0), BlockPos(1, -1)),
    BlockForm(BlockPos(0, 0), BlockPos(1, 0), BlockPos(0, -1), BlockPos(-1, -1)),

    BlockForm(BlockPos(0, 0), BlockPos(1, 0), BlockPos(-1, 0), BlockPos(0, -1)),
    BlockForm(BlockPos(0, 0), BlockPos(-1, 0), BlockPos(0, 1), BlockPos(0, -1)),
    BlockForm(BlockPos(0, 0), BlockPos(1, 0), BlockPos(-1, 0), BlockPos(0, 1)),
    BlockForm(BlockPos(0, 0), BlockPos(1, 0), BlockPos(0, 1), BlockPos(0, -1)),

    BlockForm(BlockPos(0, 0), BlockPos(-1, 0), BlockPos(0, -1), BlockPos(-1, -1)),
    BlockForm(BlockPos(0, 0), BlockPos(-1, 0), BlockPos(0, -1), BlockPos(-1, -1)),
    BlockForm(BlockPos(0, 0), BlockPos(-1, 0), BlockPos(0, -1), BlockPos(-1, -1)),
    BlockForm(BlockPos(0, 0), BlockPos(-1, 0), BlockPos(0, -1), BlockPos(-1, -1))
};
