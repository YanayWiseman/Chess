#include "Bishop.h"

/*
	function to move the bishop according to user's input
	input: destination row, destinaton column
	output: no reutrn values
*/

void Bishop::move(int dstRow, int dstCol)
{
	if(MovementCheck::moveBishopCheck(dstRow, dstCol))
	{
		this->_row = dstRow;
		this->_col = dstCol;
	}
}