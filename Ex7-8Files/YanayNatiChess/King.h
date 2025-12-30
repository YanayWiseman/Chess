#pragma once
#include "Piece.h"
#include "Board.h"
#include "MovementCheck.h"

class King : public Piece
{
private:
	// fields
	static constexpr int MAX_SQUARES = 1;
	static constexpr int CASTLING_DISTANCE = 2;

	static constexpr int AXES = 2;
	static constexpr int DIR_COUNT = 8;
	static constexpr int DIRS[DIR_COUNT][AXES] = {
		{ -1,  0 },
		{  1,  0 },
		{  0, -1 },
		{  0,  1 },
		{ -1, -1 },
		{ -1,  1 },
		{  1, -1 },
		{  1,  1 }
	};

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
	virtual std::vector<Move> getPseudoLegalMoves(const Board& board, int srcRow, int srcCol) const override;
};