#pragma once
#include <iostream>

class Move;
class Board;

/*
	Using 'enum class' for safer access
	How to access:
	Color::White || PieceType::Rook
*/

typedef enum class Color
{
	White,
	Black
} Color;

typedef enum class PieceType
{ 
	TypePawn,
	TypeBishop,
	TypeKnight,
	TypeRook,
	TypeQueen,
	TypeKing
} PieceType;

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
	// copy c'tor
	virtual Piece* clone() const = 0;
	
	// Getters
	Color getColor() const;
	PieceType getType() const;

	// Helpers
	virtual bool canMove(const Move& move, const Board& board) const = 0;
};