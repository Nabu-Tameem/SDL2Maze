#include <SDL.h>
#include "CCell.h"

/**
 * Constructor
 * @param x The x coordinate of the cell
 * @param y The y coordinate of the cell
 */
CCell::CCell(int x, int y, bool blocked = false)
{
	this->mX = x;
	this->mY = y;
    this->mBlocked = blocked;
}

/**
 * Draw the cell using a specified size and offset for the relative coordinates
 * @param size The length of one side of the cell which is a square
 * @param xOffset The amount of pixels to offset this cell by in the x coordinate
 * @param yOffset The amount of pixels to offset this cell by in the y coordinate
 */
void CCell::draw(int size, int xOffset, int yOffset)
{
    
}
