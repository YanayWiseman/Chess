#pragma once
#include <iostream>
#include <vector>

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
	bool _hasMoved;  // for castling

public:
	// Ctor & Dtor
	Piece(Color color, PieceType type);
	virtual ~Piece() = default;
	// copy c'tor
	virtual Piece* clone() const = 0;
	bool hasMoved() const;

	// Getters
	Color getColor() const;
	PieceType getType() const;

	// Setters
	void setHasMoved(bool moved);

	// Helpers
	virtual bool canMove(const Move& move, const Board& board) const = 0;
	virtual void getPseudoLegalMoves(const Board& board, int srcRow, int srcCol, std::vector<Move>& outMoves) const = 0;
};