#include "Queen.h"

/*
	function to move the Queen according to user's input
	input: destination row, destinaton column
	output: no reutrn values
*/

void Queen::move(int dstRow, int dstCol)
{
	if (MovementCheck::moveQueenCheck(dstRow, dstCol))
	{
		this->_row = dstRow;
		this->_col = dstCol;
	}
}