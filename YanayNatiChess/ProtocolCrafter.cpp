#include "ProtocolCrafter.h"
#include "Move.h"

/*
	fucntion to parse the given move from the frontEnd into a Move object
	input: the string given from the frontEnd
	output: the movement object with the given position
*/

Move& ProtocolCrafter::parseMove(string moveStr)
{
	Move move(moveStr[0] - BACKTICK, moveStr[1] - ZERO_CHAR, moveStr[2] - BACKTICK, moveStr[3] - ZERO_CHAR);

	return move;
}

/*
	function to create the response for the frontEnd
	input: the code to craft with
	output: the message to return to the frontEnd
*/

const char* ProtocolCrafter::createResponse(char code)
{
	char* returnCode = new char[2];
	returnCode[0] = code;
	returnCode[1] = '\0';

	return returnCode;
}