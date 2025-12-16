#include "Manager.h"

int main(void)
{
	Manager manager;

	manager.manageGame();

	return 0;

	//Manager manager;
	//ProtocolCrafter crafter;

	//std::string msgFromInput;

	//// Loop until tester stops sending moves
	//while (std::cin >> msgFromInput && !manager.hasWon())
	//{
	//	Move move = crafter.parseMove(msgFromInput);

	//	// Perform move and get the result code
	//	char code = manager.makeMove(move);  // or whatever your function returns
	//	const char* response = crafter.createResponse(code);

	//	// Send exactly 1 response character to stdout
	//	std::cout << response << std::endl;
	//}

}