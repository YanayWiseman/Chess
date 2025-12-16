#include "Rook.h"
#include "MovementCheck.h"

/*
	Constructor method to construct the Rook object
	input: the color of the piece and its type
	output no return values
*/

Rook::Rook(Color color, PieceType type) : Piece(color, type)
{

}

/*
	Copy c'tor to deep copy the piece
	input: no input values
	output: pointer to the piece
*/

Piece* Rook::clone() const
{
	return new Rook(*this);
}

/*
	This function handles the logic for the Rooks movement
	input: Wanted move and current board
	output: Is the move possible for a Rooks to proform
*/
bool Rook::canMove(const Move& move, const Board& board) const 
{
	// Rook can only move in a straight line
	bool checkRookMove = MovementCheck::isStraightPathClear(move, board);
	return checkRookMove;
}