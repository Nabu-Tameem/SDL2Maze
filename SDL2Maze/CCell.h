#pragma once

#include <utility>
#include <SDL.h>

class CCell
{
public:
	CCell();
	CCell(const CCell &) = delete;
	CCell operator=(CCell&) = delete;

	void draw(SDL_Rect cellRect, SDL_Renderer* renderer, int xOffset, int yOffset);
	/**
	 * Set the block state of the cell
	 * @param isBlocked The block state of the cell, true if blocked, false otherwise
	 */
	void setBlocked(bool isBlocked) { mBlocked = isBlocked; }
	/**
	 * get the block state of the cell
	 * @return bool The block state of the cell
	 */
	bool isBlocked() { return mBlocked; }


private:

	bool mBlocked = false;		///< Specify if the cell is blocked or not
};

