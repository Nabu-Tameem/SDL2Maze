#include <SDL.h>
#include <time.h>
#include <stdio.h>

#include "CBoard.h"

// Constants for generating the window and board
const int SCREENWIDTH = 1280;
const int SCREENHEIGHT = 720;
const int ROWS = 120;
const int COLS = 120;

int main(int argc, char* args[]) {
    
    // Initialize sdl
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("ERROR: %s.\nUnable to initialize SDL.\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    else {
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;

        // Create the window and renderer
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

            // Event loop
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
                         case SDLK_RETURN:  // generate a new board when return is hit
                             board.clear();
                             board.generate();
                             break;
                         
                         case SDLK_SPACE:   // generate a solution to the current board
                             board.solve();
                             break;

                         case SDLK_TAB:     // clear any generated solution
                             board.clearSolution();
                             break;

                         case SDLK_UP:      // Move the user up on the maze
                             board.move("north");
                             break;

                         case SDLK_DOWN:      // Move the user down on the maze
                             board.move("south");
                             break;

                         case SDLK_RIGHT:      // Move the user right on the maze
                             board.move("east");
                             break;

                         case SDLK_LEFT:      // Move the user left on the maze
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