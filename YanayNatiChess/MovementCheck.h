/*
	static class that handles movement checks
*/
class Move;
class Board;

class MovementCheck 
{
public:
	// fields
	static bool isStraightPathClear(const Move& move, const Board& board);
	static bool isDiagonalPathClear(const Move& move, const Board& board);
	static bool causesSelfCheck(const Move& move, const Board& board, bool isWhiteTurn);
	static bool causesOpponentCheck(const Board& board, bool isWhiteTurn);
};