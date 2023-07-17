#pragma once
#include "Piece.h"

class Rook : public Piece
{

public:

	Rook(EColor color, Position position);

	void GetMovesPossible(Position currentPos, std::function<PiecePtr(Position)> GetPieceFromBoard, PositionPieceSet& possibleMoves) const override;

};

