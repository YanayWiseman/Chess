#include "Manager.h"
#include <vector>

const int BOARD_SIZE = 8;


/*
	manager ctor
	input: no input values
	output: no return values
*/
Manager::Manager() : _board(), _turn(Color::White), _won(false), _inCheck(false)
{
}


/*
	function to run the entire game
	input: no input values
	output: no return values
*/
void Manager::manageGame()
{
#ifdef _WIN32

	Pipe pipe;
	bool isConnect = pipe.connect();

	string answer;
	if (!isConnect)
	{
		return;
	}

	char msgToGraphics[KB];

	// beggining board
	strcpy_s(msgToGraphics, "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr0");

	pipe.sendMessageToGraphics(msgToGraphics);   // send the board string

	// get message from graphics
	string msgFromGraphics = pipe.getMessageFromGraphics();

	ProtocolCrafter crafter;

	while (msgFromGraphics != "quit" && !this->_won)
	{
		Move move = crafter.parseMove(msgFromGraphics);
		char code = makeMove(move);
		const char* myCode = crafter.createResponse(code);

		strcpy_s(msgToGraphics, KB, myCode); // msgToGraphics should contain the result of the operation
		pipe.sendMessageToGraphics(msgToGraphics); // return result to graphics

		// after a valid move, send updated board state (BONUS)
		if (code == legalMove || code == legalMoveCheck || code == legalMoveCheckmate)
		{
			string boardState = getBoardString();
			strcpy_s(msgToGraphics, KB, boardState.c_str());
			pipe.sendMessageToGraphics(msgToGraphics);
		}


		msgFromGraphics = pipe.getMessageFromGraphics();  // get message from graphics
	}

	pipe.close();
#endif 
}

/*
	function returns the type of move (code) according to the protocol (check Codes enum in Manager.h)
	input: the move to make
	output: the code (char)
*/

char Manager::validateMove(const Move& move)
{
	int srcRow = move.getSrcRow();
	int srcCol = move.getSrcCol();
	int dstRow = move.getDstRow();
	int dstCol = move.getDstCol();

	// 7 (src is dst0
	if (srcRow == dstRow && srcCol == dstCol)
	{
		return noMove;
	}

	// 5 - not in board
	if (!this->_board.inBoard(srcRow, srcCol) || !this->_board.inBoard(dstRow, dstCol))
	{
		return notInBoard;
	}

	// get the move's pieces
	const Piece* srcPiece = this->_board.getPiece(srcRow, srcCol);

	// 2 - src doesnt have current plauyer's piece
	if (!srcPiece || srcPiece->getColor() != this->_turn)
	{
		return notValidSource;
	}

	const Piece* dstPiece = this->_board.getPiece(dstRow, dstCol);

	// 3 - dst is the same color as src
	if (dstPiece && dstPiece->getColor() == this->_turn)
	{
		return notValidDest;
	}

	// 6 - illegal movement of the piece
	if (!srcPiece->canMove(move, this->_board))
	{
		return pieceIllegal;
	}

	// 4 - makes check for the current player
	if (MovementCheck::causesCheck(move, this->_board, this->_turn))
	{
		return selfCheck;
	}


	// if got here, move is legal (0, 1, 8)
	// get opposite color
	Color enemy = (this->_turn == Color::White) ? Color::Black : Color::White;

	// move put enemy in check (1)
	if (MovementCheck::causesCheck(move, this->_board, enemy))
	{
		return legalMoveCheck;
	}

	// move is legal and didnt put enemy in check or won the game (0)
	return legalMove;
}

/*
	function to do the move if its legal
	input: the move to do
	output: 0 - 8 accoording to the game protocol
*/

char Manager::makeMove(const Move& move)
{
	char result = validateMove(move);


	if (result != legalMove && result != legalMoveCheck)
	{
		return result;
	}

	// apply the movement
	this->_board.movePiece(move);

	if (insufficientMaterial()) 
	{
		result = drawInsufficientMaterial;
	}

	updateTurn();

	if (result == legalMoveCheck && isKingInMate(_turn))
	{
		result = legalMoveCheckmate;
	}

	if (result == legalMove && isStalemate(_turn)) 
	{
		result = legelMoveStalemate;
	}

	// update the game state flags
	CheckGameState();

	return result;
}

/*
	function to update the turn every turn to the other player
	input: no input values
	output: no return values
*/

void Manager::updateTurn()
{
	this->_turn = (_turn == Color::White) ? Color::Black : Color::White;
}

/*
	function to check the game state and update the flags - _won, _inCheck
	input: no input values
	output: no return values
*/

void Manager::CheckGameState()
{
	Color enemy = (_turn == Color::White) ? Color::Black : Color::White;

	// check?
	this->_inCheck = this->_board.isKingInCheck(enemy);

	// if enemy king does not exist then current player won
	this->_won = !isKingAlive(enemy);
}

/*
	Helper function to check if the enemy's king is alive or not
	input: the enemy king's color
	output: boolean, true if enemy king exists and false otherwise
*/

bool Manager::isKingAlive(Color kingColor) const
{
	int i = 0, j = 0;

	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			const Piece* curPiece = this->_board.getPiece(i, j);
			if (curPiece && curPiece->getColor() == kingColor && curPiece->getType() == PieceType::TypeKing)
			{
				return true;
			}
		}
	}
	return false;
}


/*
	this function returns the win status
	input: none
	output: none
*/
bool Manager::hasWon() const
{
	return this->_won;
}

