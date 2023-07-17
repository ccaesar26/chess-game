#include "Bishop.h"

Bishop::Bishop(EColor color, Position position)
	: Piece(color, EType::Bishop, position)
{
}

// void Bishop::GetMovesPossible(Position currentPos, std::function<IPiecePtr(Position)> GetPieceFromBoard, PositionPieceSet& possibleMoves) const
//{
//	// upper left
//	for (int i = currentPos.row - 1, j = currentPos.col - 1; i >= 0 && j >= 0; i--, j--)
//	{
//		Position toCheckPosition(i, j);
//		if (GetPieceFromBoard(toCheckPosition))
//		{
//			if (GetPieceFromBoard(toCheckPosition)->GetColor() != m_color)
//			{
//				possibleMoves.insert(toCheckPosition);
//			}
//			break;
//		}
//		possibleMoves.insert(toCheckPosition);
//	}
//	// upper right
//	for (int i = currentPos.row - 1, j = currentPos.col + 1; i >= 0 && j < 8; i--, j++)
//	{
//		Position toCheckPosition(i, j);
//		if (GetPieceFromBoard(toCheckPosition))
//		{
//			if (GetPieceFromBoard(toCheckPosition)->GetColor() != m_color)
//			{
//				possibleMoves.insert(toCheckPosition);
//			}
//			break;
//		}
//		possibleMoves.insert(toCheckPosition);
//	}
//	// lower left
//	for (int i = currentPos.row + 1, j = currentPos.col - 1; i < 8 && j >= 0; i++, j--)
//	{
//		Position toCheckPosition(i, j);
//		if (GetPieceFromBoard(toCheckPosition))
//		{
//			if (GetPieceFromBoard(toCheckPosition)->GetColor() != m_color)
//			{
//				possibleMoves.insert(toCheckPosition);
//			}
//			break;
//		}
//		possibleMoves.insert(toCheckPosition);
//	}
//	// lower right
//	for (int i = currentPos.row + 1, j = currentPos.col + 1; i < 8 && j < 8; i++, j++)
//	{
//		Position toCheckPosition(i, j);
//		if (GetPieceFromBoard(toCheckPosition))
//		{
//			if (GetPieceFromBoard(toCheckPosition)->GetColor() != m_color)
//			{
//				possibleMoves.insert(toCheckPosition);
//			}
//			break;
//		}
//		possibleMoves.insert(toCheckPosition);
//	}
//}
