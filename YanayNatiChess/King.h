#include "Piece.h"

class King : public Piece
{
public:
	// King has no fields, so we can use the default implementation
	// c'tor
	King() = default;

	// d'tor
	virtual ~King() = default;

	bool canMove(const Move& move, const Board& board) const override;
};