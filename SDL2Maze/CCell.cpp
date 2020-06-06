#include <map>
#include <string>
#include <SDL.h>
#include "CCell.h"

using namespace std;

/**
 * Constructor
 * @param row The row on the board this cell is in
 * @param col The column on the board this cell is in
 */
CCell::CCell(int col, int row)
{
    this->mPos.x = col;
    this->mPos.y = row;
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
    if (this->mStarting)
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
    else if (this->mGoal)
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    else if (this->mCurrentGenerationCell)
        SDL_SetRenderDrawColor(renderer, 255, 125, 0, SDL_ALPHA_OPAQUE);
    else if (this->mCurrentUserCell)
        SDL_SetRenderDrawColor(renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
    else if (this->mSolution)
        SDL_SetRenderDrawColor(renderer, 0, 255, 255, SDL_ALPHA_OPAQUE);
    else
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);


    // Calculate the offset from origin in pixels
    // Offset of one cell will be the size of one side + 2 pixels that surround it
    cellRect.x = xOffset;
    cellRect.y = yOffset;

    SDL_RenderDrawRect(renderer, &cellRect);
    SDL_RenderFillRect(renderer, &cellRect);


    // Draw the horizontal connection between the cells
    if (this->mSouthCell != nullptr) {
        if (this->mSouthCell->isSolution() && this->mSolution) {
            SDL_SetRenderDrawColor(renderer, 0, 255, 255, SDL_ALPHA_OPAQUE);
        }
        else {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        }
        SDL_Rect wallFiller;

        wallFiller.w = cellRect.w;
        wallFiller.h = seperation;
        wallFiller.x = xOffset;
        wallFiller.y = yOffset + cellRect.h;

        SDL_RenderDrawRect(renderer, &wallFiller);
        SDL_RenderFillRect(renderer, &wallFiller);
    }

    // Draw the vertical connection between the cells
    if (this->mEastCell != nullptr) {
        if (this->mEastCell->isSolution() && this->mSolution) {
            SDL_SetRenderDrawColor(renderer, 0, 255, 255, SDL_ALPHA_OPAQUE);
        }
        else {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        }
        SDL_Rect wallFiller;

        wallFiller.w = seperation;
        wallFiller.h = cellRect.h;
        wallFiller.x = xOffset + cellRect.w;
        wallFiller.y = yOffset;

        SDL_RenderDrawRect(renderer, &wallFiller);
        SDL_RenderFillRect(renderer, &wallFiller);
    }

}

/**
 * Get the neghboring cells
 * @returns map<string, shared_ptr<CCell> > containing all the linked cells
 */
map<string, shared_ptr<CCell>> CCell::getNeighbors()
{
    map<string, shared_ptr<CCell>> neighbors;
    neighbors["north"] = this->mNorthCell;
    neighbors["south"] = this->mSouthCell;
    neighbors["east"] = this->mEastCell;
    neighbors["west"] = this->mWestCell;


    return neighbors;
}

/**
 * Clears cell to its original values (clears maze generation)
 */
void CCell::clear()
{
    this->mNorthCell = nullptr;
    this->mSouthCell = nullptr;
    this->mEastCell = nullptr;
    this->mWestCell = nullptr;
    
    this->mVisited = false;
    this->mSolution = false;
    this->mCurrentUserCell = false;
}
