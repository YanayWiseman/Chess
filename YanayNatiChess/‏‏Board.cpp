#include "Board.h"

static const char* INITIAL_BOARD =
"rnbqkbnr"
"pppppppp"
"########"
"########"
"########"
"########"
"PPPPPPPP"
"RNBQKBNR";

/*
	Constructor function to construct the Board object
	input: no input values
	output: no return values
*/

Board::Board()
{
	// initialize the board
	int i = 0, j = 0;

	for (i = 0; i < this->SIZE; i++)
	{
		for (j = 0; j < this->SIZE; j++)
		{
			char ch = INITIAL_BOARD[i * this->SIZE + j];

			this->_squares[i][j] = (ch == HASHTAG) ? nullptr : createPieceFromChar(ch);
		}
	}
}

/*
	Helper function to create the right piece according to its letter representing it
	input: the char
	output: pointer to the piece
*/

Piece* Board::createPieceFromChar(char ch) const
{
	// return the correct piece pointer according to the char
	Color color = islower(ch) ? Color::White : Color::Black;

	switch (tolower(ch))
	{
	case RookCh:
		return new Rook(color, PieceType::TypeRook);

	case KnightCh:
		return new Knight(color, PieceType::TypeKnight);

	case BishopCh:
		return new Bishop(color, PieceType::TypeBishop);

	case QueenCh:
		return new Queen(color, PieceType::TypeQueen);

	case KingCh:
		return new King(color, PieceType::TypeKing);

	case PawnCh:
		return new Pawn(color, PieceType::TypePawn);

	default:
		return nullptr;
	}
}

/*
	Destructor function to destruct the Board object by freeing all of his allocated memoty
	input: no input values
	output: no return values
*/

Board::~Board()
{
	// free the board
	int i = 0, j = 0;

	for (i = 0; i < this->SIZE; i++)
	{
		for (j = 0; j < this->SIZE; j++)
		{
			delete this->_squares[i][j];
			this->_squares[i][j] = nullptr;
		}
	}
}

/*
	function to check if a given poosition is within the board
	input: the row and col index
	output: boolean value, true if in board and false otherwise
*/

bool Board::inBoard(int row, int col) const
{
	// important!!! -> function works by 0 counting index
	return row < this->SIZE && row >= 0 && col >= 0 && col < this->SIZE;
}

/*
	A getter function to get the piece that is in the given indexes
	input: the row and col indexes
	output: the piece in the given position
*/

const Piece* Board::getPiece(int row, int col) const
{
	// check if the position is within the board
	if (!inBoard(row, col))
	{
		return nullptr;
	}

	return this->_squares[row][col];
}

/*
	function to check if the piece that is in the given indexes is empty
	input: the row and col indexes
	output: boolean, true if empty, false otherwise
*/

bool Board::isEmpty(int row, int col) const
{
	return getPiece(row, col) == nullptr;
}

/*
	function to move the piece across the board to the destination position
	input: the move (src and dst)
	output: no return values
	IMPORTANT: this function is called only when we know for certain that the move is legal!!
*/

void Board::movePiece(const Move& move)
{
	int srcRow = move.getSrcRow();
	int srcCol = move.getSrcCol();
	int dstRow = move.getDstRow();
	int dstCol = move.getDstCol();

	Piece* piece = this->_squares[srcRow][srcCol];

	// delete it
	delete this->_squares[dstRow][dstCol];

	// put source piece in destination and clear it
	this->_squares[dstRow][dstCol] = piece;
	this->_squares[srcRow][srcCol] = nullptr;
}

/*
	Method to check if the destination position is occupied with an enemy piece or a nullptr
	input: the movement (object)
	output: boolean, true if there is an enemy, false otherwise
*/

bool Board::isDestValid(const Move& move) const
{
	int srcRow = move.getSrcRow();
	int srcCol = move.getSrcCol();
	int dstRow = move.getDstRow();
	int dstCol = move.getDstCol();

	if (isEmpty(dstRow, dstCol))  // is nullptr
	{
		return true;
	}
	
	// get pieces at src and dst positions
	const Piece* srcPiece = getPiece(srcRow, srcCol);
	const Piece* dstPiece = getPiece(dstRow, dstCol);

	Color srcColor = srcPiece->getColor();
	Color dstColor = dstPiece->getColor();

	if (srcColor != dstColor)  // enemy
	{
		return true;
	}

	return false;  // dst is a piece with the same color of the src
}

/*
	Method to check if the current king is in check position by 
	iterating over all of the pieces and checking if the can harm the king
	input: the current color playing
	output: boolean, true if king is in check and false otherwise
*/

bool Board::isKingInCheck(Color curColor) const
{
	// find current king's position
	int kingRow = -1, kingCol = -1;  // -1 to check if king was found
	int i = 0, j = 0;
	const Piece* curPiece = nullptr;
	// so we don't iterate over the entire board if unneeded
	bool foundFlag = false;

	// iterate over the entire board
	for (i = 0; i < this->SIZE && !foundFlag; i++)
	{
		for (j = 0; j < this->SIZE && !foundFlag; j++)
		{
			curPiece = getPiece(i, j);

			// check if curPiece is not empty, the same color as the king and is a king
			bool isKing = curPiece->getType() == PieceType::TypeKing;
			bool sameColor = curPiece->getColor() == curColor;

			if (curPiece && sameColor && isKing)
			{
				kingRow = i;
				kingCol = j;
				foundFlag = true;
			}
		}
	}

	// if king wasn't found
	if (kingRow == -1 || kingCol == -1)
	{
		// exception
		return false;
	}

	for (i = 0; i < this->SIZE; i++)
	{
		for (j = 0; j < this->SIZE; j++)
		{
			curPiece = getPiece(i, j);

			// is an enemy
			if (curPiece && curPiece->getColor() != curColor)
			{
				// to check if the current piece can reach the king, we make a move for it
				Move attackMove(i, j, kingRow, kingCol);

				if (curPiece->canMove(attackMove, *this))
				{
					return true;
				}
			}
		}
	}

	return false;
}

/*
	Operator method - deep copy of the board
	input: the other board to copy to
	output: reference to the board
*/

Board& Board::operator=(const Board& other)
{
	if (this == &other)  // self copy check
	{
		return *this;
	}

	int i = 0, j = 0;

	// delete this's values
	for (i = 0; i < this->SIZE; i++)
	{
		for (j = 0; j < this->SIZE; j++)
		{
			if (this->_squares[i][j])
			{
				delete this->_squares[i][j];
				this->_squares[i][j] = nullptr;
			}
		}
	}

	// copy using copy c'tor that is in piece (pure)	
	for (i = 0; i < this->SIZE; i++)
	{
		for (j = 0; j < this->SIZE; j++)
		{
			if (this->_squares[i][j])
			{
				this->_squares[i][j] = other._squares[i][j]->clone();
			}
		}
	}
}