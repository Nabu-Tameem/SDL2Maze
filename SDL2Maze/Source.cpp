#include <SDL.h>
#include <time.h>
#include <stdio.h>

#include "CBoard.h"

// Constants for generating the window and board
const int SCREENWIDTH = 1280;
const int SCREENHEIGHT = 720;
const int ROWS = 40;
const int COLS = 40;
// TODO Add winning condition, add solver, make entire board green when solved by user
int main(int argc, char* args[]) {
    
    // Initialize sdl
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("ERROR: %s.\nUnable to initialize SDL.\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    else {
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;

        
        if (SDL_CreateWindowAndRenderer(SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_SHOWN,
            &window, &renderer) != 0) {
            printf("ERROR: %s.\nUnable to create window and renderer.\n", SDL_GetError());
            return EXIT_FAILURE;
        }

        // Create the board and seed the randomizer
        else {
            
            CBoard board(ROWS, COLS, SCREENWIDTH, SCREENHEIGHT);
            board.setGoal(board.maxCol(), board.maxRow() - 1, true);
            srand(time(NULL));

            board.draw(renderer);

            
            bool done = false;
            while (!done) {
                 SDL_Event event;

                 while (SDL_PollEvent(&event)) {
                     board.draw(renderer);
                     switch (event.type) {
                     case SDL_QUIT:
                         done = true;
                         break;

                     case SDL_KEYDOWN:
                         switch (event.key.keysym.sym) {
                         case SDLK_RETURN:  // generate a new board
                             board.clear();
                             board.generate(renderer);
                             break;
                         
                         case SDLK_SPACE:   
                             board.solve(renderer);
                             break;

                         case SDLK_TAB:     
                             board.clearSolution();
                             break;

                         case SDLK_UP:      
                             board.move("north");
                             break;

                         case SDLK_DOWN:      
                             board.move("south");
                             break;

                         case SDLK_RIGHT:     
                             board.move("east");
                             break;

                         case SDLK_LEFT:      
                             board.move("west");
                             break;

                         }// end switch key
                     }// end switch event
                 }// end while event
                
            }// end while not done
        }// end else window and renderer successful

        if (renderer) {
            SDL_DestroyRenderer(renderer);
        }
        if (window) {
            SDL_DestroyWindow(window);
        }
    }// end else init successful

    SDL_Quit();
	return 0;
}