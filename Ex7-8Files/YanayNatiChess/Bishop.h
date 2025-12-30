#pragma once
#include "Piece.h"

class Bishop : public Piece
{
private:
	static constexpr int AXES = 2;
	static constexpr int DIR_COUNT = 4;
	static constexpr int DIRS[DIR_COUNT][AXES] = {
		{ 1,  1},
		{ 1, -1},
		{-1,  1},
		{-1, -1}
	};

public:
	// c'tor
	Bishop(Color color, PieceType type);

	// d'tor
	virtual ~Bishop() = default;
	// deep copy c'tor
	virtual Piece* clone() const override;

	bool canMove(const Move& move, const Board& board) const override;
	virtual std::vector<Move> getPseudoLegalMoves(const Board& board, int srcRow, int srcCol) const override;
};