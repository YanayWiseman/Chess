
class ProtocolCrafter
{
public:
	//methods
	Move& parseMove(const string& moveStr);
	string createResponse(char code);
};