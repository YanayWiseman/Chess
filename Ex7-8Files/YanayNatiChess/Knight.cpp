#include "Knight.h"
#include "Move.h"
#include "Board.h"
#include <cmath>

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
	Knight* newKnight = new Knight(*this);
	newKnight->_hasMoved = this->_hasMoved;
	return newKnight;
}


/*
	This function handles the logic for the Knights movement
	input: Wanted move and current board
	output: Is the move possible for a knight to proform
*/
bool Knight::canMove(const Move& move, const Board& board) const 
{
	// Unpack wanted move
	int startRow = move.getSrcRow();
	int startCol = move.getSrcCol();
	int endRow = move.getDstRow();
	int endCol = move.getDstCol();

	// Get the length in each diraction
	int absRowDiff = abs(endRow - startRow);
	int absColDiff = abs(endCol - startCol);

	// Check if a valid knight move occured (L Shaped Move)
	bool checkRowLong = (KNIGHT_LONG == absRowDiff ) && (KNIGHT_SHORT == absColDiff);
	bool checkColLong = (KNIGHT_LONG == absColDiff ) && (KNIGHT_SHORT == absRowDiff);

	bool checkKnightMove = (checkRowLong || checkColLong);
	return checkKnightMove;
}

/*
	This function generates all pseudo legel moves for the knight
	input: current board current place(row, col)
	output: vector of the moves
*/
std::vector<Move> Knight::getPseudoLegalMoves(const Board& board, int srcRow, int srcCol) const
{
	int i = 0;
	std::vector<Move> moves;

	for (int i = 0; i < MOVE_COUNT; i++)
	{
		int r = srcRow + MOVES[i][0];
		int c = srcCol + MOVES[i][1];

		if (board.inBoard(r, c))
		{
			const Piece* target = board.getPiece(r, c);

			if (!target || target->getColor() != getColor())
			{
				moves.emplace_back(srcRow, srcCol, r, c);
			}
		}
	}
	return moves;
}
