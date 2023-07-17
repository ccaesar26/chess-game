#include "Horse.h"

Horse::Horse(EColor color, Position position)
	: Piece(color, EName::Horse, position)
{

}

void Horse::GetMovesPossible(Position currentPos, std::function<PiecePtr(Position)> GetPieceFromBoard, PositionPieceSet& possibleMoves) const
{
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
		if (GetPieceFromBoard(toCheckPosition))
		{
			if (GetPieceFromBoard(toCheckPosition)->GetColor() != m_color)
			{
				possibleMoves.insert(toCheckPosition);
			}
			break;
		}
		possibleMoves.insert(toCheckPosition);
	}
}
