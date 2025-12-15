#include "Queen.h"

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

// just for testing (nati, edit this)
bool Queen::canMove(const Move& move, const Board& board) const { return true; }