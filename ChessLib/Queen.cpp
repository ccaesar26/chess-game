#include "Queen.h"

Queen::Queen(EColor color)
	: Piece(color, EType::Queen)
{

}

PositionList Queen::GetPattern(Position currentPos, std::function<PiecePtr(Position)> GetPieceFromBoard) const
{
	PositionList finalPositions;

	// upper left
	for (int i = currentPos.row - 1, j = currentPos.col - 1; i >= 0 && j >= 0; i--, j--)
	{
		Position toCheckPosition(i, j);
		if (GetPieceFromBoard(toCheckPosition))
		{
			if (GetPieceFromBoard(toCheckPosition)->GetColor() != m_color)
			{
				finalPositions.push_back(toCheckPosition);
			}
			break;
		}
		finalPositions.push_back(toCheckPosition);
	}
	// upper right
	for (int i = currentPos.row - 1, j = currentPos.col + 1; i >= 0 && j < 8; i--, j++)
	{
		Position toCheckPosition(i, j);
		if (GetPieceFromBoard(toCheckPosition))
		{
			if (GetPieceFromBoard(toCheckPosition)->GetColor() != m_color)
			{
				finalPositions.push_back(toCheckPosition);
			}
			break;
		}
		finalPositions.push_back(toCheckPosition);
	}
	// lower left
	for (int i = currentPos.row + 1, j = currentPos.col - 1; i < 8 && j >= 0; i++, j--)
	{
		Position toCheckPosition(i, j);
		if (GetPieceFromBoard(toCheckPosition))
		{
			if (GetPieceFromBoard(toCheckPosition)->GetColor() != m_color)
			{
				finalPositions.push_back(toCheckPosition);
			}
			break;
		}
		finalPositions.push_back(toCheckPosition);
	}
	// lower right
	for (int i = currentPos.row + 1, j = currentPos.col + 1; i < 8 && j < 8; i++, j++)
	{
		Position toCheckPosition(i, j);
		if (GetPieceFromBoard(toCheckPosition))
		{
			if (GetPieceFromBoard(toCheckPosition)->GetColor() != m_color)
			{
				finalPositions.push_back(toCheckPosition);
			}
			break;
		}
		finalPositions.push_back(toCheckPosition);
	}

	// up
	for (int i = currentPos.row - 1; i >= 0; i--)
	{
		Position toCheckPosition(i, currentPos.col);
		if (GetPieceFromBoard(toCheckPosition))
		{
			if (GetPieceFromBoard(toCheckPosition)->GetColor() != m_color)
			{
				finalPositions.push_back(toCheckPosition);
			}
			break;
		}
		finalPositions.push_back(toCheckPosition);
	}

	// down
	for (int i = currentPos.row + 1; i < 8; i++)
	{
		Position toCheckPosition(i, currentPos.col);
		if (GetPieceFromBoard(toCheckPosition))
		{
			if (GetPieceFromBoard(toCheckPosition)->GetColor() != m_color)
			{
				finalPositions.push_back(toCheckPosition);
			}
			break;
		}
		finalPositions.push_back(toCheckPosition);
	}

	// left
	for (int j = currentPos.col - 1; j >= 0; j--)
	{
		Position toCheckPosition(currentPos.row, j);
		if (GetPieceFromBoard(toCheckPosition))
		{
			if (GetPieceFromBoard(toCheckPosition)->GetColor() != m_color)
			{
				finalPositions.push_back(toCheckPosition);
			}
			break;
		}
		finalPositions.push_back(toCheckPosition);
	}

	// right
	for (int j = currentPos.col + 1; j < 8; j++)
	{
		Position toCheckPosition(currentPos.row, j);
		if (GetPieceFromBoard(toCheckPosition))
		{
			if (GetPieceFromBoard(toCheckPosition)->GetColor() != m_color)
			{
				finalPositions.push_back(toCheckPosition);
			}
			break;
		}
		finalPositions.push_back(toCheckPosition);
	}

	return finalPositions;
}