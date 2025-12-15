#pragma once

#define BACKTICK  '`'
#define ZERO_CHAR '0'

/*
	class that stores the move info
*/
class Move 
{
private:
	// fields
	int _srcRow;
	int _srcCol;
	int _dstRow;
	int _dstCol;

public:
	//c'tor & d'tor
	Move(int srcRow, int srcCol, int dstRow, int dstCol);
	~Move() = default;

	// Methods
	int getSrcRow() const;
	int getSrcCol() const;
	int getDstRow() const;
	int getDstCol() const;
};