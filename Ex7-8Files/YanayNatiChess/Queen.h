#pragma once
#include "Piece.h"

class Queen : public Piece
{
private:
	static constexpr int AXES = 2;
	static constexpr int DIR_COUNT = 8;
	static constexpr int DIRS[DIR_COUNT][AXES] = {
		{ 1,  0}, {-1,  0}, { 0,  1}, { 0, -1},
		{ 1,  1}, { 1, -1}, {-1,  1}, {-1, -1}
	};

public:
	// c'tor
	Queen(Color color, PieceType type);

	// d'tor
	virtual ~Queen() = default;
	// deep copy c'tor
	virtual Piece* clone() const override;

	bool canMove(const Move& move, const Board& board) const override;
	virtual std::vector<Move> getPseudoLegalMoves(const Board& board, int srcRow, int srcCol) const override;
};