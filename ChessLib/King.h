#pragma once
#include "Piece.h"

class King : public Piece
{

public:
	
	King(EColor color);

	PositionList GetPossibleMoves(Position currentPos, std::function<PiecePtr(Position)> GetPieceFromBoard) const override;

};

