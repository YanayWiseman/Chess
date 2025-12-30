#include "Bishop.h"
#include "MovementCheck.h"
#include "Board.h"

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
	Bishop* newBishop = new Bishop(*this);
	newBishop->_hasMoved = this->_hasMoved;
	return newBishop;
}

/*
	This function handles the logic for the Bishops movement
	input: Wanted move and current board
	output: Is the move possible for a Bishop to proform
*/
bool Bishop::canMove(const Move& move, const Board& board) const 
{ 
	bool checkBishopMove = MovementCheck::isDiagonalPathClear(move, board);
	return checkBishopMove;
}


/*
	This function generates all pseudo legel moves for the bishop
	input: current board current place(row, col) 
	output: vector of the moves
*/
std::vector<Move> Bishop::getPseudoLegalMoves(const Board& board, int srcRow, int srcCol) const
{
	int dir = 0;
	std::vector<Move> moves;

	for (dir = 0; dir < DIR_COUNT; dir++)
	{
		bool blocked = false;
		int step = 1;

		while (!blocked)
		{
			int r = srcRow + DIRS[dir][0] * step;
			int c = srcCol + DIRS[dir][1] * step;

			if (!board.inBoard(r, c))
			{
				blocked = true;
			}
			else
			{
				const Piece* target = board.getPiece(r, c);

				if (!target)
				{
					moves.emplace_back(srcRow, srcCol, r, c);
				}
				else
				{
					if (target->getColor() != this->getColor())
					{
						moves.emplace_back(srcRow, srcCol, r, c);
					}
					blocked = true;
				}
			}

			step++;
		}
	}
	return moves;
}
