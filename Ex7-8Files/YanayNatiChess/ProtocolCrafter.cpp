#include "ProtocolCrafter.h"
#include "Move.h"
#include <cstdio>

/*
	fucntion to parse the given move from the frontEnd into a Move object
	input: the string given from the frontEnd
	output: the movement object with the given position
*/

Move ProtocolCrafter::parseMove(string moveStr)
{
	return Move(moveStr[1] - ONE_CHAR, moveStr[0] - SMALL_A, moveStr[3] - ONE_CHAR, moveStr[2] - SMALL_A);
}

/*
	function to create the response for the frontEnd
	input: the code to craft with
	output: the message to return to the frontEnd
*/
const char* ProtocolCrafter::createResponse(char code)
{
    static char returnCode[3]; // 2 digits + null terminator

    if (code >= '0' && code <= '9')
    {
        // single-digit codes
        returnCode[0] = code;
        returnCode[1] = '\0';
    }
    else
    {
        // for codes 10, 11, 12, map chars to integers
        int intCode = 0;

        switch (code)
        {
        case ':': intCode = 10; break;
        case ';': intCode = 11; break;
        case '<': intCode = 12; break;
        default: intCode = 0; break; // fallback
        }

        sprintf_s(returnCode, "%d", intCode);
    }

    return returnCode;
}