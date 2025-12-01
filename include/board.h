#ifndef BOARD_H
#define BOARD_H
#include "pieces.h"
#include "game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

typedef struct {
    Piece board_places[8][8];      
    Player players[2]; 
    Color current_turn;
    SDL_Rect chessboard[8][8];
    Move last_move;
    int move_count;
    Piece *selected_piece;
    int en_passant_row;        
    int en_passant_col;       
    int halfmove_clock;         
    int fullmove_number;
    int is_checkmate;
    int is_stalemate;
    int is_draw;
} Board;


void init_board(Board *board);
int check_in_bounds(int x, int y);
void show_possible_moves(Board *board, MoveList moves, SDL_Renderer *ren);
void move_piece(Board Board[], int from_row, int from_col, int to_row, int to_col , int move_count , Mix_Chunk *sound);
MoveList get_possible_moves(Board *board, int row, int col);
int is_in_check(Board *board, Color color);
int is_checkmate(Board *board, Color color);
int is_stalemate(Board *board, Color color);
int get_total_possible_moves(Board *board, Color color);
int is_file_found(const char *filename);
char piece_decoder(Type type , Color color);
void board_to_fen(Board *board, char *fen);
int save_file(char *fen);

#endif