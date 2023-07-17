#include "King.h"

King::King(EColor color, Position position)
	:Piece(color,EType::King,position)
{}

//void King::GetMovesPossible(Position currentPos, std::function<IPiecePtr(Position)> GetPieceFromBoard, PositionPieceSet& possibleMoves) const
//{
//	std::array<Position, 8> possibleMovements = {
//		Position(currentPos.row + 1, currentPos.col - 1),
//		Position(currentPos.row + 1, currentPos.col    ),
//		Position(currentPos.row + 1, currentPos.col + 1),
//		Position(currentPos.row - 1, currentPos.col - 1),
//		Position(currentPos.row - 1, currentPos.col    ),
//		Position(currentPos.row - 1, currentPos.col + 1),
//		Position(currentPos.row    , currentPos.col - 1),
//		Position(currentPos.row    , currentPos.col + 1)
//	};
//
//	for (auto toCheckPosition : possibleMovements)
//	{
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
