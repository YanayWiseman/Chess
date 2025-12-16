#pragma once
#include "Piece.h"

class Queen : public Piece
{
public:
	// c'tor
	Queen(Color color, PieceType type);

	// d'tor
	virtual ~Queen() = default;
	// deep copy c'tor
	virtual Piece* clone() const override;

	bool canMove(const Move& move, const Board& board) const override;
};