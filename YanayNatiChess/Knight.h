#include "Piece.h"

class Knight : public Piece
{
public:
	// c'tor
	Knight(Color color, PieceType type);

	// d'tor
	virtual ~Knight() = default;
	// deep copy c'tor
	virtual Piece* clone() const override;

	bool canMove(const Move& move, const Board& board) const override;
};