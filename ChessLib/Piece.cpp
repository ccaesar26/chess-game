#include "Piece.h"

#include "Bishop.h"
#include "Horse.h"
#include "King.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"

PiecePtr Piece::Produce(EType type, EColor color)
{
	switch (type)
	{
	case EType::Rook:
		return std::make_shared<Rook>(color);
	case EType::Horse:
		return std::make_shared<Horse>(color);
	case EType::King:
		return std::make_shared<King>(color);
	case EType::Queen:
		return std::make_shared<Queen>(color);
	case EType::Bishop:
		return std::make_shared<Bishop>(color);
	case EType::Pawn:
		return std::make_shared<Pawn>(color);
	}
}

Piece::Piece(EColor color, EType name)
	: m_color(color)
	, m_type(name)
{
}

EColor Piece::GetColor() const
{
	return m_color;
}

EType Piece::GetType() const
{
	return m_type;
}

PositionList Piece::GetFinalPositionsFromMovementArray(const std::array<Position, 8>& possibleMovements, 
	std::function<PiecePtr(Position)> GetPieceFromBoard) const
{
	PositionList finalPositions;

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

void Piece::AddFinalPositionsByDirections(const Position& currentPos, Position movingWay, std::function<PiecePtr(Position)> GetPieceFromBoard, PositionList& finalPositions) const
{
	Position limit;
	limit.row = movingWay.row < 0 ? -1 : 8;
	limit.col = movingWay.row < 0 ? -1 : 8;

	for (int i = currentPos.row + movingWay.row, j = currentPos.col + movingWay.col
		;	 i != limit.row && j != limit.col
		;	 i += movingWay.row, j += movingWay.col)
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
}