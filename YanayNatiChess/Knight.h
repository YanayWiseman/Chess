#include "Piece.h"

class Knight : public Piece
{
public:
	// Knight has no fields, so we can use the default implementation
	// c'tor
	Knight() = default;

	// d'tor
	virtual ~Knight() = default;

	void move(int dstRow, int dstCol) override;
};