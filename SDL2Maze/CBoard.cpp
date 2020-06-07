#include "CBoard.h"
#include <Windows.h>
#include <ctime>
using namespace std;

constexpr int TOP = 0;
constexpr int RIGHT = 1; 
constexpr int BOTTOM = 2;
constexpr int LEFT = 3;

const tuple<string> DIRECTIONS = ("north", "south", "east", "west");

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
    int rowsEmptySpaces = (rows - 1) * this->mCellSeperation + this->mBorderSeperation + this->mBorderWidth + this->mBorderOffset;
    int colsEmptySpaces = (cols - 1) * this->mCellSeperation + this->mBorderSeperation + this->mBorderWidth + this->mBorderOffset;

    // Calculate the height and width of each cell (floor of the number will be used, because int)
    this->mCellRect.h = (screenHeight - rowsEmptySpaces) / rows;
    this->mCellRect.w = (screenWidth - colsEmptySpaces) / cols;

    // Make it into a square
    if (this->mCellRect.h < this->mCellRect.w)
        this->mCellRect.w = this->mCellRect.h;
    else
        this->mCellRect.h = this->mCellRect.w;

    // Generate all the needed cell
    for (int y = 0; y < rows; y++) {
        vector <shared_ptr<CCell> > row;
        for (int x = 0; x < cols; x++) {
            shared_ptr<CCell> cell = make_shared<CCell>(x, y);
            row.push_back(cell);
        }

        this->mCells.push_back(row);
    }

    

    
    this->mBoardRect.h = rowsEmptySpaces + rows * this->mCellRect.h - this->mBorderSeperation;
    this->mBoardRect.w = colsEmptySpaces + cols * this->mCellRect.w - this->mBorderSeperation;

    this->mBorderRect.h = this->mBoardRect.h + this->mBorderSeperation * 2;
    this->mBorderRect.w = this->mBoardRect.w + this->mBorderSeperation * 2;
    this->mBorderRect.x = (screenWidth - this->mBorderRect.w) / 2;
    this->mBorderRect.y = (screenHeight - this->mBorderRect.h) / 2;

}

/**
 * Generate the maze using DFS algorithm.
 * linked cells in the graph will show as connected in the board.
 */
void CBoard::generate(SDL_Renderer* renderer)
{    
    if (mStartingCell != nullptr) {
        mStartingCell->setStarting(false);
    }
    // Picks a random cell in first column to be the starting cell
    int startingRow = rand() % mCells.size();
    this->mStartingCell = mCells[startingRow][0];
    this->mStartingCell->setStarting(true);

    this->mCurrentUserCell = mStartingCell;
    this->mCurrentUserCell->setSolution(true);

    this->clearVisited();
    vector< SDL_Point > stack;
    int visitedCount = 0;
    int boardSize = (int) (this->mCells.size() * this->mCells[0].size());

    shared_ptr<CCell> currentCell = this->mStartingCell;
    shared_ptr<CCell> nextCell = nullptr;
    bool end = false;
    // start generating the board
    while (visitedCount < boardSize - 1) {
        //SDL_Delay(500);
        currentCell->setGenerationCell(true);
        currentCell->setVisited(true);

        // If no usable cell exists, then pop the stack and backtrack
        if (this->isBlocked(currentCell) || currentCell->isGoal()) {
            currentCell->setGenerationCell(false);
            currentCell = this->mCells[stack.back().y][stack.back().x];
            stack.pop_back();
            continue;
        }

        stack.push_back(currentCell->getPos());

        // get the next cell in the board
        nextCell = getNextGenerationMove(currentCell);
        this->link(currentCell, nextCell);
        //this->draw(renderer);
        

        currentCell->setGenerationCell(false);
        currentCell = nextCell;
        visitedCount++;
    }

    this->mGenerated = true;
}

/**
 * Links two cells together
 * @param firstCell The first cell to link
 * @param secondCell The second cell to link
 */
void CBoard::link(shared_ptr<CCell> firstCell, shared_ptr<CCell> secondCell) {

    // link the two cells
    if (firstCell->getPos().y > secondCell->getPos().y) {
        firstCell->setNorth(secondCell);
        secondCell->setSouth(firstCell);
    }
    else if (firstCell->getPos().y < secondCell->getPos().y) {
        firstCell->setSouth(secondCell);
        secondCell->setNorth(firstCell);
    }
    else if (firstCell->getPos().x > secondCell->getPos().x) {
        firstCell->setWest(secondCell);
        secondCell->setEast(firstCell);
    }
    else if (firstCell->getPos().x < secondCell->getPos().x) {
        firstCell->setEast(secondCell);
        secondCell->setWest(firstCell);
    }
}

/**
 * Randomly pick the next move
 * @return shared_ptr<CCell> to the next cell, nullptr if the cell doesn't exist
 */
