#include "Manager.h"

/*
	function to run the entire game
	input: no input values
	output: no return values
*/

void Manager::manageGame()
{
	Pipe pipe;
	bool isConnect = pipe.connect();

	string answer;
	if (!isConnect)
	{
		return;
	}

	char msgToGraphics[KB];

	// begging board
	strcpy_s(msgToGraphics, "rnbqkbnrpppppppp################################PPPPPPPPRNBQKBNR0");

	pipe.sendMessageToGraphics(msgToGraphics);   // send the board string

	// get message from graphics
	string msgFromGraphics = pipe.getMessageFromGraphics();

	ProtocolCrafter crafter;

	while (msgFromGraphics != "quit")
	{
		Move move = crafter.parseMove(msgFromGraphics);
		char code = validateMove(move);

		const char* myCode = crafter.createResponse(code);

		strcpy_s(msgToGraphics, myCode); // msgToGraphics should contain the result of the operation

		// return result to graphics		
		pipe.sendMessageToGraphics(msgToGraphics);

		// get message from graphics
		msgFromGraphics = pipe.getMessageFromGraphics();
	}

	pipe.close();
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
	if (srcPiece || srcPiece->getColor() == this->_turn)
	{
		return notValidDest;
	}

	// 6 - illegal movement of the piece
	if (!srcPiece->canMove(move, this->_board))
	{
		return pieceIllegal;
	}

	// 4 - makes check for the current player
	// simulate a movement
	Board tempBoard = this->_board;
	tempBoard.movePiece(move);

	if (tempBoard.isKingInCheck(this->_turn))
	{
		return selfCheck;
	}

	// if got here, move is legal (0, 1, 8)
	// get opposite color
	Color enemy = (this->_turn == Color::White) ? Color::Black : Color::White;

	if (tempBoard.isKingInCheck(enemy))
	{
		// checkmate? (8)
		if (MovementCheck::causesCheck(move, tempBoard, enemy))
		{
			return legalMoveCheckMate;
		}
		// put enemy in check but didn't win (1)
		return legalMoveCheck;
	}

	// move is legal and didnt put enemy in check or won the game (0)
	return legalMove;
}