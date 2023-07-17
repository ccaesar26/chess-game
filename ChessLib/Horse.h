#pragma once

#include "Piece.h"

class Horse : public Piece
{
public:
    Horse(EColor color, Position position);

	void GetMovesPossible(Position currentPos, std::function<PiecePtr(Position)> GetPieceFromBoard, PositionPieceSet& possibleMoves) const override;

};

