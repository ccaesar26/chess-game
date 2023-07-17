#pragma once
#include "Piece.h"

class Queen : public Piece
{

public:

    Queen(EColor color, Position position);

    void GetPossibleMoves(Position currentPos, std::function<IPiecePtr(Position)> GetPieceFromBoard, PositionPieceSet& possibleMoves) const override;

};

