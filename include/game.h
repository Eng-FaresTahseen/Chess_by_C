#ifndef GAME_H
#define GAME_H
#include "pieces.h"
typedef struct {
    Color color;
    Piece pieces[16];          
    Piece captured_piece[15];
    int is_in_check;       
    int can_castle_kingside;
    int can_castle_queenside;
    int total_pieces;           
    int total_captured;
    
    // en_passant, halfmove_clock, fullmove_number, total_possible_moves
} Player;

#endif