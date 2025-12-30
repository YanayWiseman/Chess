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
	legalMove = '0',
	legalMoveCheck = '1',    // move caused check on enemy
	notValidSource = '2',    // src pos isn't player's piece
	notValidDest = '3',      // dst pos is the piece of the same team as the sec
	selfCheck = '4',         // movement can cause self check
	notInBoard = '5',		   // one of the positions is not within the board
	pieceIllegal = '6',	   // illegal movement of the piece
	noMove = '7',			   // src is dst
	legalMoveCheckMate = '8' // move cause checkmate (game is over)
} Codes;

class Manager
{
private:
	// Fields
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

public:
	// methods
	//c'tor
	Manager();  // temp
	void manageGame(); // runGameLoop
	char makeMove(const Move& move);
	char validateMove(const Move& move);
	bool hasWon() const;
	bool isKingInMate(Color color);
};