/*
	method to get the current state of the board as a string
	input: no input values
	output: 65 character string representing the board and current player
*/

string Manager::getBoardString() const
{
	string boardStr = "";

	int i = 0, j = 0;
	const int SIZE = 8;  // init in board so just use it here too

	for (i = SIZE - 1; i >= 0; i--) // read board backwards
	{
		for (j = 0; j < SIZE; j++)
		{
			const Piece* curPiece = this->_board.getPiece(i, j);

			//empty square
			if (!curPiece)
			{
				boardStr += '#';
			}
			else  // white piece
			{
				char ch = 0;

				switch (curPiece->getType())
				{
				case PieceType::TypeRook:
					ch = 'r';
					break;
				case PieceType::TypeKnight:
					ch = 'n';
					break;
				case PieceType::TypeBishop:
					ch = 'b';
					break;
				case PieceType::TypeQueen:
					ch = 'q';
					break;
				case PieceType::TypeKing:
					ch = 'k';
					break;
				case PieceType::TypePawn: 
					ch = 'p';
					break;
				default: 
					ch = '#';
					break;
				}

				// black is uppercase
				if (curPiece->getColor() == Color::Black)
				{
					ch = toupper(ch);
				}

				boardStr += ch;
			}
		}
	}

	// add current player
	boardStr += (this->_turn == Color::White) ? '0' : '1';

	return boardStr;
}


/*
	This function checks if a player has a valid move
	input: the current color playing
	output: true if he has a valid move false if he doesnt
*/
bool Manager::hasAnyValidMove(Color color)
{
	int i = 0;
	int row = 0;
	int col = 0;
	std::vector<const Piece*> colorPieces;
	std::vector<std::pair<int, int>> positions;


	// Step 1: collect all pieces of the given color
	for (row = 0; row < BOARD_SIZE; row++)
	{
		for (col = 0; col < BOARD_SIZE; col++)
		{
			const Piece* piece = this->_board.getPiece(row, col);
			if (piece && piece->getColor() == color)
			{
				colorPieces.push_back(piece);
				positions.emplace_back(row, col);
			}
		}
	}

	// Step 2: iterate over pieces and their pseudo-legal moves
	auto posIt = positions.begin();
	for (const Piece* p : colorPieces)
	{
		int row = posIt->first;
		int col = posIt->second;
		posIt++;

		for (const Move& move : p->getPseudoLegalMoves(this->_board, row, col))
		{
			char code = validateMove(move);
			if (code == legalMove || code == legalMoveCheck)
			{
				return true; // found a valid move
			}
		}
	}

	// No valid moves found
	return false; 
}


/*
	This function checks if a given colored king is in mate
	input: the current color playing
	output: true if the given king in mate false if not in mate
*/
bool Manager::isKingInMate(Color color)
{
	return !hasAnyValidMove(color);
}


/*
	This function checks if a given colored player is in stalemate
	input: the current color playing
	output: true if the given king in stalemate false if not in stalemate
*/
bool Manager::isStalemate(Color color)
{
	return !hasAnyValidMove(color);
}

/*
	This function checks if the meterial on the board is sufficient to play
	input: the current color playing
	output: true if sufficient false if not
*/
bool Manager::insufficientMaterial() const
{
	// Collect all pieces on the board
	std::vector<const Piece*> whitePieces;
	std::vector<const Piece*> blackPieces;
	int row = 0;
	int col = 0;

	for (row = 0; row < BOARD_SIZE; row++)
	{
		for (col = 0; col < BOARD_SIZE; col++)
		{
			const Piece* piece = this->_board.getPiece(row, col);
			if (!piece)
			{
				continue;
			}

			if (piece->getType() == PieceType::TypeKing)
			{
				continue; // ignore kings
			}

			if (piece->getColor() == Color::White)
			{
				whitePieces.push_back(piece);
			}
			else
			{
				blackPieces.push_back(piece);
			}
		}
	}

	// Only kings left
	if (whitePieces.empty() && blackPieces.empty())
	{
		return true;
	}

	// King + knight or king + bishop vs king
	if ((whitePieces.size() == 1 && blackPieces.empty()) || (blackPieces.size() == 1 && whitePieces.empty()))
	{
		const Piece* p = whitePieces.empty() ? blackPieces[0] : whitePieces[0];
		PieceType type = p->getType();
		if (type == PieceType::TypeBishop || type == PieceType::TypeKnight)
		{
			return true;
		}
	}

	// King + bishop vs king + bishop (draw if bishops on same color)
	if (whitePieces.size() == 1 && blackPieces.size() == 1)
	{
		const Piece* whiteBishop = whitePieces[0];
		const Piece* blackBishop = blackPieces[0];

		if (whiteBishop->getType() == PieceType::TypeBishop && blackBishop->getType() == PieceType::TypeBishop)
		{
			// get positions
			int whiteRow = -1, whiteCol = -1;
			int blackRow = -1, blackCol = -1;

			for (int row = 0; row < BOARD_SIZE; row++)
			{
				for (int col = 0; col < BOARD_SIZE; col++)
				{
					const Piece* piece = this->_board.getPiece(row, col);
					if (piece == whiteBishop)
					{
						whiteRow = row;
						whiteCol = col;
					}
					if (piece == blackBishop)
					{
						blackRow = row;
						blackCol = col;
					}
				}
			}

			if ((whiteRow + whiteCol) % 2 == (blackRow + blackCol) % 2)
				return true;
		}
	}

	return false; // otherwise, material is sufficient
}