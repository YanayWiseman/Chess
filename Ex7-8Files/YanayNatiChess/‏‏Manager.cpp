#include "Manager.h"

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
	strcpy_s(msgToGraphics, "rnbqkbnrpppppppp################################PPPPPPPPRNBQKBNR0");

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

	// move put enemy in checkmate (8)
	if (!isKingAlive(enemy))
	{
		return legalMoveCheckMate;
	}

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

	if (result != legalMove && result != legalMoveCheck && result != legalMoveCheckMate)
	{
		return result;
	}

	// apply the movement
	this->_board.movePiece(move);

	// update the game state flags
	CheckGameState();

	// if game is not over, swap the player
	if (!this->_won)
	{
		updateTurn();
	}

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
