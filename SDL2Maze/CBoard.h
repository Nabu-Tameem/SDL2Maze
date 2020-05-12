#pragma once

#include <memory>
#include <vector>
#include <map>
#include <string>
#include <SDL.h>

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

	void generate();
	void draw(SDL_Renderer* renderer);

	/**
	 * Sets a cell as a goal cell
	 * @param x The col the cell is in
	 * @param y The row the cell is in
	 * @param state The state of the cell as goal
	 */
	void setGoal(int x, int y, bool state) { mCells[y][x]->setGoal(true); }

	/**
	 * get The last row in the board
	 * @returns int Index of the last row in the board
	 */
	int maxRow() { return int(mCells.size()) - 1; }
	/**
	 * get The last col in the board
	 * @returns int Index of the last col in the board
	 */
	int maxCol() { return int(mCells[0].size()) - 1; }

	void clear();
	void solve();
	void clearSolution();

	void move(std::string direction);
	

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
	/// The current cell the user is on
	std::shared_ptr<CCell> mCurrentUserCell;

	bool mGenerated = false; /// indicate if a maze has already been generated

	void link(std::shared_ptr<CCell> firstCell, std::shared_ptr<CCell> secondCell);
	std::shared_ptr<CCell> getNextMove(std::shared_ptr<CCell> currentCell);
	bool isBlocked(std::shared_ptr<CCell>);

};

