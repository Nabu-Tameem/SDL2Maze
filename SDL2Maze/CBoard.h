#pragma once

#include <memory>
#include <vector>
#include <map>
#include <string>

#include "bin/include/SDL2/SDL.h"
#include "CCell.h"

class CBoard
{
public:
	CBoard(int rows, int cols, int screenWidth = 800, int screenHeight = 600);

	/** default constructor, deleted */
	CBoard() = delete;
	/** copy constructor, deleted */
	CBoard(const CBoard&) = delete;
	/** assignment constructor, deleted */
	CBoard operator=(CBoard&) = delete;

	void generateCell();
	void draw(SDL_Renderer* renderer);

	/**
	 * Set the distance between the board and the border
	 * @param distance The distance between the board and the border
	 */
	void setBoardSeperation(int distance) { mBoardSeperation = distance; }
	/**
	 * Set the distance between the cell
	 * @param distance The distance between the cell
	 */
	void setCellSeperation(int distance) { mCellSeperation = distance; }
	/**
	 * Set the boarder width
	 * @param width The new width of the boarder
	 */
	void setBorderWidth(int width) { mBorderWidth = width; }


	// REMOVED NO NEED FOR IT AND COULD CAUSE MISS USE
	/**
	 * Sets a cell as a starting cell
	 * @param x The col the cell is in
	 * @param y The row the cell is in
	 * @param state The state of the cell as starting
	 */
	//void setStarting(int x, int y, bool state) { mCells[y][x]->setStarting(true); }

	/**
	 * Sets a cell as a goal cell
	 * @param x The col the cell is in
	 * @param y The row the cell is in
	 * @param state The state of the cell as goal
	 */
	void setGoal(int x, int y, bool state) { mCells[y][x]->setGoal(true); }

private:
	/// All the cells contained in the board
	std::vector<std::vector<std::shared_ptr<CCell> > > mCells;
	/// Rectangle representing a single cell, used for drawing the cells
	SDL_Rect mCellRect;

	/// Rectangle used to draw the border
	SDL_Rect mBorderRect;
	/// Rectangle used to make the border hollow
	SDL_Rect mBoardRect;

	/// distance from border to the cells
	int mBoardSeperation = 5;
	/// distance between cells
	int mCellSeperation = 2;
	/// width of the border
	int mBorderWidth = 5;
	/// The cell to start the generation with, also the boards starting cell
	std::shared_ptr<CCell> mStartingCell;
};

