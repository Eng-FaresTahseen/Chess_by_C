#include "pieces.h"
#include <stddef.h> //--> NULL 
// construction:
//extern pieces*BoardGrid[8][8];

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
    /*
    int direction=(color==WHITE)? -1:1; // white goes up & black goes down on rows 
    int start_row=(color==WHITE)? 6:1; // bec the array is from 0->7 the index start from top (black first)
    int next_row=row+direction;
    int nextNextrow=row+(2*direction);
    if(!move_within_bounds(nextRow,col)){
        return move_list;
    }

    int targetCol=col;
    if (BoardGrid[next_row][target_col] == NULL) {
        list.moves[list.count].row = next_row;
        list.moves[list.count].col = target_col;
        list.count++;

        if (row == start_row) {
            int next_next_row = row + 2 * direction;
            if (BoardGrid[next_next_row][target_col] == NULL) {
                list.moves[list.count].row = next_next_row;
                list.moves[list.count].col = target_col;
                list.count++;
            }
        }
    }

    for (int dc = -1; dc <= 1; dc += 2) {
        target_col = col + dc;
        
        if (move_within_bounds(next_row, target_col)) {
            Piece* target_piece = BoardGrid[next_row][target_col];
            
            if (target_piece != NULL && target_piece->color != current_color) {
                list.moves[list.count].row = next_row;
                list.moves[list.count].col = target_col;
                list.count++;
            }
        }
    }
    */
    //still thinking
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
    /*
    Color current_color = color;
    
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; 

    for (int i = 0; i < 4; i++) {
        int dr = directions[i][0]; 
        int dc = directions[i][1]; 
        
        for (int step = 1; step < 8; step++) {
            int target_row = row + dr * step;
            int target_col = col + dc * step;

            if (!move_within_bounds(target_row, target_col)) {
                break; 
            }

            Piece* target_piece = BoardGrid[target_row][target_col];

            if (target_piece == NULL) {
                move_list.moves[move_list.count].row = target_row;
                move_list.moves[move_list.count].col = target_col;
                move_list.count++;
            } else {
                if (target_piece->color != current_color) {
                    move_list.moves[move_list.count].row = target_row;
                    move_list.moves[move_list.count].col = target_col;
                    move_list.count++;
                }
                
                break; 
            }
        }
    }
    */
    return move_list;
}


// bishop moves
MoveList bishop_moves(int row, int col, Color color) {
    MoveList move_list;
    move_list.count = 0;
    // Implementation of bishop move generation logic goes here
/*
    Color current_color = color;    
    // for the 4 directions:

    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    for (int i = 0; i < 4; i++) {
        int dr = directions[i][0]; 
        int dc = directions[i][1]; 
        
        for (int step = 1; step < 8; step++) {
            int target_row = row + dr * step;
            int target_col = col + dc * step;

            if (!move_within_bounds(target_row, target_col)) {
                break; 
            }
         // بص بقا ده ال construction 
            Piece* target_piece = BoardGrid[target_row][target_col];

            if (target_piece == NULL) {
                //free square
                move_list.moves[move_list.count].row = target_row;
                move_list.moves[move_list.count].col = target_col;
                move_list.count++;
            } else {
                //therse is a piece in front:
                if (target_piece->color != current_color) {
                    //to eat:
                    move_list.moves[move_list.count].row = target_row;
                    move_list.moves[move_list.count].col = target_col;
                    move_list.count++;
                }
                
                // to stop if there is some piece in front diagonaly
                break; 
            }
        }
    }

    */
    return move_list;
}



// queen moves
MoveList queen_moves(int row, int col, Color color) {
    MoveList move_list;
    move_list.count = 0;
    // Implementation of queen move generation logic goes here
    /*
    Color current_color = color;
    // to define the 8 direction:

    int directions[8][2] = {
        {0, 1}, {0, -1}, {1, 0}, {-1, 0}, 
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
    }; 

    for (int i = 0; i < 8; i++) {
        int dr = directions[i][0]; // change row
        int dc = directions[i][1]; // change col
        
        // a loop to continue to move in a certain direction:
        for (int step = 1; step < 8; step++) {
            int target_row = row + dr * step;
            int target_col = col + dc * step;

            // check boundaries: 
            if (!move_within_bounds(target_row, target_col)) {
                break;
            }

            // same construction:
            Piece* target_piece = BoardGrid[target_row][target_col];

            if (target_piece == NULL) {
               // if free square:
                move_list.moves[move_list.count].row = target_row;
                move_list.moves[move_list.count].col = target_col;
                move_list.count++;
            } else {
                // if square has piece:
                if (target_piece->color != current_color) {
                    // to eat and stop at the eaten piece:
                move_list.moves[move_list.count].row = target_row;
                    move_list.moves[move_list.count].col = target_col;
                    move_list.count++;
                }
                
                break; 
            }
        }
    }
    */
    return move_list;
}


// king moves
MoveList king_moves(int row, int col, Color color) {
    MoveList move_list;
    move_list.count = 0;
    // Implementation of king move generation logic goes here
    /*
    Color current_color = color;
    
    int directions[8][2] = {
        {0, 1}, {0, -1}, {1, 0}, {-1, 0}, 
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
    }; 

    for (int i = 0; i < 8; i++) {
        int dr = directions[i][0]; 
        int dc = directions[i][1]; 
        
        int target_row = row + dr;
        int target_col = col + dc;

        if (!move_within_bounds(target_row, target_col)) {
            continue;
        }

        Piece* target_piece = BoardGrid[target_row][target_col];

        if (target_piece == NULL) {
            move_list.moves[move_list.count].row = target_row;
            move_list.moves[move_list.count].col = target_col;
            move_list.count++;
        } else {
            if (target_piece->color != current_color) {
                move_list.moves[move_list.count].row = target_row;
                move_list.moves[move_list.count].col = target_col;
                move_list.count++;
            }
        }
    }
    */
    return move_list;
}


