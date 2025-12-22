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

	// check for castling attempt (king moves 2 squares horizontally)
	bool castlingAttempt = (absRowDiff == 0) && (absColDiff == CASTLING_DISTANCE);

	if (castlingAttempt)
	{
		return canCastle(move, board);
	}

	return checkKingMove;
}

/*
	function to check if the king can castle or not
	input: the move made by the king and the board
	output: boolean, true if king can castle and false otherwise
*/

bool King::canCastle(const Move& move, const Board& board) const
{
	int srcRow = move.getSrcRow();
	int srcCol = move.getSrcCol();
	int dstRow = move.getDstRow();
	int dstCol = move.getDstCol();

	// to check if the king can castle, it must follow 3 important rules!
	// I isolated all of the cases for easier reading and understanding
	// Rule 1: king must not have moved
	if (this->_hasMoved)
	{
		return false;
	}

	// Rule 2: king must not be in check currently
	if (board.isKingInCheck(this->_color))
	{
		return false;
	}
	
	// find which side: king side (right) or queen side (left)
	bool kingSide = (dstCol > srcCol);  // right
	int rookCol = kingSide ? (board.getSize() - 1) : 0;

	// check if rook exists and hasn't moved
	const Piece* rook = board.getPiece(srcRow, rookCol);

	if (!rook || rook->getType() != PieceType::TypeRook || rook->hasMoved())
	{
		return false;
	}

	// make sure that the path is clear between king and rook
	int direction = kingSide ? 1 : -1;
	int checkCol = srcCol + direction;
	int endCheckCol = rookCol;
	
	while (checkCol != endCheckCol)
	{
		if (!board.isEmpty(srcRow, checkCol))
		{
			return false;  // found piece inbetween
		}
		checkCol += direction;
	}

	// Rule 3: king cannot castle through check
	// check the squares the king passes through (including destination)
	int col = 0;
	for (col = srcCol + direction; col != dstCol + direction; col += direction)
	{
		// simulate king moving to this position
		Move testMove(srcRow, srcCol, srcRow, col);

		if (MovementCheck::causesCheck(testMove, board, this->_color))
		{
			return false;  // king would be in check at this square
		}
	}
	
	// met all castling conditions and is allowed to castle
	return true;
}

