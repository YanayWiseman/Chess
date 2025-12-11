/*
	static class that handles movement checks
*/

class MovementCheck 
{
public:
	// fields
	static bool moveBishopCheck(int dstRow, int dstCol);
	static bool moveQueenCheck(int dstRow, int dstCol);
	static bool moveKingCheck(int dstRow, int dstCol);
	static bool moveKnightCheck(int dstRow, int dstCol);
	static bool movePawnCheck(int dstRow, int dstCol);
	static bool moveRookCheck(int dstRow, int dstCol);
};