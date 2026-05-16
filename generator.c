#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "thirdparties/stb_image_write.h"

#define FLAG_IMPLEMENTATION
#include "thirdparties/flag.h"

#include "da.h"
#include "pieces.h"
#include "utils.h"
#include "board.h"

void add_piece_to_board(Board* board, PieceList* piece_list, int piece_id, size_t x, size_t y) {
    board->data[x + y*board->width].occupied_by = piece_id;
    for (size_t k = 0; k < piece_list->items[piece_id].moves.count; k++) {
        size_t i = x + piece_list->items[piece_id].moves.items[k].dx;
        size_t j = y + piece_list->items[piece_id].moves.items[k].dy;
        if (i < 0 || i >= board->width) continue;
        if (j < 0 || j >= board->width) continue;
        
        board->data[i + j*board->width].seen |= 0b1 << piece_id;
    }
}

void fill_board(Board* board, PieceList* piece_list) {
    int finished = piece_list->count;
    int current_class = 0;
    while (finished > 0) {
        while (piece_list->items[current_class].index < board->width * board->width) {
            Offset cell = board->indexing[piece_list->items[current_class].index];
            size_t i = cell.dx + cell.dy * board->width;
            piece_list->items[current_class].index++;
            if (piece_list->items[current_class].index >= board->width * board->width) {
                finished--;
            }
            
            if (board->data[i].occupied_by >= 0) continue;
            int current_mask = 0b1 << current_class;
            if ((board->data[i].seen & (~current_mask)) != 0) continue;
            
            add_piece_to_board(board, piece_list, current_class, cell.dx, cell.dy);
            break;
        }
        
        current_class = (current_class + 1) % piece_list->count;
    }
}

void render_to_buffer(Color *buffer, Board* board, PieceList* piece_list) {
    for (size_t i = 0; i < board->width*board->width; i++) {
        if (board->data[i].occupied_by < 0) {
            buffer[i] = (Color){ 255, 255, 255 };
        } else {
            buffer[i] = piece_list->items[board->data[i].occupied_by].color;
        }
    }
}

void usage(FILE *stream) {
    fprintf(stream, "OPTIONS:\n");
    flag_print_options(stream);
}

int main(int argc, char** argv) {
    bool *help = flag_bool("help", false, "Print this help to stdout and exit with 0");
    size_t *width = flag_size("width", 255, "Width of the spiral");
    char **setup_path = flag_str("setup", "", "Path to the setup file");
    char **move_dir = flag_str("move-dir", "./setup/moves/", "Path to moves directory");
    char *output_path[MAX_PATH_LENGTH];
    flag_str_var(output_path, "out", "auto", "Path to the output image or auto");
    
    if (!flag_parse(argc, argv)) {
        usage(stderr);
        flag_print_error(stderr);
        exit(1);
    }
    
    argc = flag_rest_argc();
    argv = flag_rest_argv();

    if (*help) {
        usage(stdout);
        exit(0);
    }

    if (strcmp(*setup_path, "") == 0) {
        fprintf(stderr, "[ERROR] A setup path should be provided (see -help)\n");
        exit(1);
    }
    
    if (strcmp(*output_path, "auto") == 0) {
        char output_path_buffer[MAX_PATH_LENGTH];
        char setup_name[MAX_STR_LENGTH];
        get_file_name(setup_name, *setup_path);
        *output_path = get_path(output_path_buffer, "./out/", setup_name, ".png");
    }
    
    Board board = {0};
    PieceList piece_list = {0};
    init_board(&board, *width);
    parse_piece_list(*setup_path, *move_dir, &piece_list);
    fill_board(&board, &piece_list);
    
    Color* buffer = calloc(board.width*board.width, sizeof(Color));
    render_to_buffer(buffer, &board, &piece_list);
    if(!stbi_write_png(*output_path, board.width, board.width, 3, buffer, sizeof(Color) * board.width)) {
        fprintf(stderr, "[ERROR] Failed to write image");
        return 1;
    }
    printf("Saved image to [%s]\n", *output_path);

    free(buffer);
    free_board(&board);
    return 0;
}