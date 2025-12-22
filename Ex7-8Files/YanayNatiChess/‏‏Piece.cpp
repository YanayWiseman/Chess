#include "Piece.h"
#include "Board.h"
#include "Move.h"
#include "MovementCheck.h"

/*
	Constructor method to construct the Piece object
	input: the color of the piece and its type
	output no return values
*/

Piece::Piece(Color color, PieceType type) : _color(color), _type(type), _hasMoved(false)
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

/*
	Getter mehtod to get the boolean value representing whether the piece has moved yet or not
	input: no input values
	output: whether the piece has moved yet or not
*/

bool Piece::hasMoved() const
{
	return this->_hasMoved;
}

/*
	Setter mehtod to set the boolean value representing whether the piece has moved yet or not
	input: whether the piece has moved yet or not
	output: no return values
*/

void Piece::setHasMoved(bool moved)
{
	this->_hasMoved = moved;
}