# include "board.h"
# include <stdio.h>
# include <stdlib.h>


int is_file_found(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}

char piece_decoder(Type type , Color color){
    char result ;
    switch (type)
    {
    case PAWN:
        result = 'p';
        break;
    case KNIGHT:
        result = 'n';
        break;
    case BISHOP:
        result = 'b';
        break;
    case ROOK:
        result = 'r';
        break;
    case QUEEN:
        result = 'q';
        break;
    case KING:
        result = 'k';
        break;
    }
    if (color == BLACK){
        return result ;
    } else {
        return ((char)(result - 32));
    }
}

void board_to_fen(Board *board, char *fen) {
    int current_position = 0 ; 
    for (int row = 0 ; row < 8 ; row ++){
        int empty_square = 0;
        for (int col = 0 ; col < 8 ; col ++){
            Piece p = board->board_places[row][col];
            if (p.in_game){
                if (empty_square != 0){
                    fen[current_position++] = '0' + empty_square ;
                    empty_square = 0 ;
                }
                fen[current_position] = piece_decoder(p.piece_type, p.color);
                current_position ++ ;
            } else {
                empty_square ++ ;
            }
        }
        if (empty_square != 0) {
            fen[current_position++] = '0' + empty_square;
        }
        if (row != 7)
            fen[current_position++] = '/';
    }
    fen[current_position++] = ' ';
    fen[current_position++] = (board->current_turn == WHITE) ? 'w' : 'b' ;
    fen[current_position++] = ' ';
    int white_king = (board->players[WHITE]).can_castle_kingside ;
    int black_king = (board->players[BLACK]).can_castle_kingside ;
    int white_queen = (board->players[WHITE]).can_castle_queenside ;
    int black_queen = (board->players[BLACK]).can_castle_queenside ;
    if (white_king){
        fen[current_position++] = 'K';
    }
    if (white_queen){
        fen[current_position++] = 'Q';
    }
    if (black_king){
        fen[current_position++] = 'k';
    }
    if (black_queen){
        fen[current_position++] = 'q';
    }
    if (!((white_king)||(white_queen)||(black_king)||(black_queen))){
        fen[current_position++] = '-';
    }
    fen[current_position++] = ' ';
    if (board->en_passant_row == -1){
        fen[current_position++] = '-';
    } else {
        fen[current_position++] = (char)(board->en_passant_col + 'a');
        fen[current_position++] = (char)('8'- board->en_passant_row );
    }
    fen[current_position++] = ' ';
    current_position += sprintf(fen + current_position, "%d", board->halfmove_clock);
    fen[current_position++] = ' ';
    current_position += sprintf(fen + current_position, "%d", board->fullmove_number);
    fen[current_position] = '\0';
}

int save_file(char *fen){
    char filepath[100];
    int i = 1;
    sprintf(filepath, "Saved_Games/Game(%d)", i);
    while (is_file_found(filepath)) {
        i++;
        sprintf(filepath, "Saved_Games/Game(%d)", i);
    }

    FILE *file = fopen(filepath , "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 0 ;
    }
    fprintf(file, "%s", fen);
    fclose(file);
    return 1 ;
}
