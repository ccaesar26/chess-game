#include "Piece.h"

Piece::Piece(EColor color, EType name)
	: m_color(color)
	, m_name(name)
{
}

EType Piece::GetType() const
{
	return m_name;
}

EColor Piece::GetColor() const
{
	return m_color;
}

//void Piece::SetPosition(Position pos)
//{
//	m_position = pos;
//}

//BoardPosition Piece::GetBoardPosition() const
//{
//	BoardPosition p(8 - m_position.row, m_position.col + 'A');
//	return p;
//}
