#include "board.h"

// Board initialization
void init_board(Board *board){
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            board->board_places[row][col].in_game = 0;
            board->board_places[row][col].selected = 0;
            board->board_places[row][col].row = row;
            board->board_places[row][col].col = col;
            board->board_places[row][col].captured = 0;
            board->board_places[row][col].has_moved = 0;
            board->board_places[row][col].is_attacked = 0;
        }
    }
    // Place Black pieces at the top (rows 0 and 1)
    board->board_places[0][0] = (Piece){0, 1, 0, 0, BLACK, ROOK, 0, 0, 0};
    board->board_places[0][1] = (Piece){0, 1, 0, 1, BLACK, KNIGHT, 0, 0, 1};
    board->board_places[0][2] = (Piece){0, 1, 0, 2, BLACK, BISHOP, 0, 0, 2};
    board->board_places[0][3] = (Piece){0, 1, 0, 3, BLACK, QUEEN, 0, 0, 3};
    board->board_places[0][4] = (Piece){0, 1, 0, 4, BLACK, KING, 0, 0, 4};
    board->board_places[0][5] = (Piece){0, 1, 0, 5, BLACK, BISHOP, 0, 0, 5};
    board->board_places[0][6] = (Piece){0, 1, 0, 6, BLACK, KNIGHT, 0, 0, 6};
    board->board_places[0][7] = (Piece){0, 1, 0, 7, BLACK, ROOK, 0, 0, 7};
    for (int col = 0; col < 8; col++) {
        board->board_places[1][col] = (Piece){0, 1, 1, col, BLACK, PAWN, 0, 0, 8 + col};
    }

    // Place White pieces at the bottom (rows 7 and 6)
    board->board_places[7][0] = (Piece){0, 1, 7, 0, WHITE, ROOK, 0, 0, 16};
    board->board_places[7][1] = (Piece){0, 1, 7, 1, WHITE, KNIGHT, 0, 0, 17};
    board->board_places[7][2] = (Piece){0, 1, 7, 2, WHITE, BISHOP, 0, 0, 18};
    board->board_places[7][3] = (Piece){0, 1, 7, 3, WHITE, QUEEN, 0, 0, 19};
    board->board_places[7][4] = (Piece){0, 1, 7, 4, WHITE, KING, 0, 0, 20};
    board->board_places[7][5] = (Piece){0, 1, 7, 5, WHITE, BISHOP, 0, 0, 21};
    board->board_places[7][6] = (Piece){0, 1, 7, 6, WHITE, KNIGHT, 0, 0, 22};
    board->board_places[7][7] = (Piece){0, 1, 7, 7, WHITE, ROOK, 0, 0, 23};
    for (int col = 0; col < 8; col++) {
        board->board_places[6][col] = (Piece){0, 1, 6, col, WHITE, PAWN, 0, 0, 24 + col};
    }

    board->players[WHITE].color = WHITE;
    board->players[WHITE].is_in_check = 0;
    board->players[WHITE].can_castle_kingside = 1;
    board->players[WHITE].can_castle_queenside = 1;
    board->players[WHITE].total_pieces = 16;
    board->players[WHITE].total_captured = 0;
    for (int i = 0; i < 16; i++) {
        board->players[WHITE].pieces[i] = board->board_places[ (i < 8) ? 6 : 7 ][ i % 8 ];
    }

    board->players[BLACK].color = BLACK;
    board->players[BLACK].is_in_check = 0;
    board->players[BLACK].can_castle_kingside = 1;
    board->players[BLACK].can_castle_queenside = 1;
    board->players[BLACK].total_pieces = 16;
    board->players[BLACK].total_captured = 0;
    for (int i = 0; i < 16; i++) {
        board->players[BLACK].pieces[i] = board->board_places[ (i < 8) ? 1 : 0 ][ i % 8 ];
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

// Check if coordinates are within board bounds
int check_in_bounds(int x, int y) {
    // Board origin is at (80,125). Each cell is 80px and there are 8 cells.
    // Valid x: [80, 80 + 8*80) -> [80, 720)
    // Valid y: [125, 125 + 8*80) -> [125, 765)
    return (x >= 80 && x < 80 + 8*80 && y >= 125 && y < 125 + 8*80);
}

// Show possible moves on the board
void show_possible_moves(Board *board, MoveList moves, SDL_Renderer *ren) {
    SDL_SetRenderDrawColor(ren, 0, 255, 0, 100);
    for (int i = 0; i < moves.count; i++) {
        int row = moves.moves[i].row;
        int col = moves.moves[i].col;
        // guard against out-of-range moves coming from move generation
        if (row < 0 || row >= 8 || col < 0 || col >= 8) continue;
        SDL_Rect highlight_rect = board->chessboard[row][col];
        SDL_RenderFillRect(ren, &highlight_rect);
    }}

// Get possible moves for a piece
MoveList get_possible_moves(Board *board, int row, int col) {
    MoveList move_list;
    move_list.count = 0;
    // Implementation of move generation logic goes here
    if (board->board_places[row][col].piece_type == PAWN) {
        move_list = pawn_moves(row, col, board->board_places[row][col].color);
    } else if (board->board_places[row][col].piece_type == ROOK) {
        move_list = rook_moves(row, col, board->board_places[row][col].color);
    } else if (board->board_places[row][col].piece_type == KNIGHT) {
        move_list = knight_moves(row, col, board->board_places[row][col].color);
    } else if (board->board_places[row][col].piece_type == BISHOP) {
        move_list = bishop_moves(row, col, board->board_places[row][col].color);
    } else if (board->board_places[row][col].piece_type == QUEEN) {
        move_list = queen_moves(row, col, board->board_places[row][col].color);
    } else if (board->board_places[row][col].piece_type == KING) {
        move_list = king_moves(row, col, board->board_places[row][col].color);
    }
    return move_list;}

// move_piece implementation would go here
void move_piece(Board board[], int from_row, int from_col, int to_row, int to_col, int move_count , Mix_Chunk *sound) {
    if (sound != NULL) {
        Mix_PlayChannel(-1, sound, 0);
    } else {
        printf("Failed to load sound: %s\n", Mix_GetError());
    }
    board[move_count + 1] = board[move_count];
    int dest_was_occupied = board[move_count].board_places[to_row][to_col].in_game;
    Piece dest_piece = board[move_count].board_places[to_row][to_col];
    Piece moving_piece = board[move_count].board_places[from_row][from_col];
    if (!moving_piece.in_game) {
        return;
    }
    if (dest_was_occupied) {
        Color captured_color = dest_piece.color;
        Color capturer_color = moving_piece.color;
        int captured_index = board[move_count + 1].players[capturer_color].total_captured;
        board[move_count + 1].players[capturer_color].captured_piece[captured_index] = dest_piece;
        board[move_count + 1].players[capturer_color].total_captured += 1;
        board[move_count + 1].players[captured_color].total_pieces -= 1;
        board[move_count + 1].board_places[to_row][to_col].captured = 1;}
    board[move_count + 1].board_places[to_row][to_col] = moving_piece;
    board[move_count + 1].board_places[to_row][to_col].row = to_row;
    board[move_count + 1].board_places[to_row][to_col].col = to_col;
    board[move_count + 1].board_places[to_row][to_col].has_moved = 1;
    board[move_count + 1].board_places[to_row][to_col].in_game = 1;
    board[move_count + 1].board_places[to_row][to_col].selected = 0;
    board[move_count + 1].board_places[from_row][from_col].in_game = 0;
    board[move_count + 1].board_places[from_row][from_col].selected = 0;
    board[move_count + 1].last_move = (Move){from_row, from_col};
    board[move_count + 1].move_count = move_count + 1;
    board[move_count + 1].current_turn = (board[move_count].current_turn == WHITE) ? BLACK : WHITE;

    if (dest_was_occupied || moving_piece.piece_type == PAWN) {
        board[move_count + 1].halfmove_clock = 0;
    } else {
        board[move_count + 1].halfmove_clock = board[move_count].halfmove_clock + 1;
    }
    board[move_count + 1].fullmove_number = board[move_count].fullmove_number + (moving_piece.color == BLACK ? 1 : 0);

    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            board[move_count + 1].chessboard[i][j].x = 80 + j*80;
            board[move_count + 1].chessboard[i][j].y = 125 + i*80;
            board[move_count + 1].chessboard[i][j].w = 80;
            board[move_count + 1].chessboard[i][j].h = 80;
        }
    }
}
