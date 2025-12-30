#include "Queen.h"
#include "MovementCheck.h"
#include "Board.h"

/*
	Constructor method to construct the Queen object
	input: the color of the piece and its type
	output no return values
*/

Queen::Queen(Color color, PieceType type) : Piece(color, type)
{

}

/*
	Copy c'tor to deep copy the piece
	input: no input values
	output: pointer to the piece
*/

Piece* Queen::clone() const
{
	Queen* newQueen = new Queen(*this);
	newQueen->_hasMoved = this->_hasMoved;
	return newQueen;
}

/*
	This function handles the logic for the Queens movement
	input: Wanted move and current board
	output: Is the move possible for a Queen to proform
*/
bool Queen::canMove(const Move& move, const Board& board) const 
{ 
	bool checkStraight = MovementCheck::isStraightPathClear(move, board);
	bool checkDiagonal = MovementCheck::isDiagonalPathClear(move, board);

	// Queen can move either diagonally or straight
	bool checkQueenMove = (checkStraight || checkDiagonal);

	return checkQueenMove;
}

/*
	This function generates all pseudo legel moves for the queen
	input: current board current place(row, col)
	output: vector of the moves
*/
std::vector<Move> Queen::getPseudoLegalMoves(const Board& board, int srcRow, int srcCol) const
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
