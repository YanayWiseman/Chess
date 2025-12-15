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