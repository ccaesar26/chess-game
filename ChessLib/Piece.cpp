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

EType Piece::GetType() const
{
	return m_type;
}

EColor Piece::GetColor() const
{
	return m_color;
}

//Position Piece::GetPosition() const
//{
//	return Position();
//}

//void Piece::SetPosition(Position pos)
//{
//	m_position = pos;
//}

//BoardPosition Piece::GetBoardPosition() const
//{
//	BoardPosition p(8 - m_position.row, m_position.col + 'A');
//	return p;
//}
