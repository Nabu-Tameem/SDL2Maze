#include "CBoard.h"
using namespace std;

/// size of border around the board in pixels
const int BORDER = 5;
/// distance between one cell to the other in pixels
const int SEPERATION = 0;


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
    // This is used to figure out the size in pixels for each column and row
    int rowsEmptySpaces = (rows - 1) * SEPERATION + this->mBoardSeperation + BORDER;
    int colsEmptySpaces = (cols - 1) * SEPERATION + this->mBoardSeperation + BORDER;

    // Calculate the height and width of each cell (floor of the number will be used, because int)
    this->mCellRect.h = (screenHeight - rowsEmptySpaces) / rows;
    this->mCellRect.w = (screenWidth - colsEmptySpaces) / cols;
    this->mBoardSeperation = this->mCellRect.h;

    // Make it into a square
    if (this->mCellRect.h < this->mCellRect.w)
        this->mCellRect.w = this->mCellRect.h;
    else
        this->mCellRect.h = this->mCellRect.w;

    // Generate all the needed cell
    for (int y = 0; y < rows; y++) {
        vector <shared_ptr<CCell> > row;
        for (int x = 0; x < cols; x++) {
            shared_ptr<CCell> cell = make_shared<CCell>();
            row.push_back(cell);
        }

        this->mCells.push_back(row);
    }

    // Calculate width and height of the cells
    this->mBoardRect.h = (rows - 1) * (this->mCellRect.h + SEPERATION) + this->mCellRect.h + this->mBoardSeperation * 2;
    this->mBoardRect.w = (cols - 1) * (this->mCellRect.w + SEPERATION) + this->mCellRect.w + this->mBoardSeperation * 2;

    this->mBorderRect.h = this->mBoardRect.h + BORDER * 2;
    this->mBorderRect.w = this->mBoardRect.w + BORDER * 2;
    this->mBorderRect.x = (screenWidth - this->mBorderRect.w) / 2;
    this->mBorderRect.y = (screenHeight - this->mBorderRect.h) / 2;

}

/**
 * Draw all the cells on the board
 * @param renderer The renderer to be used for drawing
 */
void CBoard::draw(SDL_Renderer* renderer)
{
    //TODO center board
    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    // Draw the border
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(renderer, &this->mBorderRect);
    SDL_RenderFillRect(renderer, &this->mBorderRect);

    // Calculate the position of the board relative to the boarder
    this->mBoardRect.x = this->mBorderRect.x + BORDER;
    this->mBoardRect.y = this->mBorderRect.y + BORDER;
    // Draw the board background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(renderer, &this->mBoardRect);
    SDL_RenderFillRect(renderer, &this->mBoardRect);
    
    int xOffset = this->mBoardRect.x + this->mBoardSeperation;
    int yOffset = this->mBoardRect.y + this->mBoardSeperation;

    // draw the cells
    for (auto row : this->mCells) {
        int basexoffset = xOffset;
        
        for (auto cell : row) {
            cell->draw(this->mCellRect, renderer, xOffset, yOffset);
            xOffset += this->mCellRect.w + SEPERATION;
        }
        // reset x offset to it starts at origin again
        xOffset = basexoffset;
        yOffset += this->mCellRect.h + SEPERATION;
    }

    SDL_RenderPresent(renderer);
}
