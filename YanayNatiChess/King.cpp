#include "King.h"

/*
	Constructor method to construct the King object
	input: the color of the piece and its type
	output no return values
*/

King::King(Color color, PieceType type) : Piece(color, type)
{

}

/*
	Copy c'tor to deep copy the piece
	input: no input values
	output: pointer to the piece
*/

Piece* King::clone() const
{
	return new King(*this);
}

// just for testing (nati, edit this)
bool King::canMove(const Move& move, const Board& board) const { return true; }