#include "pieces.h"

void parse_move_set(const char* filename, MoveSet* move_set) {
    move_set->count = 0;

    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "[ERROR] Failed to open 'MoveSet' file [%s]\n", filename);
        exit(EXIT_FAILURE);
    }
    
    char* line = NULL;
    size_t line_length;
    int x, y;
    Offset offset;
    while (getline(&line, &line_length, fp) != -1) {
        sscanf(line, "%d %d\n", &x, &y);
        offset = (Offset){ x, y };
        da_append(move_set, offset);
    }
    fclose(fp);
}

void parse_piece_list(const char* setup_path, const char* move_dir, PieceList* piece_list) {
    piece_list->count = 0;

    FILE* fp = fopen(setup_path, "r");
    if (fp == NULL) {
        fprintf(stderr, "[ERROR] Failed to open 'PieceList' file [%s]\n", setup_path);
        exit(EXIT_FAILURE);
    }
    
    char path[MAX_PATH_LENGTH];
    char name[MAX_PIECE_NAME_LENGTH];
    uint8_t r, g, b;
    
    char* line = NULL;
    size_t line_length;
    while (getline(&line, &line_length, fp) != -1) {
        sscanf(line, "%s %hhu %hhu %hhu\n", name, &r, &g, &b);
        
        MoveSet move_set = {0};
        parse_move_set(get_path(path, move_dir, name, ".txt"), &move_set);
        
        Piece piece = {
            .moves = move_set,
            .color = (Color){ r, g, b },
            .index = 0,
        };
        da_append(piece_list, piece);
    }
    fclose(fp);
}
