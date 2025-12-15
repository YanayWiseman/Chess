#include "Move.h"
#include <string>
using std::string;

class ProtocolCrafter
{
public:
	//methods
	Move& parseMove(const string& moveStr);
	string createResponse(char code);
};