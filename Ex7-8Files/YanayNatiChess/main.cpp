#include "Manager.h"

int main(void)
{
	//Manager manager;

	//manager.manageGame();

	//return 0;

    Manager manager;
    ProtocolCrafter crafter;

    std::string msgFromInput;

    while (std::getline(std::cin, msgFromInput) && !manager.hasWon())
    {
        Move move = crafter.parseMove(msgFromInput);

        char code = manager.makeMove(move); // '0'–'8' or other Codes enum chars

        std::cout << code << std::endl;
        std::cout.flush();
    }

    return 0;
}