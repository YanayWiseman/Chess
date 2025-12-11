#include "Manager.h"

/*
	function to run the entire game
	input: no input values
	output: no return values
*/

void Manager::manageGame()
{
	Pipe p;
	bool isConnect = p.connect();

	string ans;
	if (!isConnect)
	{
		return;
	}

	char msgToGraphics[KB];

	// begging board
	strcpy_s(msgToGraphics, "rnbqkbnrpppppppp################################PPPPPPPPRNBQKBNR0");

	p.sendMessageToGraphics(msgToGraphics);   // send the board string

	// get message from graphics
	string msgFromGraphics = p.getMessageFromGraphics();

	while (msgFromGraphics != "quit")
	{
		//const char* myCode = ProtocolCrafter::craftCode();
		strcpy_s(msgToGraphics, "myCode"); // msgToGraphics should contain the result of the operation

		// return result to graphics		
		p.sendMessageToGraphics(msgToGraphics);

		// get message from graphics
		msgFromGraphics = p.getMessageFromGraphics();
		//delete myCode;
	}

	p.close();
}
