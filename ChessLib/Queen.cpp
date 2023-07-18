#include "Queen.h"

Queen::Queen(EColor color)
	: Piece(color, EType::Queen)
{

}

PositionList Queen::GetPossibleMoves(Position currentPos, std::function<PiecePtr(Position)> GetPieceFromBoard) const
{
	//// upper left
	//for (int i = currentPos.row - 1, j = currentPos.col - 1; i >= 0 && j >= 0; i--, j--)
	//{
	//	Position toCheckPosition(i, j);
	//	if (GetPieceFromBoard(toCheckPosition))
	//	{
	//		if (GetPieceFromBoard(toCheckPosition)->GetColor() != m_color)
	//		{
	//			possibleMoves.insert(toCheckPosition);
	//		}
	//		break;
	//	}
	//	possibleMoves.insert(toCheckPosition);
	//}
	//// upper right
	//for (int i = currentPos.row - 1, j = currentPos.col + 1; i >= 0 && j < 8; i--, j++)
	//{
	//	Position toCheckPosition(i, j);
	//	if (GetPieceFromBoard(toCheckPosition))
	//	{
	//		if (GetPieceFromBoard(toCheckPosition)->GetColor() != m_color)
	//		{
	//			possibleMoves.insert(toCheckPosition);
	//		}
	//		break;
	//	}
	//	possibleMoves.insert(toCheckPosition);
	//}
	//// lower left
	//for (int i = currentPos.row + 1, j = currentPos.col - 1; i < 8 && j >= 0; i++, j--)
	//{
	//	Position toCheckPosition(i, j);
	//	if (GetPieceFromBoard(toCheckPosition))
	//	{
	//		if (GetPieceFromBoard(toCheckPosition)->GetColor() != m_color)
	//		{
	//			possibleMoves.insert(toCheckPosition);
	//		}
	//		break;
	//	}
	//	possibleMoves.insert(toCheckPosition);
	//}
	//// lower right
	//for (int i = currentPos.row + 1, j = currentPos.col + 1; i < 8 && j < 8; i++, j++)
	//{
	//	Position toCheckPosition(i, j);
	//	if (GetPieceFromBoard(toCheckPosition))
	//	{
	//		if (GetPieceFromBoard(toCheckPosition)->GetColor() != m_color)
	//		{
	//			possibleMoves.insert(toCheckPosition);
	//		}
	//		break;
	//	}
	//	possibleMoves.insert(toCheckPosition);
	//}
	//// up
	//for (int iRow = currentPos.row - 1; iRow >= 0; iRow--)
	//{
	//	Position toCheckPosition(iRow, currentPos.col);
	//	if (GetPieceFromBoard(toCheckPosition))
	//	{
	//		if (GetPieceFromBoard(toCheckPosition)->GetColor() != m_color)
	//		{
	//			possibleMoves.insert(toCheckPosition);
	//		}
	//		break;
	//	}
	//	else possibleMoves.insert(toCheckPosition);
	//}
	//// down
	//for (int iRow = currentPos.row + 1; iRow <= 7; iRow++)
	//{
	//	Position toCheckPosition(iRow, currentPos.col);
	//	if (GetPieceFromBoard(toCheckPosition))
	//	{
	//		if (GetPieceFromBoard(toCheckPosition)->GetColor() != m_color)
	//		{
	//			possibleMoves.insert(toCheckPosition);
	//		}
	//		break;
	//	}
	//	else possibleMoves.insert(toCheckPosition);
	//}
	//// left
	//for (int iCol = currentPos.col - 1; iCol >= 0; iCol--)
	//{
	//	Position toCheckPosition(currentPos.row, iCol);
	//	if (GetPieceFromBoard(toCheckPosition))
	//	{
	//		if (GetPieceFromBoard(toCheckPosition)->GetColor() != m_color)
	//		{
	//			possibleMoves.insert(toCheckPosition);
	//		}
	//		break;
	//	}
	//	else possibleMoves.insert(toCheckPosition);
	//}
	//// right
	//for (int iCol = currentPos.col + 1; iCol <= 7; iCol++)
	//{
	//	Position toCheckPosition(currentPos.row, iCol);
	//	if (GetPieceFromBoard(toCheckPosition))
	//	{
	//		if (GetPieceFromBoard(toCheckPosition)->GetColor() != m_color)
	//		{
	//			possibleMoves.insert(toCheckPosition);
	//		}
	//		break;
	//	}
	//	else possibleMoves.insert(toCheckPosition);
	//}
}