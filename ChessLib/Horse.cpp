#include "Horse.h"

Horse::Horse(EColor color)
	: Piece(color, EType::Horse)
{

}

PositionList Horse::GetPattern(Position currentPos, std::function<PiecePtr(Position)> GetPieceFromBoard) const
{
	PositionList finalPositions;

	std::array<Position, 8> possibleMovements = {
		Position(currentPos.row + 1, currentPos.col - 2),
		Position(currentPos.row + 2, currentPos.col - 1),
		Position(currentPos.row + 2, currentPos.col + 1),
		Position(currentPos.row + 1, currentPos.col + 2),
		Position(currentPos.row - 1, currentPos.col + 2),
		Position(currentPos.row - 2, currentPos.col + 1),
		Position(currentPos.row - 2, currentPos.col - 1),
		Position(currentPos.row - 1, currentPos.col - 2)
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