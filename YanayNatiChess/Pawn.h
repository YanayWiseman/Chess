#include "Piece.h"

class Pawn : public Piece
{
public:
	// Pawn has no fields, so we can use the default implementation
	// c'tor
	Pawn() = default;

	// d'tor
	virtual ~Pawn() = default;

	bool canMove(const Move& move, const Board& board) const override;
};