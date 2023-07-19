#pragma once

#include "IPiece.h"

using IChessGamePtr = std::shared_ptr<class IChessGame>;

class IChessGame
{

public:

	static IChessGamePtr CreateBoard();

	virtual bool IsGameOver() = 0;

	virtual void MakeMovement(char initialColumn, int initialRow, char finalColumn, int finalRow) = 0;

	virtual IPieceList GetWhitePiecesCaptured() = 0;
	virtual IPieceList GetBlackPiecesCaptured() = 0;

	virtual IPiecePtr GetIPiece(char col, int ln) const = 0;

	virtual PositionList GetPossibleMoves(Position currentPos) = 0;

	virtual EColor GetCurrentPlayer() const = 0;

	~IChessGame() = default;

};

