#pragma once
#include "Piece.h"

class King : public Piece
{
public:
	// c'tor
	King(Color color, PieceType type);

	// d'tor
	virtual ~King() = default;
	// deep copy c'tor
	virtual Piece* clone() const override;

	bool canMove(const Move& move, const Board& board) const override;
};