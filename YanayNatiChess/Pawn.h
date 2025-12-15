#include "Piece.h"

class Pawn : public Piece
{
public:
	// c'tor
	Pawn(Color color, PieceType type);

	// d'tor
	virtual ~Pawn() = default;
	// deep copy c'tor
	virtual Piece* clone() const override;

	bool canMove(const Move& move, const Board& board) const override;
};