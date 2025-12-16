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


	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
	/* Pawn can move only in one of the 3 following ways				   */
	/* 1. One square forward										       */
	/* 2. Two squares forward but only if still on starting rank	       */
	/* 3. One square diagonally but only if there is an enemy piece there  */
	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
	bool checkPawnMove = (forwardOne || forwardTwo || captureDiagonal);

	return checkPawnMove;
}