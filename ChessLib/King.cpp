#include "King.h"

King::King(EColor color)
	: Piece(color, EType::King)
{
}

PositionList King::GetPattern(Position currentPos, std::function<PiecePtr(Position)> GetPieceFromBoard) const
{
	PositionList finalPositions;

	std::array<Position, 8> possibleMovements = {
		Position(currentPos.row + 1, currentPos.col - 1),
		Position(currentPos.row + 1, currentPos.col),
		Position(currentPos.row + 1, currentPos.col + 1),
		Position(currentPos.row - 1, currentPos.col - 1),
		Position(currentPos.row - 1, currentPos.col),
		Position(currentPos.row - 1, currentPos.col + 1),
		Position(currentPos.row    , currentPos.col - 1),
		Position(currentPos.row    , currentPos.col + 1)
	};

	for (auto toCheckPosition : possibleMovements)
	{
		if (toCheckPosition.row < 0 || toCheckPosition.row > 7 ||
			toCheckPosition.col < 0 || toCheckPosition.col > 7)
		{
			continue;
		}
		if (GetPieceFromBoard(toCheckPosition))
		{
			if (GetPieceFromBoard(toCheckPosition)->GetColor() != m_color)
			{
				finalPositions.push_back(toCheckPosition);
			}
			continue;
		}
		finalPositions.push_back(toCheckPosition);
	}

	return finalPositions;
}