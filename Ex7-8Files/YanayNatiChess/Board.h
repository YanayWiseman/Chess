#pragma once
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"
#include "Piece.h"
#include "Move.h"

class Piece;        
class Move;
enum class Color;

#define HASHTAG '#'

typedef enum PieceLetters
{
	RookCh = 'r',
	KnightCh = 'n',
	BishopCh = 'b',
	QueenCh = 'q',
	KingCh = 'k',
	PawnCh = 'p'
} PieceLetters;

class Board 
{
private:
	//fields
	static constexpr int SIZE = 8;
	Piece* _squares[SIZE][SIZE];

	// methods
	Piece* createPieceFromChar(char ch) const;

public:
	//Methods (big 3)
	// c'tor & d'tor
	Board();
	~Board();
	// copy operator
	Board& operator=(const Board& other);

	// Getter
	const Piece* getPiece(int row, int col) const;

	// Helpers
	bool isEmpty(int row, int col) const;
	bool isDestValid(const Move& move) const;
	bool inBoard(int row, int col) const;
	void movePiece(const Move& move);
	bool isKingInCheck(Color curColor) const;
};