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
	This function prints the board
	input: none
	output: none
*/
void Board::printBoard() const
{
	int row = 0, col = 0;
	for (row = 0; row < SIZE; row++)
	{
		for (col = 0; col < SIZE; col++)
		{
			const Piece* piece = this->_squares[row][col];

			char outChar = HASHTAG;

			if (piece)
			{
				switch (piece->getType())
				{
				case PieceType::TypeRook:
					outChar = RookCh;
					break;

				case PieceType::TypeKnight:
					outChar = KnightCh;
					break;

				case PieceType::TypeBishop:
					outChar = BishopCh;
					break;

				case PieceType::TypeQueen:
					outChar = QueenCh;
					break;

				case PieceType::TypeKing:
					outChar = KingCh;
					break;

				case PieceType::TypePawn:
					outChar = PawnCh;
					break;
				}

				// Black pieces are uppercase
				if (piece->getColor() == Color::Black)
				{
					outChar = toupper(outChar);
				}
			}

			std::cout << outChar;

			if (col < (SIZE - 1))
			{
				std::cout << ' ';
			}
		}

		std::cout << std::endl;
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
	Getter method to get the last move performed in the chess game
	input: no input values
	output: the move made
*/

const Move* Board::getLastMove() const
{
	// if there was a last move return it and if not return nullptr
	return this->_hasLastMove ? &(this->_lastMove) : nullptr;
}

/*
	function to set the last move made in the chess game
	input: the move made
	output: no return values
*/

void Board::setLastMove(const Move& move)
{
	this->_lastMove = move;
	this->_hasLastMove = true;
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

	// first, detect en passant
	bool isEnPassant = false;
	int enPassantCapturedRow = -1;
	int enPassantCapturedCol = -1;

	// handle en passant
	if (piece && piece->getType() == PieceType::TypePawn)
	{
		int rowDifference = dstRow - srcRow;
		int colDifference = dstCol - srcCol;

		// diagonal move into empty square means possible en passant
		if (std::abs(colDifference) == 1 && isEmpty(dstRow, dstCol))
		{
			// get the last move's fields
			const Move* lastMove = getLastMove();

			if (lastMove)
			{
				int lastMoveSrcRow = lastMove->getSrcRow();
				int lastMoveDstRow = lastMove->getDstRow();
				int lastMoveDstCol = lastMove->getDstCol();

				const Piece* lastPiece = getPiece(lastMoveDstRow, lastMoveDstCol);

				if (lastPiece && lastPiece->getType() == PieceType::TypePawn  // are pawns
					&& lastPiece->getColor() != piece->getColor() // pawns are enemies
					&& std::abs(lastMoveDstRow - lastMoveSrcRow) == 2  // pawn jumped two
					&& lastMoveDstRow == srcRow  // correct row
					&& lastMoveDstCol == dstCol)  // correct column
				{
					isEnPassant = true;
					enPassantCapturedRow = lastMoveDstRow;
					enPassantCapturedCol = lastMoveDstCol;
				}
			}
		}
	}

	// second,  resolve en passant's capture
	// delete it
	if (isEnPassant)
	{
		delete this->_squares[enPassantCapturedRow][enPassantCapturedCol];
		this->_squares[enPassantCapturedRow][enPassantCapturedCol] = nullptr;

	}
	else
	{
		delete this->_squares[dstRow][dstCol];
	}

	// 3, move the piece

	// put source piece in destination and clear it
	this->_squares[dstRow][dstCol] = piece;
	this->_squares[srcRow][srcCol] = nullptr;


	//4,  Pawn promotion
	if (piece->getType() == PieceType::TypePawn)
	{
		Color color = piece->getColor();

		if ((piece->getColor() == Color::White) && (move.getDstRow() == WHITE_BACK_RANK) ||
			(piece->getColor() == Color::Black) && (move.getDstRow() == BLACK_BACK_RANK))
		{
			// promote to queen
			delete piece;
			_squares[dstRow][dstCol] = new Queen(color, PieceType::TypeQueen);
		}
	}
	// 5, update last move
	setLastMove(move);
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
	// -1 to check if king was found
	int kingRow = -1;
	int kingCol = -1;

	int row = 0;
	int col = 0;

	const Piece* piece = nullptr;

	// so we don't iterate over the entire board if unneeded
	bool foundKing = false;


	// Go over the whole board and find the kind
	for (row = 0; row < this->SIZE && !foundKing; row++)
	{
		for (col = 0; col < this->SIZE && !foundKing; col++)
		{
			piece = getPiece(row, col);

			bool isNotEmpty = (piece != nullptr);
			bool sameColor = false;
			bool isKing = false;

			// To Not Derefrence a NULL pointer
			if (isNotEmpty)
			{
				sameColor = (piece->getColor() == curColor);
				isKing = (piece->getType() == PieceType::TypeKing);
			}

			if (isNotEmpty && sameColor && isKing)
			{
				kingRow = row;
				kingCol = col;
				foundKing = true;
			}
		}
	}

	// King not found (should not happen)
	if (!foundKing)
	{
		return false; // Exception
	}


	// Check if any enemy piece attacks the king
	for (row = 0; row < this->SIZE; row++)
	{
		for (col = 0; col < this->SIZE; col++)
		{
			piece = getPiece(row, col);

			bool isNotEmpty = (piece != nullptr);
			bool isEnemy = false;

			// To Not Derefrence a NULL pointer
			if (isNotEmpty)
			{
				isEnemy = (piece->getColor() != curColor);
			}

			// Is an enemy
			if (isNotEmpty && isEnemy)
			{
				// to check if the current piece can reach the king, we make a move for it
				Move attackMove(row, col, kingRow, kingCol);

				if (piece->canMove(attackMove, *this))
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

	// Clear current board
	for (i = 0; i < this->SIZE; i++)
	{
		for (j = 0; j < this->SIZE; j++)
		{
			delete _squares[i][j];
			_squares[i][j] = nullptr;
		}
	}

	// Deep copy from other board using copy c'tor that is in piece (pure)	
	for (i = 0; i < this->SIZE; i++)
	{
		for (j = 0; j < this->SIZE; j++)
		{
			if (other._squares[i][j])
			{
				_squares[i][j] = other._squares[i][j]->clone();
			}
		}
	}

	return *this;
}
