#include "Knight.h"

/*
	Constructor method to construct the Knight object
	input: the color of the piece and its type
	output no return values
*/

Knight::Knight(Color color, PieceType type) : Piece(color, type)
{

}

/*
	Copy c'tor to deep copy the piece
	input: no input values
	output: pointer to the piece
*/

Piece* Knight::clone() const
{
	return new Knight(*this);
}