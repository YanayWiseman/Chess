#pragma once
#include <string>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <thread>
#include "Pipe.h"
#include <chrono>
#endif
#include "ProtocolCrafter.h"
#include "MovementCheck.h"
#include "Board.h"
#include "Piece.h"
#include "Move.h"

#define KB 1024

using std::cout;
using std::endl;
using std::string;

typedef enum Codes
{
	legalMove = '0',				   		    // move was legel and didn't cause nothing
	legalMoveCheck = '1',			  		   // move caused check on enemy
	notValidSource = '2',			 		  // src pos isn't player's piece
	notValidDest = '3',             		 // dst pos is the piece of the same team as the sec
	selfCheck = '4',               		    // movement can cause self check
	notInBoard = '5',			  		   // one of the positions is not within the board
	pieceIllegal = '6',			 		  // illegal movement of the piece
	noMove = '7',			    		 // src is dst
	legalMoveCheckmate = '8',  		    // move cause checkmate (game is over)
	legalMoveStalemate = '9', 		   // move cause stalemate (game is over)
	drawInsufficientMaterial = 58,    // not enough meterial on the board to cause mate
	drawFiftyMoveRule = 59,			 // no pawn was moved or piece was captured for 50 moves
	drawThreeFoldRepetition = 60    // the same position was reach 5 times
	
} Codes;

class Manager
{
private:
	static constexpr int FIFTY_MOVE_RULE = 100; // 50 * 2 as each players turn is a half move
	static constexpr int THREE_FOLD_REPETITION = 3;

	// Fields
	int _halfMoveClock;  // for 50-move rule

	// (uses the constent from the fifty moves rule as the reset condition for both is the same)
	std::string _positionHistory[FIFTY_MOVE_RULE]; // store last 100 board positions 
	int _positionIndex; // points to the next slot to write

	Board _board;
	Color _turn;
	bool _won;
	bool _inCheck;

	// methods
	void updateTurn();
	void CheckGameState();
	bool isKingAlive(Color kingColor) const;
	string getBoardString() const;
	bool hasAnyValidMove(Color color);
	bool isStalemate(Color color);

public:
	// methods
	//c'tor
	Manager();  // temp
	void manageGame(); // runGameLoop
	char makeMove(const Move& move);
	char validateMove(const Move& move);
	bool hasWon() const;
	bool isKingInMate(Color color);
	bool insufficientMaterial() const;
};