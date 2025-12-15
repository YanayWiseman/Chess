#include <string>
#include "Pipe.h"
#include <iostream>
#include <thread>
#include <stdlib.h>
#include <string.h>
#include <chrono>
#include "ProtocolCrafter.h"

#define KB 1024

using std::cout;
using std::endl;
using std::string;

class Manager
{
protected:
	bool _won;
	int _turn;  // 0 -> white, 1 -> black
	bool _isCheck; // current king is in check position
	string _code;  // input recieved from the froneEnd
public:
	// methods
	//c'tor
	Manager() = default;  // temp
	void manageGame();
};