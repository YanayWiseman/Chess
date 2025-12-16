#include "King.h"
#include "Move.h"

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

/*
	This function handles the logic for the Kings movement
	input: Wanted move and current board
	output: Is the move possible for a King to proform
*/
bool King::canMove(const Move& move, const Board& board) const 
{ 
	// Unpack wanted move
	int startRow = move.getSrcRow();
	int startCol = move.getSrcCol();
	int endRow = move.getDstRow();
	int endCol = move.getDstCol();

	// Get the length in each diraction
	int absRowDiff = abs(endRow - startRow);
	int absColDiff = abs(endCol - startCol);

	// King can move only one square in any diraction
	bool checkKingMove = (MAX_SQUARES >= absRowDiff ) && (MAX_SQUARES >= absColDiff);
	return checkKingMove;
}