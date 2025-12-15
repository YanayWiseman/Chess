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
	Rook = 'r',
	Knight = 'n',
	Bishop = 'b',
	Queen = 'q',
	King = 'k',
	Pawn = 'p'
};

class Board 
{
private:
	//fields
	static constexpr int SIZE = 8;
	Piece* _squares[SIZE][SIZE];

	// methods
	bool inBoard(int row, int col) const;
	Piece* createPieceFromChar(char ch) const;

public:
	//Methods
	// c'tor & d'tor
	Board();
	~Board();

	// Getter
	const Piece* getPiece(int row, int col) const;

	// Helpers
	bool isEmpty(int row, int col) const;
	bool isPathClear(const Move& move) const;
	void movePiece(const Move& move);
	bool isKingInCheck(Color color) const;
};