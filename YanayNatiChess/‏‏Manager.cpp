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

char Manager::validateMove(const Move& move)
{
	return '0';
}