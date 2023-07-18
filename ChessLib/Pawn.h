#pragma once
#include "Piece.h"

class Pawn : public Piece
{

public:
	
	Pawn(EColor color);

	PositionList GetPossibleMoves(Position currentPos, std::function<PiecePtr(Position)> GetPieceFromBoard) const override;

};

