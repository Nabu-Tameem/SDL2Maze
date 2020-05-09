#pragma once

#include <SDL.h>
#include <memory>
#include <vector>

#include "CCell.h"

class CBoard
{
public:
	CBoard(int rows, int cols, int screenHeight = 600, int screenWidth = 800);

	/** default constructor, deleted */
	CBoard() = delete;
	/** copy constructor, deleted */
	CBoard(const CBoard&) = delete;
	/** assignment constructor, deleted */
	CBoard operator=(CBoard&) = delete;

	void draw(SDL_Renderer* renderer);

private:
	/// All the cells contained in the board
	std::vector<std::shared_ptr<CCell> > mCells;
	/// Rectangle representing a single cell, used for drawing the cells
	SDL_Rect mCellRect;

	int mCellXOffset;
	int mCellYOffset;

};

