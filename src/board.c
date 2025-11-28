#include "board.h"


void init_board(Board *board){
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            board->board_places[row][col].in_game = 0;
            board->board_places[row][col].selected = 0;
            board->board_places[row][col].is_attacked = 0;
        }
    }
    board->board_places[0][0] = (Piece){0, 1, 0, 0, WHITE, ROOK, 0, 0, 0};
    board->board_places[0][1] = (Piece){0, 1, 0, 1, WHITE, KNIGHT, 0, 0, 1};
    board->board_places[0][2] = (Piece){0, 1, 0, 2, WHITE, BISHOP, 0, 0, 2};
    board->board_places[0][3] = (Piece){0, 1, 0, 3, WHITE, QUEEN, 0, 0, 3};
    board->board_places[0][4] = (Piece){0, 1, 0, 4, WHITE, KING, 0, 0, 4};
    board->board_places[0][5] = (Piece){0, 1, 0, 5, WHITE, BISHOP, 0, 0, 5};
    board->board_places[0][6] = (Piece){0, 1, 0, 6, WHITE, KNIGHT, 0, 0, 6};
    board->board_places[0][7] = (Piece){0, 1, 0, 7, WHITE, ROOK, 0, 0, 7};
    for (int col = 0; col < 8; col++) {
        board->board_places[1][col] = (Piece){0, 1, 1, col, WHITE, PAWN, 0, 0, 8 + col};
    }
    board->board_places[7][0] = (Piece){0, 1, 7, 0, BLACK, ROOK, 0, 0, 16};
    board->board_places[7][1] = (Piece){0, 1, 7, 1, BLACK, KNIGHT, 0, 0, 17};
    board->board_places[7][2] = (Piece){0, 1, 7, 2, BLACK, BISHOP, 0, 0, 18};
    board->board_places[7][3] = (Piece){0, 1, 7, 3, BLACK, QUEEN, 0, 0, 19};
    board->board_places[7][4] = (Piece){0, 1, 7, 4, BLACK, KING, 0, 0, 20};
    board->board_places[7][5] = (Piece){0, 1, 7, 5, BLACK, BISHOP, 0, 0, 21};
    board->board_places[7][6] = (Piece){0, 1, 7, 6, BLACK, KNIGHT, 0, 0, 22};
    board->board_places[7][7] = (Piece){0, 1, 7, 7, BLACK, ROOK, 0, 0, 23};
    for (int col = 0; col < 8; col++) {
        board->board_places[6][col] = (Piece){0, 1, 6, col, BLACK, PAWN, 0, 0, 24 + col};
    }

    board->players[WHITE].color = WHITE;
    board->players[WHITE].is_in_check = 0;
    board->players[WHITE].can_castle_kingside = 1;
    board->players[WHITE].can_castle_queenside = 1;
    board->players[WHITE].total_pieces = 16;
    board->players[WHITE].total_captured = 0;
    for (int i = 0; i < 16; i++) {
        board->players[WHITE].pieces[i] = board->board_places[ (i < 8) ? 1 : 0 ][ i % 8 ];
    }

    board->players[BLACK].color = BLACK;
    board->players[BLACK].is_in_check = 0;
    board->players[BLACK].can_castle_kingside = 1;
    board->players[BLACK].can_castle_queenside = 1;
    board->players[BLACK].total_pieces = 16;
    board->players[BLACK].total_captured = 0;
    for (int i = 0; i < 16; i++) {
        board->players[BLACK].pieces[i] = board->board_places[ (i < 8) ? 6 : 7 ][ i % 8 ];
    }
    board->current_turn = WHITE;
    board->move_count = 0;
    board->selected_piece = NULL;
    board->en_passant_row = -1;
    board->en_passant_col = -1;
    board->halfmove_clock = 0;
    board->fullmove_number = 1;
    board->is_checkmate = 0;
    board->is_stalemate = 0;
    board->is_draw = 0;
}