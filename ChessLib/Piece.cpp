#include "Piece.h"

Piece::Piece(EColor color, EName name, Position position)
	: m_color(color)
	, m_name(name)
	, m_position(position)
{
}

EName Piece::GetName() const
{
	return m_name;
}

EColor Piece::GetColor() const
{
	return m_color;
}

Position Piece::GetPosition() const
{
	return m_position;
}

BoardPosition Piece::GetBoardPosition() const
{
	BoardPosition p(8 - m_position.row, m_position.col + 'A');
	return p;
}
