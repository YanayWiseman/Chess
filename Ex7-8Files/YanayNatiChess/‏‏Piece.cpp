#include "Piece.h"
#include "Board.h"
#include "Move.h"
#include "MovementCheck.h"

/*
	Constructor method to construct the Piece object
	input: the color of the piece and its type
	output no return values
*/

Piece::Piece(Color color, PieceType type) : _color(color), _type(type)
{

}

/*
	Getter method to get the color of the current player
	input: no input values
	output: the color
*/

Color Piece::getColor() const
{
	return this->_color;
}

/*
	Getter method to get the type of the piece
	input: no input values
	output: the type
*/

PieceType Piece::getType() const
{
	return this->_type;
}