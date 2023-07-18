#include "Piece.h"

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
