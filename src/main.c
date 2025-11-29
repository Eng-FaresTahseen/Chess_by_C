#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "board.h"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 920

void draw_text(SDL_Renderer* ren, TTF_Font* font,const char* text, SDL_Color color, int x, int y)
{
    SDL_Surface* surf = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, surf);
    SDL_Rect rect = {x, y, surf->w, surf->h};
    SDL_RenderCopy(ren, tex, NULL, &rect);
    SDL_FreeSurface(surf);
    SDL_DestroyTexture(tex);
}

int is_clicked_highlighted_square(MoveList highlighted , int row , int col) {
    for (int i = 0; i < highlighted.count; i++) {
        if (highlighted.moves[i].row == row && highlighted.moves[i].col == col) {
            return 1;
        }
    }
    return 0;
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }
    
    SDL_Window *win = SDL_CreateWindow("Chess" ,SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,WINDOW_WIDTH,WINDOW_HEIGHT,SDL_WINDOW_SHOWN);
    if (win == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == NULL) {
        SDL_DestroyWindow(win);
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
  
    if (TTF_Init() == -1) {
        printf("TTF_Init Error: %s\n", TTF_GetError());
        return 1;
    }
    
    TTF_Font* font = TTF_OpenFont("assets/arial.ttf", 24); 
    if (!font) {
        printf("TTF_OpenFont Error: %s\n", TTF_GetError());
        return 1;
    }
    SDL_Init(SDL_INIT_AUDIO);
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 512) < 0) {
        printf("Mix_OpenAudio Error: %s\n", Mix_GetError());
        return 1;
    }
    Mix_AllocateChannels(8);

    // Load sound effects
    Mix_Chunk *capture_sound = Mix_LoadWAV("./assets/capture.wav");
    Mix_Chunk *move_sound = Mix_LoadWAV("./assets/move-self.wav");
    
    // Game variables
    
    //selected square
    MoveList highlighted_squares;
    highlighted_squares.count = 0;
    for (int i = 0; i < 27; i++) {
        highlighted_squares.moves[i].row = -1;
        highlighted_squares.moves[i].col = -1;
    }

    int running = 1 , x , y ; // main loop flag , x, y; // mouse coordinates
    int move_count = 0; // move counter and also indicates turn (white starts)
    int latest_move = move_count;
    Board board[500]; // array of boards to store game states for undo/redo
    init_board(&board[move_count]); // initialize the first board
    Player current_player = board[move_count].players[WHITE]; // current player pointer
    SDL_Event event;

    Type pieces_captured_type[2][15]; // types of captured pieces for display
    SDL_Rect pieces_captured[2][15]; // rectangles for captured pieces display

    SDL_Color color_black = {0, 0, 0, 255};
    char letters[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    int numbers[] = {8, 7, 6, 5, 4, 3, 2, 1};
    char options[][20] = {"New", "Save", "Load", "Undo", "Redo"};
    // Initialize chessboard squares
    for (int i=0 ; i < 8 ; i++){
        for (int j=0 ; j < 8 ; j++){
            (board[move_count].chessboard[i][j]).x = 80 + j*80;
            (board[move_count].chessboard[i][j]).y = 125 + i*80;
            (board[move_count].chessboard[i][j]).w = 80;
            (board[move_count].chessboard[i][j]).h = 80;
        };
    };
    // Initialize captured pieces areas
    for (int i=0 ; i<2 ; i++){
        for (int j=0 ; j<15 ; j++){
            pieces_captured[i][j].x = 100 + j*40;
            pieces_captured[i][j].y = (i==0) ? 810 : 70;
            pieces_captured[i][j].w = 40;
            pieces_captured[i][j].h = 40;
        };
    };
    // commands
    char commands[][40] = {" ","White wins","Black wins","Draw by stalemate",
        "Draw by insufficient material","Draw by threefold repetition",
        "Draw by fifty-move rule","Game saved","Game loaded","Move undone",
        "Move redone","Invalid move","Check","Which piece to promote to? (Q,R,B,N)"};
    int command_index = 0;
    // Main loop
    while (running) {
        latest_move = (move_count > latest_move) ? move_count : latest_move;
        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
        SDL_RenderClear(ren);
        // draw chessboard
        for (int i=0 ; i<8 ; i++){
            for (int j=0 ; j<8 ; j++){
                if ((i+j)%2 == 0){
                    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
                } else {
                    SDL_SetRenderDrawColor(ren, 128, 128, 128, 255);
                        }
                SDL_RenderFillRect(ren, &(board[move_count].chessboard[i][j]));
            }
        }
        // draw letters and numbers
        for (int i=0 ; i<8 ; i++){
            char letter_str[2] = {letters[i], '\0'};
            draw_text(ren, font, letter_str, color_black, 80 + i*80 + 30, 780);
            
            char number_str[3];
            sprintf(number_str, "%d", numbers[i]);
            draw_text(ren, font, number_str, color_black, 40, 80 + i*80 + 75);
        }
        // draw captured pieces areas
        for (int i=0 ; i<2 ; i++){
            for (int j=0 ; j<15 ; j++){
                SDL_SetRenderDrawColor(ren, 200, 200, 200, 255);
                SDL_RenderDrawRect(ren, &pieces_captured[i][j]);
            };
        };
        // draw pieces
        for(int row = 0; row < 8; row++) {
            for(int col = 0; col < 8; col++) {
                Piece piece = board[move_count].board_places[row][col];
                if (piece.in_game) {
                    char filepath[50];
                    const char* color_str = (piece.color == WHITE) ? "white" : "black";
                    const char* type_str;
                    switch (piece.piece_type) {
                        case PAWN: type_str = "pawn"; break;
                        case ROOK: type_str = "rook"; break;
                        case KNIGHT: type_str = "knight"; break;
                        case BISHOP: type_str = "bishop"; break;
                        case QUEEN: type_str = "queen"; break;
                        case KING: type_str = "king"; break;
                    }
                    sprintf(filepath, "./assets/%s_%s.png", type_str, color_str);
                    SDL_Surface* piece_surf = IMG_Load(filepath);
                    SDL_Texture* piece_tex = SDL_CreateTextureFromSurface(ren, piece_surf);
                    SDL_Rect dest_rect = board[move_count].chessboard[row][col];
                    SDL_RenderCopy(ren, piece_tex, NULL, &dest_rect);
                    SDL_FreeSurface(piece_surf);
                    SDL_DestroyTexture(piece_tex);
                }
            }
        }
        // show highlights after drawing pieces so they are visible on top
        show_possible_moves(&board[move_count] , highlighted_squares , ren);
        // options
        for (int i = 0; i < 5; i++) {
            char* option_str = options[i];
            SDL_Surface* option_surf = TTF_RenderText_Solid(font, option_str, color_black);
            SDL_Texture* option_tex = SDL_CreateTextureFromSurface(ren, option_surf);
            SDL_Rect button_rect = {90 + 128*i, 10, 110, 40};
            SDL_SetRenderDrawColor(ren, 180, 220, 255, 255);
            SDL_RenderFillRect(ren, &button_rect);
            SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
            SDL_RenderDrawRect(ren, &button_rect);
            SDL_Rect text_rect;
            text_rect.w = option_surf->w;
            text_rect.h = option_surf->h;
            text_rect.x = button_rect.x + (button_rect.w - text_rect.w) / 2;
            text_rect.y = button_rect.y + (button_rect.h - text_rect.h) / 2;
            SDL_RenderCopy(ren, option_tex, NULL, &text_rect);
            SDL_FreeSurface(option_surf);
            SDL_DestroyTexture(option_tex);
        }
        // player turn display
        const char* turn_str = (move_count % 2 == 0) ? "White's Turn" : "Black's Turn";
        SDL_Surface* turn_surf = TTF_RenderText_Solid(font, turn_str, color_black);
        SDL_Texture* turn_tex = SDL_CreateTextureFromSurface(ren, turn_surf);
        SDL_Rect turn_rect = {WINDOW_WIDTH - turn_surf->w - 20, 880, turn_surf->w, turn_surf->h};
        SDL_RenderCopy(ren, turn_tex, NULL, &turn_rect);
        SDL_FreeSurface(turn_surf);
        SDL_DestroyTexture(turn_tex);
        // show current command
        const char* command_str = commands[command_index];
        draw_text(ren, font, command_str, color_black, 20, 880);
        // Event handling
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            // Handle other events (mouse clicks, etc.) here
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                x = event.button.x;
                y = event.button.y;
                // Handle mouse click at (x, y)
                if (check_in_bounds(x, y)) {
                    int row = (y - 125) / 80;
                    int col = (x - 80) / 80;
                    if ((board[move_count].board_places[row][col].in_game) && (board[move_count].board_places[row][col].color == ((move_count % 2 == 0) ? WHITE : BLACK))) {
                        // Piece selected
                        int selecting = 1;
                        board[move_count].selected_piece = &board[move_count].board_places[(y - 125) / 80][(x - 80) / 80];
                        MoveList possible_moves = get_possible_moves(&board[move_count], board[move_count].selected_piece->row, board[move_count].selected_piece->col);
                        for (int i=0 ; i < possible_moves.count ; i++){
                            highlighted_squares.moves[i].row = possible_moves.moves[i].row;
                            highlighted_squares.moves[i].col = possible_moves.moves[i].col;
                        }
                        highlighted_squares.count = possible_moves.count;
                        } else if ((board[move_count].selected_piece != NULL) && is_clicked_highlighted_square(highlighted_squares , row , col)) {
                            // Move selected piece
                            int from_row = board[move_count].selected_piece->row;
                            int from_col = board[move_count].selected_piece->col;
                            int to_row = row;
                            int to_col = col;
                            move_piece(board, from_row, from_col, to_row, to_col , move_count , (is_clicked_highlighted_square(highlighted_squares , to_row , to_col) && board[move_count].board_places[to_row][to_col].in_game) ? capture_sound : move_sound);
                            // Clear selection and highlights
                            board[move_count].selected_piece = NULL;
                            highlighted_squares.count = 0;
                            for (int i = 0; i < 27; i++) {
                                highlighted_squares.moves[i].row = -1;
                                highlighted_squares.moves[i].col = -1;
                            }
                            move_count++;
                            current_player = board[move_count].players[(move_count % 2 == 0) ? WHITE : BLACK];
                            }
                } else if (x >= 90 && x <= 200 && y >= 10 && y <= 50) {
                    // New Game button clicked
                    move_count = 0;
                    init_board(&board[move_count]);
                    highlighted_squares.count = 0;
                    for (int i = 0; i < 27; i++) {
                        highlighted_squares.moves[i].row = -1;
                        highlighted_squares.moves[i].col = -1; }
                        command_index = 0;
                    } else if (x >= 218 && x <= 328 && y >= 10 && y <= 50) {
                        // Save Game button clicked
                        // Implement save functionality here
                        command_index = 7; // "Game saved"
                    } else if (x >= 346 && x <= 456 && y >= 10 && y <= 50) {
                        // Load Game button clicked
                        // Implement load functionality here
                        command_index = 8; // "Game loaded"
                    } else if (x >= 474 && x <= 584 && y >= 10 && y <= 50) {
                        // Undo button clicked
                        if (move_count > 0) {
                            move_count--;
                            command_index = 9; // "Move undone"
                        }
                    } else if (x >= 602 && x <= 712 && y >= 10 && y <= 50) {
                        // Redo button clicked
                        if (move_count < latest_move) {
                            move_count++;
                            command_index = 10; // "Move redone"
                        }
                    }
            }
        }

        // White captured pieces
        if (board[move_count].players[WHITE].total_captured > 0) {
            for (int i = 0; i < board[move_count].players[WHITE].total_captured; i++) {
                Type captured_type = board[move_count].players[WHITE].captured_piece[i].piece_type;
                char filepath[50];
                sprintf(filepath, "./assets/%s_black.png",
                        (captured_type == PAWN) ? "pawn" :
                        (captured_type == ROOK) ? "rook" :
                        (captured_type == KNIGHT) ? "knight" :
                        (captured_type == BISHOP) ? "bishop" :
                        (captured_type == QUEEN) ? "queen" : "king");
                SDL_Surface* piece_surf = IMG_Load(filepath);
                SDL_Texture* piece_tex = SDL_CreateTextureFromSurface(ren, piece_surf);
                SDL_RenderCopy(ren, piece_tex, NULL, &pieces_captured[0][i]);
                SDL_FreeSurface(piece_surf);
                SDL_DestroyTexture(piece_tex);
            }
        }
        // Black captured pieces
        if (board[move_count].players[BLACK].total_captured > 0) {
            for (int i = 0; i < board[move_count].players[BLACK].total_captured; i++) {
                Type captured_type = board[move_count].players[BLACK].captured_piece[i].piece_type;
                char filepath[50];
                sprintf(filepath, "./assets/%s_white.png",
                        (captured_type == PAWN) ? "pawn" :
                        (captured_type == ROOK) ? "rook" :
                        (captured_type == KNIGHT) ? "knight" :
                        (captured_type == BISHOP) ? "bishop" :
                        (captured_type == QUEEN) ? "queen" : "king");
                SDL_Surface* piece_surf = IMG_Load(filepath);
                SDL_Texture* piece_tex = SDL_CreateTextureFromSurface(ren, piece_surf);
                SDL_RenderCopy(ren, piece_tex, NULL, &pieces_captured[1][i]);
                SDL_FreeSurface(piece_surf);
                SDL_DestroyTexture(piece_tex);
            }
        }
        
       SDL_RenderPresent(ren);
    }
    if (capture_sound) Mix_FreeChunk(capture_sound);
    if (move_sound) Mix_FreeChunk(move_sound);
    Mix_CloseAudio();
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}