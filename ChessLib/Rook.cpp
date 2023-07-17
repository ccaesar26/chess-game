#include "Rook.h"

Rook::Rook(EColor color, Position position)
	:Piece(color,EName::Rook,position)
{}

void Rook::GetMovesPossible(Position currentPos, std::function<PiecePtr(Position)> GetPieceFromBoard, PositionPieceSet& possibleMoves) const
{
	for (int iRow = currentPos.row - 1; iRow >= 0; iRow--)
	{
		Position toCheckPosition(iRow, currentPos.col);
		if (GetPieceFromBoard(toCheckPosition) != nullptr)
		{
			if(GetPieceFromBoard(toCheckPosition)->GetColor() != m_color) possibleMoves.insert(toCheckPosition);
			break;
		}
		else possibleMoves.insert(toCheckPosition);
	}

	for (int iRow = currentPos.row + 1; iRow <= 7; iRow++)
	{
		Position toCheckPosition(iRow, currentPos.col);
		if (GetPieceFromBoard(toCheckPosition) != nullptr)
		{
			if (GetPieceFromBoard(toCheckPosition)->GetColor() != m_color) possibleMoves.insert(toCheckPosition);
			break;
		}
		else possibleMoves.insert(toCheckPosition);
	}

	for (int iCol = currentPos.col - 1; iCol >= 0; iCol--)
	{
		Position toCheckPosition(currentPos.row, iCol);
		if (GetPieceFromBoard(toCheckPosition) != nullptr)
		{
			if (GetPieceFromBoard(toCheckPosition)->GetColor() != m_color) possibleMoves.insert(toCheckPosition);
			break;
		}
		else possibleMoves.insert(toCheckPosition);
	}

	for (int iCol = currentPos.col + 1; iCol <= 7; iCol++)
	{
		Position toCheckPosition(currentPos.row, iCol);
		if (GetPieceFromBoard(toCheckPosition) != nullptr)
		{
			if (GetPieceFromBoard(toCheckPosition)->GetColor() != m_color) possibleMoves.insert(toCheckPosition);
			break;
		}
		else possibleMoves.insert(toCheckPosition);
	}

}

