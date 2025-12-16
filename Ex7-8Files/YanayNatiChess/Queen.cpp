#include "Queen.h"
#include "MovementCheck.h"

/*
	Constructor method to construct the Queen object
	input: the color of the piece and its type
	output no return values
*/

Queen::Queen(Color color, PieceType type) : Piece(color, type)
{

}

/*
	Copy c'tor to deep copy the piece
	input: no input values
	output: pointer to the piece
*/

Piece* Queen::clone() const
{
	return new Queen(*this);
}

/*
	This function handles the logic for the Queens movement
	input: Wanted move and current board
	output: Is the move possible for a Queen to proform
*/
bool Queen::canMove(const Move& move, const Board& board) const 
{ 
	bool checkStraight = MovementCheck::isStraightPathClear(move, board);
	bool checkDiagonal = MovementCheck::isDiagonalPathClear(move, board);

	// Queen can move either diagonally or straight
	bool checkQueenMove = (checkStraight || checkDiagonal);

	return checkQueenMove;
}