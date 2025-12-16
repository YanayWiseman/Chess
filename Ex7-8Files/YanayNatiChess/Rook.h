#pragma once
#include "Piece.h"

class Rook : public Piece
{
public:
	// c'tor
	Rook(Color color, PieceType type);

	// d'tor
	virtual ~Rook() = default;
	// deep copy c'tor
	virtual Piece* clone() const override;

	bool canMove(const Move& move, const Board& board) const override;
};