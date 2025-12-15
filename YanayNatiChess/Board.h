class Piece;        
class Move;
enum Color;

class Board 
{
private:
	//fields
	static constexpr int SIZE = 8;
	Piece* _squares[SIZE][SIZE];
public:
	//Methods

	// Getter
	const Piece* getPiece(int row, int col) const;

	// Helpers
	bool isEmpty(int row, int col) const;
	bool isPathClear(const Move move) const;
	void movePiece(const Move move);
	bool isKingInCheck(Color color) const;
};