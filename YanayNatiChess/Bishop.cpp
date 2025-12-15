#include "Bishop.h"

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
	return new Bishop(*this);
}