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