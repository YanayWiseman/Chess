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

/*
	A getter function to get the piece that is in the given indexes
	input: the row and col indexes
	output: the piece in the given position
*/

const Piece* Board::getPiece(int row, int col) const
{
	// check if the position is within the board
	if (!inBoard(row, col))
	{
		return nullptr;
	}

	return this->_squares[row][col];
}

/*
	function to check if the piece that is in the given indexes is empty
	input: the row and col indexes
	output: boolean, true if empty, false otherwise
*/

bool Board::isEmpty(int row, int col) const
{
	return getPiece(row, col) == nullptr;
}

/*
	function to move the piece across the board to the destination position
	input: the move (src and dst)
	output: no return values
	IMPORTANT: this function is called only when we know for certain that the move is legal!!
*/

void Board::movePiece(const Move& move)
{
	int srcRow = move.getSrcCol();
	int srcCol = move.getSrcCol();
	int dstRow = move.getDstRow();
	int dstCol = move.getDstCol();

	Piece* piece = this->_squares[srcRow][srcCol];

	// delete it
	
}