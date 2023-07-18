#pragma once
#include "Piece.h"

class Rook : public Piece
{

public:

	Rook(EColor color);

	PositionList GetPossibleMoves(Position currentPos, std::function<PiecePtr(Position)> GetPieceFromBoard) const override;

};

