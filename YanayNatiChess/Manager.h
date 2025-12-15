#include <string>
#include "Pipe.h"
#include <iostream>
#include <thread>
#include <stdlib.h>
#include <string.h>
#include <chrono>
#include "ProtocolCrafter.h"
#include "Board.h"
#include "Piece.h"
#include "Move.h"

#define KB 1024

using std::cout;
using std::endl;
using std::string;

class Manager
{
private:
	// Fields
	Board _board;
	Color _turn;
	bool _won;
	bool _inCheck;

	void updateTurn();
	void CheckGameState();

public:
	// methods
	//c'tor
	Manager() = default;  // temp
	void manageGame(); // runGameLoop
	char makeMove(const Move& move);
	char validateMove(const Move& move);

};