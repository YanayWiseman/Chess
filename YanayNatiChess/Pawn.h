#include "Piece.h"

class Pawn : public Piece
{
public:
	// c'tor
	Pawn(Color color, PieceType type);

	// d'tor
	virtual ~Pawn() = default;

	bool canMove(const Move& move, const Board& board) const override;
};