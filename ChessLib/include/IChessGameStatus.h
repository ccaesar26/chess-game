#pragma once

#include "Enums.h"

class IChessGameStatus
{
public:
	virtual ~IChessGameStatus() = default;

	virtual IPiecePtr GetIPiecePtr(Position pos) const = 0;
	virtual PositionList GetPossibleMoves(Position currentPos) const = 0;
	virtual IPieceList GetCapturedPieces(EColor color) const = 0;
	virtual EColor GetCurrentPlayer() const = 0;
	virtual CharBoard GetBoardAtIndex(int index) const = 0;
	virtual int GetNumberOfMoves() const = 0;

	virtual bool IsGameOver() const = 0;
	virtual bool IsDraw() const = 0;
	virtual bool IsWaitingForDrawResponse() const = 0;
	virtual bool IsWon(EColor player) const = 0;
	virtual bool IsWaitingForUpgrade() const = 0;
	virtual bool IsCheckState() const = 0;
	virtual bool IsCastlingAvailable(EColor color, ESide side) const = 0;
};