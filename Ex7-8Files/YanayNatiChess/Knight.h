#pragma once
#include "Piece.h"

class Knight : public Piece
{
private:
	static constexpr int KNIGHT_LONG = 2;
	static constexpr int KNIGHT_SHORT = 1;

	static constexpr int AXES = 2;
	static constexpr int MOVE_COUNT = 8;
	static constexpr int MOVES[MOVE_COUNT][AXES] = {
		{ KNIGHT_LONG, KNIGHT_SHORT}, { KNIGHT_LONG, -KNIGHT_SHORT},
		{-KNIGHT_LONG, KNIGHT_SHORT}, {-KNIGHT_LONG, -KNIGHT_SHORT},
		{ KNIGHT_SHORT, KNIGHT_LONG}, { KNIGHT_SHORT, -KNIGHT_LONG},
		{-KNIGHT_SHORT, KNIGHT_LONG}, {-KNIGHT_SHORT, -KNIGHT_LONG}
	};

public:
	// c'tor
	Knight(Color color, PieceType type);

	// d'tor
	virtual ~Knight() = default;
	// deep copy c'tor
	virtual Piece* clone() const override;

	bool canMove(const Move& move, const Board& board) const override;
	virtual std::vector<Move> getPseudoLegalMoves(const Board& board, int srcRow, int srcCol) const override;
};