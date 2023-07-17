#pragma once
#include "Piece.h"

class Pawn : public Piece
{

public:
	
	Pawn(EColor color, Position position);

	void GetMovesPossible(Position currentPos, std::function<PiecePtr(Position)> GetPieceFromBoard, PositionPieceSet& possibleMoves) const override;

};

