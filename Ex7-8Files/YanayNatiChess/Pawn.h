#pragma once
#include "Piece.h"

class Pawn : public Piece
{
private:
	// Moving direction Constents
	static constexpr int UP = 1;
	static constexpr int DOWN = -1;

	// Move Constent
	static constexpr int JUMP_MOVE = 2;

	//Start Row
	static constexpr int WHITE_RANK = 1;
	static constexpr int BLACK_RANK = 6;

public:
	// c'tor
	Pawn(Color color, PieceType type);

	// d'tor
	virtual ~Pawn() = default;
	// deep copy c'tor
	virtual Piece* clone() const override;

	bool canMove(const Move& move, const Board& board) const override;
};