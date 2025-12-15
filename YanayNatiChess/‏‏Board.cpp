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

/*
	Destructor function to destruct the Board object by freeing all of his allocated memoty
	input: no input values
	output: no return values
*/

Board::~Board()
{
	// free the board
	int i = 0, j = 0;

	for (i = 0; i < this->SIZE; i++)
	{
		for (j = 0; j < this->SIZE; j++)
		{
			delete this->_squares[i][j];
			this->_squares[i][j] = nullptr;
		}
	}
}

/*
	function to check if a given poosition is within the board
	input: the row and col index
	output: boolean value, true if in board and false otherwise
*/

bool Board::inBoard(int row, int col) const
{
	// important!!! -> function works by 0 counting index
	return row < this->SIZE && row >= 0 && col >= 0 && col < this->SIZE;
}