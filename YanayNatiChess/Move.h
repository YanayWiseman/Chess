#pragma once

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
	// Methods
	int getSrcRow() const;
	int getSrcCol() const;
	int getDstRow() const;
	int getDstCol() const;
};