#include "Pawn.h"

/*
	Constructor method to construct the Pawn object
	input: the color of the piece and its type
	output no return values
*/

Pawn::Pawn(Color color, PieceType type) : Piece(color, type)
{

}

/*
	Copy c'tor to deep copy the piece
	input: no input values
	output: pointer to the piece
*/

Piece* Pawn::clone() const
{
	return new Pawn(*this);
}

// just for testing (nati, edit this)
bool Pawn::canMove(const Move& move, const Board& board) const { return true; }