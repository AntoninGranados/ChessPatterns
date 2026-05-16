#pragma once

#include <stdlib.h>
#include <stdio.h>

#include "da.h"
#include "utils.h"

typedef struct {
    int dx, dy;
} Offset;

typedef struct {
    size_t count;
    size_t capacity;
    Offset* items;
} MoveSet;

typedef struct {
    MoveSet moves;
    Color color;
    size_t index;  // @note used to save the position in the spiral
} Piece;

typedef struct {
    size_t count;
    size_t capacity;
    Piece* items;
} PieceList;

void parse_move_set(const char* filename, MoveSet* move_set);
void parse_piece_list(const char* setup_path, const char* move_dir, PieceList* piece_list);