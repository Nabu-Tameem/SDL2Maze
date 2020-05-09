#pragma once
class CBoard
{
public:
	CBoard(int rows, int cols);

	/** default constructor, deleted */
	CBoard() = delete;
	/** copy constructor, deleted */
	CBoard(const CBoard&) = delete;
	/** assignment constructor, deleted */
	CBoard operator=(CBoard&) = delete;

private:

};

