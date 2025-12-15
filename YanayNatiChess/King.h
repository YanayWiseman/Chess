#include "Piece.h"

class King : public Piece
{
public:
	// c'tor
	King(Color color, PieceType type);

	// d'tor
	virtual ~King() = default;

	bool canMove(const Move& move, const Board& board) const override;
};