#pragma once
#include "Piece.h"

class King : public Piece
{

public:
	
	King(EColor color, Position position);

	//void GetMovesPossible(Position currentPos, std::function<IPiecePtr(Position)> GetPieceFromBoard, PositionPieceSet& possibleMoves) const override;

};

