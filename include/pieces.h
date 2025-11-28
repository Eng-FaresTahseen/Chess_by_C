#ifndef PIECES_H
#define PIECES_H

typedef enum { WHITE, BLACK } Color;
typedef enum { PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING } Type;

typedef struct {
    int selected;
    int in_game;
    int row, col;
    Color color;
    Type piece_type;
    int has_moved;
    int is_attacked;
    int id;
}Piece;

#endif
