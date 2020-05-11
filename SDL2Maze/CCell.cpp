#include <map>

#include "bin/include/SDL2/SDL.h"
#include "CCell.h"

/**
 * Constructor
 */
CCell::CCell()
{
}

/**
 * Draw the cell using a specified size and offset for the relative coordinates
 * @param rect An SDL rectangle holding the dimensions for each cell
 * @param renderer The renderer to draw wtih
 * @param xOffset The offset from the x direction in pixels
 * @param yOffset The offset from the y direction in pixels
 */
void CCell::draw(SDL_Rect cellRect, SDL_Renderer* renderer, int xOffset, int yOffset, int seperation)
{
    // Draw the cell in white, blocked in black (TODO visited in blue)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);


    // Calculate the offset from origin in pixels
    // Offset of one cell will be the size of one side + 2 pixels that surround it
    cellRect.x = xOffset;
    cellRect.y = yOffset;

    SDL_RenderDrawRect(renderer, &cellRect);
    SDL_RenderFillRect(renderer, &cellRect);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);


    // Draw wall fillers, these will make connected cells appear to be connected
    if (this->mSouthCell != nullptr) {
        SDL_Rect wallFiller;

        wallFiller.w = cellRect.w;
        wallFiller.h = seperation;
        wallFiller.x = xOffset;
        wallFiller.y = yOffset + cellRect.h;

        SDL_RenderDrawRect(renderer, &wallFiller);
        SDL_RenderFillRect(renderer, &wallFiller);
    }

    if (this->mEastCell != nullptr) {
        SDL_Rect wallFiller;

        wallFiller.w = seperation;
        wallFiller.h = cellRect.h;
        wallFiller.x = xOffset + cellRect.w;
        wallFiller.y = yOffset;

        SDL_RenderDrawRect(renderer, &wallFiller);
        SDL_RenderFillRect(renderer, &wallFiller);
    }

}
