#pragma once

#include <stdlib.h>

#include "pieces.h"

typedef struct {
    uint64_t seen;  // @note limited to 64 different pieces
    int occupied_by;
} Cell;

typedef struct {
    size_t width;
    Offset* indexing;
    Cell* data;
} Board;

void init_board(Board* board, size_t width);
void free_board(Board* board);
