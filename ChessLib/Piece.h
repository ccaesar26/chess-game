#pragma once

#include "IPiece.h"

using PiecePtr = std::shared_ptr<class Piece>;

class Piece : public IPiece
{

public:

	Piece(EColor color, EType name, Position position);

	EType GetType() const override;
	
	EColor GetColor() const override;

	Position GetPosition() const;

	void SetPosition(Position pos);

	

	virtual PositionList GetPossibleMoves(Position currentPos, std::function<PiecePtr(Position)> GetPieceFromBoard) const = 0;

protected:

	EColor m_color;
	EType m_name;
};