#include <SDL.h>
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
void CCell::draw(SDL_Rect cellRect, SDL_Renderer* renderer, int xOffset, int yOffset)
{
    // Draw the cell in white, blocked in black (TODO visited in blue)
    if (this->mBlocked)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    else
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);


    // Calculate the offset from origin in pixels
    // Offset of one cell will be the size of one side + 2 pixels that surround it
    cellRect.x = xOffset;
    cellRect.y = yOffset;

    SDL_RenderDrawRect(renderer, &cellRect);
    SDL_RenderFillRect(renderer, &cellRect);
}
