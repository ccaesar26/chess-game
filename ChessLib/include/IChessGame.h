#pragma once

#include "IPiece.h"

#include <string>

using IChessGamePtr = std::shared_ptr<class IChessGame>;

struct BoardPosition
{
	char col;
	char row;
	BoardPosition(char c, char r);
};

class IChessGame
{
public:
	static  IChessGamePtr CreateBoard();

	virtual IPiecePtr GetIPiece(char col, int ln) const = 0;
	virtual std::vector<BoardPosition> GetMoves(char col, char row) const = 0;
	virtual IPieceList GetCapturedPieces(EColor color) const = 0;
	virtual EColor GetCurrentPlayer() const = 0;

	virtual bool IsGameOver() const = 0;

	virtual void MakeMovement(char initialColumn, char initialRow, char finalColumn, char finalRow) = 0;

	virtual void UpgradePawn(std::string upgradeType) = 0;
	virtual void RequestDraw() = 0;
	virtual void AcceptDrawProposal() = 0;
	virtual void DeclineDrawProposal() = 0;

	virtual bool IsDraw() const = 0;
	virtual bool IsWaitingForDrawResponse() const = 0;
	virtual bool IsWonByWhitePlayer() const = 0;
	virtual bool IsWonByBlackPlayer() const = 0;
	virtual bool IsWaitingForUpgrade() const = 0;
	virtual bool IsCheckState() const = 0;

	virtual Position ConvertToMemoryPosition(char col, char row) const = 0;
	virtual BoardPosition ConvertToBoardPosition(Position pos) const = 0;

	virtual ~IChessGame() = default;
};

inline BoardPosition::BoardPosition(char c, char r)
	: col(c)
	, row(r)
{
}

