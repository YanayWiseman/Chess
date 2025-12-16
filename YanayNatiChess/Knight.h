#pragma once
#include "Piece.h"

class Knight : public Piece
{
private:
	static constexpr int KNIGHT_LONG = 2;
	static constexpr int KNIGHT_SHORT = 1;
public:
	// c'tor
	Knight(Color color, PieceType type);

	// d'tor
	virtual ~Knight() = default;
	// deep copy c'tor
	virtual Piece* clone() const override;

	bool canMove(const Move& move, const Board& board) const override;
};