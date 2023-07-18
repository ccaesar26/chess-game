#pragma once
#include "Piece.h"

class Queen : public Piece
{

public:

    Queen(EColor color);

    PositionList GetPossibleMoves(Position currentPos, std::function<PiecePtr(Position)> GetPieceFromBoard) const override;

};

