#include "board.h"

void init_board(Board* board, size_t width) {
    board->width = width;
    board->indexing = calloc(width*width, sizeof(Offset));
    board->data = calloc(width*width, sizeof(Cell));

    for (size_t y = 0; y < width; y++) {
        for (size_t x = 0; x < width; x++) {
            size_t i = x + y*width;
            board->data[i].occupied_by = -1;
            board->indexing[get_spiral_index(x - width/2, y-width/2)] = (Offset){
                .dx = x, .dy = y
            };
        }
    }
}

void free_board(Board* board) {
    free(board->indexing);
    free(board->data);
}
