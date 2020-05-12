#pragma once

#include <utility>
#include <memory>
#include <string>

#include "bin/include/SDL2/SDL.h"

class CCell
{
public:
	CCell() = delete;
	CCell(const CCell &) = delete;
	CCell operator=(CCell&) = delete;

	CCell(int row, int col);

	void draw(SDL_Rect cellRect, SDL_Renderer* renderer, int xOffset, int yOffset, int seperation);

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

	/**
	 * Sets the cell as the starting cell
	 * @param starting Represents if the cell is a starting cell or not
	 */
	void setStarting(bool starting) { mStarting = starting; }

	/**
	 * Sets the cell as the goal cell
	 * @param goal Represents if the cell is a goal cell or not
	 */
	void setGoal(bool goal) { mGoal = goal; }

	/**
	 * Checks if the cell is a starting cell
	 * @return bool If the cell is a starting cell
	 */
	bool isStarting() { return mStarting; }

	/**
	 * Checks if the cell is a goal cell
	 * @return bool If the cell is a goal cell
	 */
	bool isGoal() { return mGoal; }
	
	/**
	 * Gets the coordinates of the cell on the board
	 * @returns SDL_Point A point representing the position of the cell
	 */
	SDL_Point getPos() { return mPos; }

	std::map<std::string, std::shared_ptr<CCell> > getNeighbors();

	/**
	 * Sets this cells north facing neighbor
	 * @param cell Pointer to the north facing cell
	 */
	void setNorth(std::shared_ptr<CCell> cell) { mNorthCell = cell; }
	/**
	 * Sets this cells south facing neighbor
	 * @param cell Pointer to the soyth facing cell
	 */
	void setSouth(std::shared_ptr<CCell> cell) { mSouthCell = cell; }
	/**
	 * Sets this cells east facing neighbor
	 * @param cell Pointer to the east facing cell
	 */
	void setEast(std::shared_ptr<CCell> cell) { mEastCell = cell; }
	/**
	 * Sets this cells west facing neighbor
	 * @param cell Pointer to the west facing cell
	 */
	void setWest(std::shared_ptr<CCell> cell) { mWestCell = cell; }

	/**
	 * Sets a cell as stopped, in other words a cell that gets blocked during generation and
	 * the board needs to back track
	 * @param stopped The stopping state of the cell
	 */
	void setStopped(bool stopped) { mStopped = true; }
private:
	/// Column and row of the cell
	SDL_Point mPos;

	/// Indicate if the cell has been visited by the maze generator
	bool mVisited = false;							

	/// Pointer to the cells that are connected to this cell in the maze.
	std::shared_ptr<CCell> mNorthCell = nullptr;
	std::shared_ptr<CCell> mEastCell = nullptr;
	std::shared_ptr<CCell> mSouthCell = nullptr;
	std::shared_ptr<CCell> mWestCell = nullptr;
	
	/// Indicates if the cell is the current target during the maze generation
	bool mCurrentGenerationCell = false;	
	/// Indicates if this cell is the starting cell
	bool mStarting = false;
	/// Indicates if the cell is the goal cell
	bool mGoal = false;

	bool mStopped = false;
};

