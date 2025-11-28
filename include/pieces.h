#ifndef PIECES_H
#define PIECES_H

typedef enum { WHITE, BLACK } Color;
typedef enum { PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING } Type;

// الحركة
typedef struct {
    int row ;
    int col ;
} Move;

// قائمة الحركات
typedef struct {
    Move moves[27];
    int count;
} MoveList;
typedef struct {
    int selected;
    int in_game;
    int row, col;
    Color color;
    Type piece_type;
    int has_moved;
    int is_attacked;
    int id;
    int captured;
}Piece;

int move_within_bounds(int row, int col);
MoveList pawn_moves(int row, int col, Color color);
MoveList rook_moves(int row, int col, Color color);
MoveList knight_moves(int row, int col, Color color);
MoveList bishop_moves(int row, int col, Color color);
MoveList queen_moves(int row, int col, Color color);
MoveList king_moves(int row, int col, Color color);

#endif
