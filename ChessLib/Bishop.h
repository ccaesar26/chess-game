#pragma once
#include "Piece.h"

class Bishop : public Piece
{

public:

    Bishop(EColor color, Position position);

    //void GetMovesPossible(Position currentPos, std::function<IPiecePtr(Position)> GetPieceFromBoard, PositionPieceSet& possibleMoves) const override;

};

