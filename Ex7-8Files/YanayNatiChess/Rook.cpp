#include "Rook.h"
#include "MovementCheck.h"

/*
	Constructor method to construct the Rook object
	input: the color of the piece and its type
	output no return values
*/

Rook::Rook(Color color, PieceType type) : Piece(color, type)
{

}

/*
	Copy c'tor to deep copy the piece
	input: no input values
	output: pointer to the piece
*/

Piece* Rook::clone() const
{
	Rook* newRook = new Rook(*this);
	newRook->_hasMoved = this->_hasMoved;
	return newRook;
}

/*
	This function handles the logic for the Rooks movement
	input: Wanted move and current board
	output: Is the move possible for a Rooks to proform
*/

bool Rook::canMove(const Move& move, const Board& board) const 
{
	// Rook can only move in a straight line
	bool checkRookMove = MovementCheck::isStraightPathClear(move, board);
	return checkRookMove;
}


/*
	This function generates all pseudo legel moves for the rook
	input: current board current place(row, col) 
	output: vector of the moves
*/
std::vector<Move> Rook::getPseudoLegalMoves(const Board& board, int srcRow, int srcCol) const
{
	int dir = 0;
	std::vector<Move> moves;

	for (dir = 0; dir < DIR_COUNT; dir++) 
	{
		bool blocked = false;
		int step = 1;

		while(!blocked) 
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
