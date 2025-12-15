#include "Piece.h"

class Bishop : public Piece
{
public:
	// c'tor
	Bishop(Color color, PieceType type);

	// d'tor
	virtual ~Bishop() = default;

	bool canMove(const Move& move, const Board& board) const override;
};