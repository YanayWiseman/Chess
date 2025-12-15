#pragma once

/*
	static class that handles movement checks
*/
class Move;
class Board;
enum class Color;

class MovementCheck 
{
public:
	// Methods
	static bool isStraightPathClear(const Move& move, const Board& board);
	static bool isDiagonalPathClear(const Move& move, const Board& board);
	static bool causesCheck(const Move& move, const Board& board, Color kingColor);
};