#include "Piece.h"

class Rook : public Piece
{
public:
	// c'tor
	Rook(Color color, PieceType type);

	// d'tor
	virtual ~Rook() = default;

	bool canMove(const Move& move, const Board& board) const override;
};