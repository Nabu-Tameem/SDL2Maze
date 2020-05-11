#pragma once

#include <utility>
#include <memory>

#include "bin/include/SDL2/SDL.h"

class CCell
{
public:
	CCell();
	CCell(const CCell &) = delete;
	CCell operator=(CCell&) = delete;

	void draw(SDL_Rect cellRect, SDL_Renderer* renderer, int xOffset, int yOffset, int seperation);
	///**
	// * Sets the block state of the cell
	// * @param isBlocked The block state of the cell, true if blocked, false otherwise
	// */
	//void setBlocked(bool blocked) { mBlocked = blocked; }
	///**
	// * gets the block state of the cell
	// * @return bool The block state of the cell
	// */
	//bool isBlocked() { return mBlocked; }

	/**
	 * sets the visit state of the cell
	 * @param visited The visit state of the cell
	 */
	void setVisited(bool visited) { mVisited = visited; }

	/**
	 * checks if the cell has been visited
	 * @returns bool If the cell has been visited
	 */
	bool isVisited() { return mVisited; }

	/**
	 * Sets this cell as the current maze generation cell
	 * @param generation Represents if the cell is the current maze generation cell
	 */
	void setGenerationCell(bool generation) { mCurrentGenerationCell = generation; }

	/**
	 * Gets if the cell is the current maze generation cell
	 * @returns bool If the cell is the current generation cell
	 */
	bool isGenerationCell() { return mCurrentGenerationCell; }

private:

	/*bool mBlocked = false;		///< Specify if the cell is blocked or not*/
	bool mVisited = false;

	// Pointer to the cells that are connected to this cell in the maze.
	std::shared_ptr<CCell> mNorthCell = nullptr;
	std::shared_ptr<CCell> mEastCell = nullptr;
	std::shared_ptr<CCell> mSouthCell = nullptr;
	std::shared_ptr<CCell> mWestCell = nullptr;

	bool mCurrentGenerationCell = false; ///< Indicates if the cell is the current target during the maze generation


};

