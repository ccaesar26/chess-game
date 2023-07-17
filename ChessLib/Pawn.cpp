#include "Pawn.h"

Pawn::Pawn(EColor color, Position position)
	:Piece(color, EName::Pawn, position)
{}

void Pawn::GetMovesPossible(Position currentPos, std::function<PiecePtr(Position)> GetPieceFromBoard, PositionPieceSet& possibleMoves) const
{
	//throw std::logic_error("The method or operation is not implemented.");
}

//bool Pawn::PieceMoveIsPossible(Position initialPosition, Position finalPosition, const Matrix & board)
//{
//
//	int movingWay=1;
//	int initialLine=1;
//
//	if (m_color == EColor::White)
//	{
//		movingWay = -1;
//		initialLine = 6;
//	}
//
//	if (finalPosition.row == initialPosition.row + movingWay)
//	{
//		if (finalPosition.col == initialPosition.col)
//		{
//			if (board[finalPosition.row][finalPosition.col] != nullptr) return false;
//		}
//		else if (finalPosition.col == initialPosition.col - 1 || finalPosition.col == initialPosition.col + 1)
//		{
//			if (board[finalPosition.row][finalPosition.col] == nullptr) return false;
//		}
//		else return false;
//	}
//	else if (finalPosition.row == initialPosition.row + 2 * movingWay)
//	{
//		if (initialPosition.col == finalPosition.col && initialPosition.row==initialLine)
//		{
//			int nextRow = initialLine + movingWay;
//			int nextTwoRows = initialLine + 2 * movingWay;
//			if (board[nextRow][initialPosition.col] != nullptr || board[nextTwoRows][initialPosition.col] != nullptr) return false;
//		}
//		else return false;
//	}
//	else return false;
//	
//	return true;
//}
