#pragma once
#include "Piece.h"

class Queen : public Piece
{

public:

    Queen(EColor color, Position position);

    void GetMovesPossible(Position currentPos, std::function<PiecePtr(Position)> GetPieceFromBoard, PositionPieceSet& possibleMoves) const override;

};

