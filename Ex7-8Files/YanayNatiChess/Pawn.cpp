#include "Pawn.h"
#include "Move.h"
#include "Board.h"
#include "MovementCheck.h"
#include <cmath>

/*
	Constructor method to construct the Pawn object
	input: the color of the piece and its type
	output no return values
*/

Pawn::Pawn(Color color, PieceType type) : Piece(color, type)
{

}

/*
	Copy c'tor to deep copy the piece
	input: no input values
	output: pointer to the piece
*/

Piece* Pawn::clone() const
{
	return new Pawn(*this);
}

/*
	This function handles the logic for the Pawns movement
	input: Wanted move and current board
	output: Is the move possible for a Pawn to proform
*/
bool Pawn::canMove(const Move& move, const Board& board) const 
{
	/*                         Prerequisites                         */

	// Unpack wanted move											 
	int startRow = move.getSrcRow();								 
	int startCol = move.getSrcCol();							     
	int endRow = move.getDstRow();									 
	int endCol = move.getDstCol();									 						
																	 
	// Get the length in each diraction								 
	int rowDiff = (endRow - startRow);						 
	int colDiff = (endCol - startCol);						 
																	 
	int moveDirection = (this->_color == Color::White) ? UP : DOWN;	 
																	 
	


	/*						 Normal move Logic						 */

	// Normal move conditions
	bool correctColumn = (startCol == endCol);
	bool correctRow = (rowDiff == moveDirection);
	bool destinationEmpty = board.isEmpty(endRow, endCol);
	
	bool forwardOne = correctColumn && correctRow && destinationEmpty;




	/*						 Jump move Logic						 */

	int getStartRank = (moveDirection > 0) ? WHITE_RANK : BLACK_RANK;


	// Jump move conditions
	bool jumpMove = (rowDiff == (JUMP_MOVE * moveDirection));
	bool noObstacle = MovementCheck::isStraightPathClear(move, board) && destinationEmpty;
	bool atStartRank = (getStartRank == startRow);
	
	bool forwardTwo = correctColumn && jumpMove && noObstacle && atStartRank;




	/*						 Capture Logic						     */
	const Piece* dstPiece = board.getPiece(endRow, endCol);

	bool onDiagonal = (abs(colDiff) == 1);
	bool dstIsEnemy = dstPiece && (dstPiece->getColor() != _color);

	bool captureDiagonal = onDiagonal && correctRow && dstIsEnemy;

	// check en passant
	bool enPassant = isEnPassant(move, board);

	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
	/* Pawn can move only in one of the 3 following ways				   */
	/* 1. One square forward										       */
	/* 2. Two squares forward but only if still on starting rank	       */
	/* 3. One square diagonally but only if there is an enemy piece there  */
	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
	bool checkPawnMove = (forwardOne || forwardTwo || captureDiagonal || enPassant);

	return checkPawnMove;
}

/*
	function to check if current state of the board is en passant
	input: the current move and the board (piece positions) (the move is the same as the move that canMove recieved)
	output: boolean, true if en passant is occuring and false otherwise
*/

bool Pawn::isEnPassant(const Move& move, const Board& board) const
{
	const Move* lastMove = board.getLastMove();

	// check if there was a last move (first move in the game edge case)
	if (!lastMove)
	{
		return false;
	}

	// dismante the move's fields
	int srcRow = move.getSrcRow();
	int srcCol = move.getSrcCol();
	int dstRow = move.getDstRow();
	int dstCol = move.getDstCol();

	int moveDirection = (this->_color == Color::White) ? UP : DOWN;

	// for en passant to happen the pawn must move diagonally forword into an empty square
	if ((dstRow - srcRow != moveDirection || std::abs(dstCol - srcCol) != 1) 
		|| (!board.isEmpty(dstRow, dstCol)))
	{
		return false;
	}

	// dismante the last move's fields
	int lastMoveSrcRow = lastMove->getSrcRow();
	int lastMoveDstRow = lastMove->getDstRow();
	int lastMoveDstCol = lastMove->getDstCol();

	// get the destionamtion square of the last move
	const Piece* lastPiece = board.getPiece(lastMoveDstRow, lastMoveDstCol);
	
	// must be enemy pawn
	if (!lastPiece || lastPiece->getType() != PieceType::TypePawn || lastPiece->getColor() == this->_color)
	{
		return false;
	}

	// last pawn must have jumped two squares
	int lastDirection = (lastPiece->getColor() == Color::White) ? UP : DOWN;
	if ((lastMoveDstRow - lastMoveSrcRow) != lastDirection * JUMP_MOVE)
	{
		return false;
	}

	// pawn must now be adjacent horizontally
	if (lastMoveDstRow != srcRow || lastMoveDstCol != dstCol)
	{
		return false;
	}

	// fits all of the en passant conditions!!!
	return true;
}
