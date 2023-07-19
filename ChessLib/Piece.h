#pragma once

#include "IPiece.h"

using PiecePtr = std::shared_ptr<class Piece>;

class Piece : public IPiece
{
public:
	static PiecePtr Produce(EType type, EColor color);

	Piece(EColor color, EType name);

	EType GetType() const override;
	
	EColor GetColor() const override;

	virtual PositionList GetPattern(Position currentPos, std::function<PiecePtr(Position)> GetPieceFromBoard) const = 0;

protected:

	EColor m_color;
	EType m_type;
};