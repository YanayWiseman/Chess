#include "Move.h"

/*
	Constructor for the Move object
	input: the source and destination positions
	output: no return values
*/

Move::Move(int srcRow, int srcCol, int dstRow, int dstCol)
	: _srcRow(srcRow), _srcCol(srcCol), _dstRow(dstRow), _dstCol(dstCol)
{

}

/*
	Getter methods to get the source row
	input: no input values
	output: the source row
*/

int Move::getSrcRow() const
{
	return this->_srcRow;
}

/*
	Getter methods to get the source column
	input: no input values
	output: the source column
*/

int Move::getSrcCol() const
{
	return this->_srcCol;
}

/*
	Getter methods to get the destination row
	input: no input values
	output: the destination row
*/

int Move::getDstRow() const
{
	return this->_dstRow;
}

/*
	Getter methods to get the destination column
	input: no input values
	output: the destination columns
*/

int Move::getDstCol() const
{
	return this->_dstCol;
}