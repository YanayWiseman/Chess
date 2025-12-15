#include "Piece.h"

class Bishop : public Piece
{
public:
	// c'tor
	Bishop(Color color, PieceType type);

	// d'tor
	virtual ~Bishop() = default;
	// deep copy c'tor
	virtual Piece* clone() const override;

	bool canMove(const Move& move, const Board& board) const override;
};