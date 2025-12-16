#pragma once
#include "Move.h"
#include <string>
using std::string;

class ProtocolCrafter
{
public:
	//methods
	static Move parseMove(string moveStr);
	static const char* createResponse(char code);
};