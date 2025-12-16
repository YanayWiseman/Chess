#include "Pawn.h"
#include "Move.h"
#include "Board.h"

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

/*
	This function handles the logic for the Pawns movement
	input: Wanted move and current board
	output: Is the move possible for a Pawn to proform
*/
bool Pawn::canMove(const Move& move, const Board& board) const 
{ 
	// Unpack wanted move
	int startRow = move.getSrcRow();
	int startCol = move.getSrcCol();
	int endRow = move.getDstRow();
	int endCol = move.getDstCol();

	// Get the length in each diraction
	int absRowDiff = abs(endRow - startRow);
	int absColDiff = abs(endCol - startCol);

	int moveDirection = (this->_color == Color::White) ? UP : DOWN;

	// Normal move conditions
	bool correctColumn = (startCol == endCol);
	bool correctRow = ((endRow - startRow) == moveDirection);
	bool destinationEmpty = board.isEmpty(endRow, endCol);


	bool forwardOne = correctColumn && correctRow && destinationEmpty;
	return forwardOne;
}