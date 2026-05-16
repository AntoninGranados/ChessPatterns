#pragma once

#include <stdlib.h>
#include <string.h>

#define MAX_STR_LENGTH 256
#define MAX_PATH_LENGTH MAX_STR_LENGTH
#define MAX_PIECE_NAME_LENGTH MAX_STR_LENGTH

char* get_path(char path[MAX_PATH_LENGTH], const char* dir, const char* name, const char* extension);
char* get_file_name(char out[MAX_STR_LENGTH], const char* path);

typedef struct {
    uint8_t r, g, b;
} Color;

int get_spiral_index(int x, int y);
