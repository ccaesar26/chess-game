#pragma once

#include "IPiece.h"

using Board = std::array < std::array<PiecePtr, 8>, 8>;


class Piece : public IPiece
{

public:

	Piece(EColor color, EName name, Position position);

	EName GetName() const override;
	
	EColor GetColor() const override;

	Position GetPosition() const;

	void SetPosition(Position pos);

	BoardPosition GetBoardPosition() const override;

	//virtual void GetMovesPossible(Position currentPos, std::function<PiecePtr(Position)> GetPieceFromBoard, PositionPieceSet& possibleMoves) const = 0;

protected:

	Position m_position;
	EColor m_color;
	EName m_name;
};