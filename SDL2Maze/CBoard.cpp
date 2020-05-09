#include "CBoard.h"
using namespace std;

/**
 * Constructor
 * @param rows The number of rows in the board
 * @param cols The number of cols in the board
 * @param screenHeight The height of the screen in pixels
 * @param screenWidth The width of the screen in pixels
 */
CBoard::CBoard(int rows, int cols, int screenHeight, int screenWidth)
{
    // The number of pixels of empty space in the entire board 
    // (1px around each cell, in other words, 2px in the inside of the board, 1px on the outside)
    // This is used to figure out the size in pixels for each column and row
    int rowsEmptySpaces = (rows - 1) * 2 + 2; 
    int colsEmptySpaces = (cols - 1) * 2 + 2;

    // Calculate the height and width of each cell (floor of the number will be used, because int)
    this->mCellRect.h = (screenHeight - rowsEmptySpaces) / rows;
    this->mCellRect.w = (screenWidth - colsEmptySpaces) / cols;

    // Generate all the needed cell
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            shared_ptr<CCell> cell = make_shared<CCell>(i, j);
            this->mCells.push_back(cell);
        }
    }

}

/**
 * Draw all the cells on the board
 * @param renderer The renderer to be used for drawing
 */
void CBoard::draw(SDL_Renderer* renderer)
{
    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    for (shared_ptr<CCell> cell : this->mCells) {
        cell->draw(this->mCellRect, renderer);
    }

    SDL_RenderPresent(renderer);
}
