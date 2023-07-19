#pragma once

#include "IPiece.h"

using PiecePtr = std::shared_ptr<class Piece>;
using PieceList = std::vector<PiecePtr>;

class Piece : public IPiece
{
public:
	static PiecePtr Produce(EType type, EColor color);

	Piece(EColor color, EType name);

	EColor GetColor() const override;
	EType GetType() const override;

	virtual PositionList GetPattern(Position currentPos, std::function<PiecePtr(Position)> GetPieceFromBoard) const = 0;

protected:

	EColor m_color;
	EType m_type;
};