#pragma once
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"
#include "Piece.h"
#include "Move.h"
#include <cmath>

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
	static constexpr int WHITE_BACK_RANK = 7;
	static constexpr int BLACK_BACK_RANK = 0;

	Piece* _squares[SIZE][SIZE];

	// for en passant
	bool _hasLastMove = false;
	Move _lastMove;

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
	const Move* getLastMove() const;
	int getSize() const;

	// setter
	void setLastMove(const Move& move);

	// Helpers
	bool isEmpty(int row, int col) const;
	bool isDestValid(const Move& move) const;
	bool inBoard(int row, int col) const;
	void movePiece(const Move& move);
	bool isKingInCheck(Color curColor) const;
	Move findKingByColor(Color color) const;

	void printBoard() const;
};