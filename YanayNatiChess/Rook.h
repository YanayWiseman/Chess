#include "Piece.h"

class Rook : public Piece
{
public:
	// Rook has no fields, so we can use the default implementation
	// c'tor
	Rook() = default;

	// d'tor
	virtual ~Rook() = default;

	void move(int dstRow, int dstCol) override;
};