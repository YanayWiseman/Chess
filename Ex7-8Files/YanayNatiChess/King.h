#pragma once
#include "Piece.h"
#include "Board.h"

class King : public Piece
{
private:
	// fields
	static constexpr int MAX_SQUARES = 1;
	static constexpr int CASTLING_DISTANCE = 2;

	// methods
	bool canCastle(const Move& move, const Board& board) const;
public:
	// c'tor
	King(Color color, PieceType type);

	// d'tor
	virtual ~King() = default;
	// deep copy c'tor
	virtual Piece* clone() const override;

	bool canMove(const Move& move, const Board& board) const override;
};