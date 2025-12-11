#include <vector>
#include <iostream>

class Piece
{
private:
	//fields
	int _row;
	int _col;
	int _color;
	// first digit -> row, second digit -> col
	std::vector<int> _canMoveTo;

public:
	// methods
	
	//c'tor
	Piece(const int row, const int col, const int color);

	//d'tor
	virtual ~Piece();

	virtual void move() = 0;
};