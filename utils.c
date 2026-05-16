#include "utils.h"

char* get_path(char path[MAX_PATH_LENGTH], const char* dir, const char* name, const char* extension) {
    path[0] = '\0';
    strlcat(path, dir, MAX_PATH_LENGTH);
    strlcat(path, name, MAX_PATH_LENGTH);
    strlcat(path, extension, MAX_PATH_LENGTH);
    return path;
}

char* get_file_name(char out[MAX_STR_LENGTH], const char* path) {
    const char* filename = strrchr(path, '/');
    filename = filename == NULL ? path : filename + 1;

    const char* dot = strrchr(filename, '.');

    size_t len = dot == NULL ? strlen(filename) : (size_t)(dot - filename);
    if (len >= MAX_STR_LENGTH) len = MAX_STR_LENGTH - 1;

    memcpy(out, filename, len);
    out[len] = '\0';

    return out;
}


int get_spiral_index(int x, int y) {
    int index = 0;
    if(y*y >= x*x) {
        index = 4 * y * y + y - x;
        if(- y < x)
            index = index + 2 * (y + x);
    } else {
        index = 4 *x*x + y - x;
        if(- y < x)
            index = index - 2 * (y + x);
    }

    return index;
}