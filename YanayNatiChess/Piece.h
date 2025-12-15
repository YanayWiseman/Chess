#include <vector>
#include <iostream>

/*
	Using 'enum class' for safer access
	How to access:
	Color::White || PieceType::Rook
*/ 
enum class Color { White, Black };
enum class PieceType { Pawn, Bishop, Knight, Rook, Queen, King };

class Piece
{
protected:
	//fields
	Color _color;
	PieceType _type;

public:
	// Ctor & Dtor
	Piece(Color color, PieceType type);
	virtual ~Piece() = default;
	
	// Getters
	Color getColor() const;
	PieceType getType() const;

	// Helpers
	virtual bool canMove(const Move& move, const Board& board) const = 0;
};