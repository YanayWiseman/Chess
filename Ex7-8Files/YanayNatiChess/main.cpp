#include "Manager.h"

int main(void)
{
    // if running locally, uncomment this and comment the rest
#ifdef _WIN32
	Manager manager;

	manager.manageGame();

	return 0;
#endif

    // if running on github, uncomment this and comment the section above
    
    //Manager manager;
    //ProtocolCrafter crafter;

    //std::string msgFromInput;

    //while (std::getline(std::cin, msgFromInput) && !manager.hasWon())
    //{
    //    Move move = crafter.parseMove(msgFromInput);

    //    char code = manager.makeMove(move); // '0'–'8' or other Codes enum chars

    //    std::cout << code << std::endl;
    //    std::cout.flush();
    //}

    //return 0;
}