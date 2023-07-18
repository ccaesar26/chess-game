#include "Pawn.h"

Pawn::Pawn(EColor color)
	: Piece(color, EType::Pawn)
{
}

PositionList Pawn::GetPossibleMoves(Position currentPos, std::function<PiecePtr(Position)> GetPieceFromBoard) const
{
	return PositionList();
}

//void Pawn::GetMovesPossible(Position currentPos, std::function<IPiecePtr(Position)> GetPieceFromBoard, PositionPieceSet& possibleMoves) const
//{
//	int movingWay = 1;
//	int initialLine = 1;
//
//	if (m_color == EColor::White)
//	{
//		movingWay = -1;
//		initialLine = 6;
//	}
//
//	if (GetPieceFromBoard(Position(currentPos.row + movingWay, currentPos.col)) == nullptr)
//	{
//		possibleMoves.insert(Position(currentPos.row + movingWay, currentPos.col));
//	}
//
//	if (currentPos.col - 1 >= 0)
//	{
//		if (GetPieceFromBoard(Position(currentPos.row + movingWay, currentPos.col - 1)) != nullptr)
//		{
//			if (GetPieceFromBoard(Position(currentPos.row + movingWay, currentPos.col - 1))->GetColor() != m_color)
//			{
//				possibleMoves.insert(Position(currentPos.row + movingWay, currentPos.col - 1));
//			}
//		}
//	}
//
//	if (currentPos.col + 1 <= 7)
//	{
//		if (GetPieceFromBoard(Position(currentPos.row + movingWay, currentPos.col + 1)) != nullptr)
//		{
//			if (GetPieceFromBoard(Position(currentPos.row + movingWay, currentPos.col + 1))->GetColor() != m_color)
//			{
//				possibleMoves.insert(Position(currentPos.row + movingWay, currentPos.col + 1));
//			}
//		}
//	}
//
//	if (currentPos.row == initialLine)
//	{
//		if (possibleMoves.find(Position(currentPos.row + movingWay, currentPos.col)) != possibleMoves.end())
//		{
//			if (GetPieceFromBoard(Position(currentPos.row + 2 * movingWay, currentPos.col)) == nullptr)
//			{
//				possibleMoves.insert(Position(currentPos.row + 2 * movingWay, currentPos.col));
//			}
//		}
//	}
//}