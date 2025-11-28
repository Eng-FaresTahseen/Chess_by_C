#include "pieces.h"

// move bounds check
int move_within_bounds(int row, int col) {
    return (row >= 0 && row < 8 && col >= 0 && col < 8);
}

// pieces moves

// pawn moves
MoveList pawn_moves(int row, int col, Color color) {
    MoveList move_list;
    move_list.count = 0;
    // Implementation of pawn move generation logic goes here

    return move_list;
}

// knight moves
MoveList knight_moves(int row, int col, Color color) {
    MoveList move_list;
    move_list.count = 0;
    // Implementation of rook move generation logic goes here
    if (color == WHITE) {
        if (move_within_bounds(row - 2, col - 1)) {
            move_list.moves[move_list.count++] = (Move){row - 2, col - 1};
        }
        if (move_within_bounds(row - 2, col + 1)) {
            move_list.moves[move_list.count++] = (Move){row - 2, col + 1};
        }
        if (move_within_bounds(row - 1, col - 2)) {
            move_list.moves[move_list.count++] = (Move){row - 1, col - 2};
        }
        if (move_within_bounds(row - 1, col + 2)) {
            move_list.moves[move_list.count++] = (Move){row - 1, col + 2};
        }
        if (move_within_bounds(row + 1, col - 2)) {
            move_list.moves[move_list.count++] = (Move){row + 1, col - 2};
        }
        if (move_within_bounds(row + 1, col + 2)) {
            move_list.moves[move_list.count++] = (Move){row + 1, col + 2};
        }
        if (move_within_bounds(row + 2, col - 1)) {
            move_list.moves[move_list.count++] = (Move){row + 2, col - 1};
        }
        if (move_within_bounds(row + 2, col + 1)) {
            move_list.moves[move_list.count++] = (Move){row + 2, col + 1};
        }
    } else {
        if (move_within_bounds(row - 2, col - 1)) {
            move_list.moves[move_list.count++] = (Move){row - 2, col - 1};
        }
        if (move_within_bounds(row - 2, col + 1)) {
            move_list.moves[move_list.count++] = (Move){row - 2, col + 1};
        }
        if (move_within_bounds(row - 1, col - 2)) {
            move_list.moves[move_list.count++] = (Move){row - 1, col - 2};
        }
        if (move_within_bounds(row - 1, col + 2)) {
            move_list.moves[move_list.count++] = (Move){row - 1, col + 2};
        }
        if (move_within_bounds(row + 1, col - 2)) {
            move_list.moves[move_list.count++] = (Move){row + 1, col - 2};
        }
        if (move_within_bounds(row + 1, col + 2)) {
            move_list.moves[move_list.count++] = (Move){row + 1, col + 2};
        }
        if (move_within_bounds(row + 2, col - 1)) {
            move_list.moves[move_list.count++] = (Move){row + 2, col - 1};
        }
        if (move_within_bounds(row + 2, col + 1)) {
            move_list.moves[move_list.count++] = (Move){row + 2, col + 1};
        }
    }

    return move_list;
}

// rook moves
MoveList rook_moves(int row, int col, Color color) {
    MoveList move_list;
    move_list.count = 0;
    // Implementation of rook move generation logic goes here

    return move_list;
}


// bishop moves
MoveList bishop_moves(int row, int col, Color color) {
    MoveList move_list;
    move_list.count = 0;
    // Implementation of bishop move generation logic goes here

    return move_list;
}



// queen moves
MoveList queen_moves(int row, int col, Color color) {
    MoveList move_list;
    move_list.count = 0;
    // Implementation of queen move generation logic goes here

    return move_list;
}


// king moves
MoveList king_moves(int row, int col, Color color) {
    MoveList move_list;
    move_list.count = 0;
    // Implementation of king move generation logic goes here

    return move_list;
}


