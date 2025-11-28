#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "board.h"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 920

void draw_text(SDL_Renderer* ren, TTF_Font* font,
               const char* text, SDL_Color color, int x, int y)
{
    SDL_Surface* surf = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, surf);
    SDL_Rect rect = {x, y, surf->w, surf->h};
    SDL_RenderCopy(ren, tex, NULL, &rect);
    SDL_FreeSurface(surf);
    SDL_DestroyTexture(tex);
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

    if (TTF_Init() == -1) {
    printf("TTF_Init Error: %s\n", TTF_GetError());
    return 1;
    }

    TTF_Font* font = TTF_OpenFont("assets/arial.ttf", 24); 
    if (!font) {
    printf("TTF_OpenFont Error: %s\n", TTF_GetError());
    return 1;
    }

    

    int running = 1;
    int move_count = 0; // move counter and also indicates turn (white starts)
    Board board;
    init_board(&board);
    SDL_Event event;
    SDL_Rect pieces_captured[2][15]; // rectangles for captured pieces display
    SDL_Color color_black = {0, 0, 0, 255};
    char letters[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    int numbers[] = {8, 7, 6, 5, 4, 3, 2, 1};
    char options[][20] = {"New", "Save", "Load", "Undo", "Redo"};
    // Initialize chessboard squares
    for (int i=0 ; i<8 ; i++){
        for (int j=0 ; j<8 ; j++){
            (board.chessboard[i][j]).x = 80 + j*80;
            (board.chessboard[i][j]).y = 125 + i*80;
            (board.chessboard[i][j]).w = 80;
            (board.chessboard[i][j]).h = 80;
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
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }
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
                SDL_RenderFillRect(ren, &(board.chessboard[i][j]));
            }
        };
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
        // draw pieces
        for(int row = 0; row < 8; row++) {
            for(int col = 0; col < 8; col++) {
                Piece piece = board.board_places[row][col];
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
                    SDL_Rect dest_rect = board.chessboard[row][col];
                    SDL_RenderCopy(ren, piece_tex, NULL, &dest_rect);
                    SDL_FreeSurface(piece_surf);
                    SDL_DestroyTexture(piece_tex);
                }
            }
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
        SDL_RenderPresent(ren);
    }

    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}