#include "MovementCheck.h"
#include "Board.h"
#include "Move.h"


bool isStraightPathClear(const Move& move, const Board& board) 
{
	int startRow = move.getSrcRow();
	int startCol = move.getSrcCol();
	int endRow = move.getDstRow();
	int endCol = move.getDstCol();

	// Moving horizontally
	if (startRow == endRow) 
	{
		int direction = (endCol > startCol) ? 1 : -1;
		int currentCol = startCol + direction;

		while (currentCol != endCol) 
		{
			// Check each square between start and end
			if (!board.isEmpty(startRow, currentCol)) 
			{
				return false;  // Path blocked
			}
			currentCol += direction;
		}
		return true;  // Path is clear
	}
	// Moving vertically (same column)  
	else if (startCol == endCol) 
	{
		int direction = (endRow > startRow) ? 1 : -1;
		int currentRow = startRow + direction;

		while (currentRow != endRow) 
		{
			if (!board.isEmpty(currentRow, startCol)) 
			{
				return false;  // Path blocked
			}
			currentRow += direction;
		}
		return true;  // Path is clear
	}

	// Not a straight line move
	else 
	{
		return false;  // Or throw exception
	}
}
