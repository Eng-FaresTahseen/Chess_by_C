#ifndef BOARD_H
#define BOARD_H
#include "pieces.h"
#include "game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct {
    Piece board_places[8][8];// مصفوفة تمثل أماكن القطع على اللوح
    Player players[2]; // معلومات عن اللاعبين
    Color current_turn;
    SDL_Rect chessboard[8][8];
    
    // معلومات اللعبة الحالية
    Move last_move;
    int move_count;
    Piece *selected_piece;
    
    // ✅ قواعد الشطرنج (خاصة باللعبة كلها)
    int en_passant_row;      // -1 = مفيش en passant متاح
    int en_passant_col;      // -1 = مفيش en passant متاح
    int halfmove_clock;      // للقاعدة الـ50 حركة
    int fullmove_number;     // رقم الحركة الكامل
    
    // حالة اللعبة
    int is_checkmate;        // انتهت اللعبة (كش مات)؟
    int is_stalemate;        // تعادل (stalemate)؟
    int is_draw;             // تعادل (50 حركة أو تكرار)؟
} Board;

// الدوال الأساسية
void init_board(Board *board);
int check_in_bounds(int x, int y);
void show_possible_moves(Board *board, MoveList moves, SDL_Renderer *ren);
int is_valid_move(Board *board, int from_row, int from_col, int to_row, int to_col);
void move_piece(Board *board, int from_row, int from_col, int to_row, int to_col);
MoveList get_possible_moves(Board *board, int row, int col);
int is_in_check(Board *board, Color color);
int is_checkmate(Board *board, Color color);
int is_stalemate(Board *board, Color color);
int get_total_possible_moves(Board *board, Color color);

#endif