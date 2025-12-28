#include "Bishop.h"
#include "MovementCheck.h"
/*
	Constructor method to construct the bishop object
	input: the color of the piece and its type
	output no return values
*/

Bishop::Bishop(Color color, PieceType type) : Piece(color, type)
{

}

/*
	Copy c'tor to deep copy the piece
	input: no input values
	output: pointer to the piece
*/

Piece* Bishop::clone() const
{
	Bishop* newBishop = new Bishop(*this);
	newBishop->_hasMoved = this->_hasMoved;
	return newBishop;
}

/*
	This function handles the logic for the Bishops movement
	input: Wanted move and current board
	output: Is the move possible for a Bishop to proform
*/
bool Bishop::canMove(const Move& move, const Board& board) const 
{ 
	bool checkBishopMove = MovementCheck::isDiagonalPathClear(move, board);
	return checkBishopMove;
}
