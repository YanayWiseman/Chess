#include "Rook.h"

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