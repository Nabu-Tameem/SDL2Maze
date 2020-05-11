#include "CBoard.h"

using namespace std;

constexpr int TOP = 0;
constexpr int RIGHT = 1; 
constexpr int BOTTOM = 2;
constexpr int LEFT = 3;

/**
 * Constructor
 * @param rows The number of rows in the board
 * @param cols The number of cols in the board
 * @param screenHeight The height of the screen in pixels
 * @param screenWidth The width of the screen in pixels
 */
CBoard::CBoard(int rows, int cols, int screenWidth, int screenHeight)
{
    // The number of pixels of empty space in the entire board 
    // This is used to figure out the size in pixels for each column and row
    int rowsEmptySpaces = (rows - 1) * this->mCellSeperation + this->mBoardSeperation + this->mBorderWidth;
    int colsEmptySpaces = (cols - 1) * this->mCellSeperation + this->mBoardSeperation + this->mBorderWidth;

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

    // Calculate width and height of the entire board
    this->mBoardRect.h = (rows - 1) * (this->mCellRect.h + this->mCellSeperation) + this->mCellRect.h + this->mBoardSeperation * 2;
    this->mBoardRect.w = (cols - 1) * (this->mCellRect.w + this->mCellSeperation) + this->mCellRect.w + this->mBoardSeperation * 2;

    // Calculate the Border rect dimensons and location (centered on screen)
    this->mBorderRect.h = this->mBoardRect.h + this->mBorderWidth * 2;
    this->mBorderRect.w = this->mBoardRect.w + this->mBorderWidth * 2;
    this->mBorderRect.x = (screenWidth - this->mBorderRect.w) / 2;
    this->mBorderRect.y = (screenHeight - this->mBorderRect.h) / 2;

    // Picks a random cell in first column to be the starting cell
    int row = rand() % rows;
    mStartingCell = mCells[row][0];
    mStartingCell->setStarting(true);

}

/**
 * randomly picks the next cell to use for generation of the maze
 * @param row The row of the current cell
 * @param col The column of the current cell
 */
void getNextCell(int& row, int& col) {
    int direction = rand() % 4;

    if (direction == TOP)
        row -= 1;
    else if (direction == BOTTOM)
        row += 1;
    else if (direction == RIGHT)
        col += 1;
    else if (direction == LEFT)
        col -= 1;
}

/**
 * Pick a cell to be a part of the maze
 */
void CBoard::generateCell()
{
    

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
    this->mBoardRect.x = this->mBorderRect.x + this->mBorderWidth;
    this->mBoardRect.y = this->mBorderRect.y + this->mBorderWidth;
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
            cell->draw(this->mCellRect, renderer, xOffset, yOffset, this->mCellSeperation);
            xOffset += this->mCellRect.w + this->mCellSeperation;
        }
        // reset x offset to it starts at origin again
        xOffset = basexoffset;
        yOffset += this->mCellRect.h + this->mCellSeperation;
    }

    SDL_RenderPresent(renderer);
}
