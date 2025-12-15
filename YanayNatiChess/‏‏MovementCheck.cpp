#include "MovementCheck.h"
#include "Board.h"
#include "Move.h"
#include <cmath>

/*
	This function checks if there are no pieces in the moves path
	input: Wanted move, Current board
	output: Is the path clear, if it is true if it isn't false
*/

bool MovementCheck::isStraightPathClear(const Move& move, const Board& board) 
{
	int startRow = move.getSrcRow();
	int startCol = move.getSrcCol();
	int endRow = move.getDstRow();
	int endCol = move.getDstCol();

	bool isHorizontal = (startRow == endRow);
	bool isVertical = (startCol == endCol);

	if (!isHorizontal && !isVertical) 
	{
		return false; // later will add exception
	}

	// Horizontal movement
	if (isHorizontal) 
	{
		int stepCol = (endCol > startCol) ? 1 : -1;
		int currentCol = startCol + stepCol;

		while (currentCol != endCol) 
		{
			if (!board.isEmpty(startRow, currentCol))
			{
				return false;
			}
			currentCol += stepCol;
		}
	}

	// Vertical movement

	else 
	{
		int stepRow = (endRow > startRow) ? 1 : -1;
		int currentRow = startRow + stepRow;

		while (currentRow != endRow) 
		{
			if (!board.isEmpty(currentRow, startCol))
			{
				return false;
			}
			currentRow += stepRow;
		}
	}

	return true; // Path clear
}


/*
	This fucntion if there are no pieces in the moves path diagonally
	input: Wanted move, Current board
	output: Is the path clear, if it is true if it isn't false
*/
bool MovementCheck::isDiagonalPathClear(const Move& move, const Board& board) 
{
	int startRow = move.getSrcRow();
	int startCol = move.getSrcCol();
	int endRow = move.getDstRow();
	int endCol = move.getDstCol();

	if (abs(endRow - startRow) != abs(endCol - startCol)) 
	{
		return false; // Will add an excepetion
	}

	int stepCol = (endCol > startCol) ? 1 : -1;
	int stepRow = (endRow > startRow) ? 1 : -1;

	int currentCol = startCol + stepCol;
	int currentRow = startRow + stepRow;

	// We can check only one diraction as on a diagonal they will reach at the same time
	while (currentRow != endRow) 
	{
		if (!board.isEmpty(currentRow, currentCol))
		{
			return false;
		}

		currentCol += stepCol;
		currentRow += stepRow;
	}

	return true;  // Path clear
}