#include "Piece.h"

class Bishop : public Piece
{
public:
	// Bishop has no fields, so we can use the default implementation
	// c'tor
	Bishop() = default;

	// d'tor
	virtual ~Bishop() = default;

	void move(int dstRow, int dstCol) override;
};