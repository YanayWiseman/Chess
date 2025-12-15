#include "Board.h"
#include "Piece.h"
#include "Move.h"

/*
	Constructor function to construct the Board object
	input: no input values
	output: no return values
*/

Board::Board()
{
	// initialize the board
	int i = 0, j = 0;

	for (i = 0; i < this->SIZE; i++)
	{
		for (j = 0; j < this->SIZE; j++)
		{
			this->_squares[i][j] = nullptr;
		}
	}
}