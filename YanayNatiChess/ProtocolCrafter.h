#include "Move.h"
#include <string>
using std::string;

class ProtocolCrafter
{
public:
	//methods
	Move& parseMove(string moveStr);
	const char* createResponse(char code);
};