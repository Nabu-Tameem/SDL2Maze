#include "bin/include/SDL2/SDL.h"
#include <time.h>
#include "CBoard.h"

int main(int argc, char* args[]) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, 0);
    CBoard board(80, 80, 720, 1280);
    srand(time(NULL));
    bool running = true;
    while (running) {
        SDL_Event event;
        board.draw(renderer);
        board.generateCell();
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
    }

    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }

    SDL_Quit();
	return 0;
}