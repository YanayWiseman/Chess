#pragma once
#include "Piece.h"

class Pawn : public Piece
{
private:
	// Moving diraction Constents
	static constexpr int UP = 1;
	static constexpr int DOWN = -1;

public:
	// c'tor
	Pawn(Color color, PieceType type);

	// d'tor
	virtual ~Pawn() = default;
	// deep copy c'tor
	virtual Piece* clone() const override;

	bool canMove(const Move& move, const Board& board) const override;
};