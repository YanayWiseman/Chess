#include "Piece.h"

class Queen : public Piece
{
public:
	// Queen has no fields, so we can use the default implementation
	// c'tor
	Queen() = default;

	// d'tor
	virtual ~Queen() = default;

	void move(int dstRow, int dstCol) override;
};