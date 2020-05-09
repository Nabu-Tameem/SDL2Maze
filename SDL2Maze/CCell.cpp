#include <SDL.h>
#include "CCell.h"

/**
 * Constructor
 * @param x The x coordinate of the cell
 * @param y The y coordinate of the cell
 * @param blocked Specifiy if the cell is blocked, default false
 */
CCell::CCell(int x, int y, bool blocked)
{
	this->mX = x;
	this->mY = y;
    this->mBlocked = blocked;
}

/**
 * Draw the cell using a specified size and offset for the relative coordinates
 * @param rect An SDL rectangle holding the dimensions for each cell
 * @param renderer The renderer to draw wtih
 */
void CCell::draw(SDL_Rect cellRect, SDL_Renderer* renderer)
{
    // Draw the cell in white (TODO change color based on cell state
    if (this->mBlocked)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    else
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);


    // Calculate the offset from origin in pixels
    // Offset of one cell will be the size of one side + 2 pixels that surround it
    cellRect.x = 1;
    cellRect.y = 1;
    cellRect.x += (cellRect.w + 2) * this->mX;
    cellRect.y = (cellRect.h + 2) * this->mY;

    SDL_RenderDrawRect(renderer, &cellRect);
    SDL_RenderFillRect(renderer, &cellRect);
}
