#pragma once

#include "IBoard.h"

using IChessGamePtr = std::shared_ptr<class IChessGame>;

class IChessGame
{

public:

	static IChessGamePtr CreateBoard();

	virtual bool IsGameOver() const = 0;

	virtual void MakeMove(Position initialPos, Position finalPos) = 0;

	virtual IBoardPtr GetBoard() const = 0; 

	virtual IPieceList GetWhitePiecesCaptured() = 0;

	virtual IPieceList GetBlackPiecesCaptured() = 0;

	virtual IPiecePtr GetIPiece(Position pos) const = 0;

	virtual PositionList GetPossibleMoves(Position currentPos)  = 0;

	~IChessGame() = default;

};

