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
    // The number of pixels of empty space in the entire board (2px around each cell)
    // This is used to figure out the size in pixels for each column and row
    int rowsEmptySpaces = (rows + 2) * 2; 
    int colsEmptySpaces = (cols + 2) * 2;

    // Calculate the height and width of each cell (floor of the number will be used, because int)
    this->cell.h = (screenHeight - rowsEmptySpaces) / rows;
    this->cell.w = (screenWidth - colsEmptySpaces) / cols;

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
    // TODO actually make the board draw the cell
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(renderer, 320, 200, 300, 240);
    SDL_RenderDrawLine(renderer, 300, 240, 340, 240);
    SDL_RenderDrawLine(renderer, 340, 240, 320, 200);
    SDL_RenderPresent(renderer);
}
