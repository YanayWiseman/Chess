#include <string>

using std::string;

class Manager
{
protected:
	bool _won;
	int _turn;  // 0 -> white, 1 -> black
	bool _isCheck; // current king is in check position
	string _code;  // input recieved from the froneEnd
public:
	void manageGame(string _code);
};