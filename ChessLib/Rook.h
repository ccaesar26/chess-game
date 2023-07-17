#pragma once
#include "Piece.h"

class Rook : public Piece
{

public:

	Rook(EColor color, Position position);

	void GetPossibleMoves(Position currentPos, std::function<IPiecePtr(Position)> GetPieceFromBoard, PositionPieceSet& possibleMoves) const override;

};