shared_ptr<CCell> CBoard::getNextGenerationMove(shared_ptr<CCell> currentCell) {
    shared_ptr<CCell> nextCell = nullptr;
    int currentRow = currentCell->getPos().y;
    int currentCol = currentCell->getPos().x;
    vector<shared_ptr<CCell> > moves;

    // get up move
    if (currentRow > 0) {
        std::shared_ptr<CCell> move = mCells[currentRow - 1][currentCol];
        if (!move->isVisited())
            moves.push_back(move);
    }
    // get down move
    if (currentRow < (int)this->mCells.size() - 1) {
        std::shared_ptr<CCell> move = mCells[currentRow + 1][currentCol];
        if (!move->isVisited())
            moves.push_back(move);
    }
    // get right move
    if (currentCol < (int)this->mCells[0].size() - 1) {
        std::shared_ptr<CCell> move = mCells[currentRow][currentCol + 1];
        if (!move->isVisited())
            moves.push_back(move);
    }
    // get left move
    if (currentCol > 0) {
        std::shared_ptr<CCell> move = mCells[currentRow][currentCol - 1];
        if (!move->isVisited())
            moves.push_back(move);
    }
    
    int nextMove = rand() % (int)moves.size();

    return moves[nextMove];
}

/**
 * Check if a cell has already been visited and exists
 * @param currentCell The cell to check
 */
bool CBoard::isBlocked(shared_ptr<CCell> currentCell)
{
    // In order for a cell to be usable it has to exist and not be visited
    int currentRow = currentCell->getPos().y;
    int currentCol = currentCell->getPos().x;

    // check if the cells exist and not visited
    bool usableTop = ((currentRow > 0) && (!this->mCells[currentRow - 1][currentCol]->isVisited()));
    bool usableBottom = ((currentRow < (int)mCells.size() - 1) && (!this->mCells[currentRow + 1][currentCol]->isVisited()));
    bool usableRight = ((currentCol < (int)mCells[0].size() - 1) && (!this->mCells[currentRow][currentCol + 1]->isVisited()));
    bool usableLeft = ((currentCol > 0) && (!this->mCells[currentRow][currentCol - 1]->isVisited()));
    
    return !(usableTop || usableBottom || usableLeft || usableRight);
}

void CBoard::clearVisited()
{
    for (auto row : this->mCells) {
        for (shared_ptr<CCell> cell : row) {
            cell->setVisited(false);
        }
    }
}

/**
 * Draw all the cells on the board
 * @param renderer The renderer to be used for drawing
 */
void CBoard::draw(SDL_Renderer* renderer)
{
    //TODO center board
    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
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
    
    int xOffset = this->mBoardRect.x + this->mBorderSeperation;
    int yOffset = this->mBoardRect.y + this->mBorderSeperation;

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

/**
 * Clears all the cells to their default values
 */
void CBoard::clear() {
    for (auto row : this->mCells) {
        for(auto cell : row) {
            cell->clear();
        }
    }
}

/**
 * Get a random neighbor of a cell
 */
shared_ptr<CCell> CBoard::getNeighbor(shared_ptr<CCell> cell) {
    vector<shared_ptr<CCell> > validNeighbors = {};
    map<string, shared_ptr<CCell> > neighbors = cell->getNeighbors();
    
    // Find neighbors
    for (auto neighborDirectionPair : neighbors) {
        shared_ptr<CCell> neighbor = neighborDirectionPair.second;
        if (neighbor != nullptr && neighbor->isVisited() == 0) {
            validNeighbors.push_back(neighbor);
        }
    }

    if (validNeighbors.size() == 0) {
        return nullptr;
    }
    
    return validNeighbors[rand() % validNeighbors.size()];

}

/**
 * Solves the current maze
 */
void CBoard::solve(SDL_Renderer* renderer)
{
    if (this->mGenerated) {

        this->clearSolution();
        this->clearVisited();

        vector< SDL_Point > stack;
        int visitedCount = 0;
        int boardSize = (int)(this->mCells.size() * this->mCells[0].size());

        shared_ptr<CCell> currentCell = this->mStartingCell;
        shared_ptr<CCell> nextCell = nullptr;
        
        // start solving the board
        while (currentCell->isGoal() == 0) {
            currentCell->setVisited(true);
            currentCell->setSolution(true);
            nextCell = this->getNeighbor(currentCell);

            if (nextCell == nullptr) {
                currentCell->setGenerationCell(false);
                currentCell->setSolution(false);
                currentCell = this->mCells[stack.back().y][stack.back().x];
                stack.pop_back();
                continue;
            }

            stack.push_back(currentCell->getPos());

            currentCell->setGenerationCell(false);
            currentCell = nextCell;
        }

        this->mSolved = true;
        
        this->clearVisited();
    }
}

/**
 * Clears all cells from being a part of the solution
 */
void CBoard::clearSolution()
{
    for (auto row : this->mCells) {
        for (auto cell : row) {
            cell->setSolution(false);
        }
    }
    this->mCurrentUserCell->setCurrentUserCell(false);
    this->mCurrentUserCell = this->mStartingCell;
    this->mCurrentUserCell->setCurrentUserCell(true);
}

/**
 *move a cell in a specific direction
 */
void CBoard::move(string direction) {
    if (this->mSolved) {
        this->clearSolution();
        this->mSolved = false;
    }
    if (this->mCurrentUserCell->getNeighbors()[direction] != nullptr) {
        shared_ptr<CCell> next = this->mCurrentUserCell->getNeighbors()[direction];
        // Clear cell if user backtracks
        if (next->isSolution()) {
            this->mCurrentUserCell->setSolution(false);
        }
        this->mCurrentUserCell->setCurrentUserCell(false);
        this->mCurrentUserCell = next;
        this->mCurrentUserCell->setCurrentUserCell(true);
        this->mCurrentUserCell->setSolution(true);
    }

    
}
