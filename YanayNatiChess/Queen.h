#include "Piece.h"

class Queen : public Piece
{
public:
	// c'tor
	Queen(Color color, PieceType type);

	// d'tor
	virtual ~Queen() = default;

	bool canMove(const Move& move, const Board& board) const override;
};