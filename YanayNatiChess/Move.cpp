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