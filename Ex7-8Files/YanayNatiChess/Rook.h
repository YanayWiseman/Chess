#pragma once
#include "Piece.h"
#include "Board.h"


class Rook : public Piece
{
private:
	static constexpr int DIR_COUNT = 4;
	static constexpr int AXES = 2;

	static constexpr int DIRS[DIR_COUNT][AXES] = {
	{ 1, 0 },
	{ -1, 0 },
	{ 0, 1 },
	{ 0, -1 }
	};

public:
	// c'tor
	Rook(Color color, PieceType type);

	// d'tor
	virtual ~Rook() = default;
	// deep copy c'tor
	virtual Piece* clone() const override;

	bool canMove(const Move& move, const Board& board) const override;
	virtual std::vector<Move> getPseudoLegalMoves(const Board& board, int srcRow, int srcCol) const override;

};