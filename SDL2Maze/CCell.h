#pragma once

#include <utility>
#include <SDL.h>

class CCell
{
public:
	CCell(int x, int y, bool blocked = false);

	CCell() = delete;
	CCell(const CCell &) = delete;
	CCell operator=(CCell&) = delete;
	
	/**
	 * Retrive the position of the cell in the board
	 * @returns: pair<int, int> The corrdinates of the cell
	 */
	std::pair<int, int> getPos() { return std::make_pair(mX, mY); }

	void draw(SDL_Rect cellRect, SDL_Renderer* renderer);


private:
			
	int mX;				///< X coordinate of the cell relative to the board
	int mY;				///< Y coordinate of the cell relative to the board

	bool mBlocked;		///< Specify if the cell is blocked or not
};

