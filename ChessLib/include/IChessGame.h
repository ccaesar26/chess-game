#pragma once

#include "IPiece.h"
#include "IChessGameListener.h"

#include <string>

using IChessGamePtr = std::shared_ptr<class IChessGame>;

using IChessGameListenerWeakPtr = std::weak_ptr<IChessGameListener>;
using IChessGameListenerPtr = std::shared_ptr<IChessGameListener>;

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

	virtual void ResetGame() = 0;

	virtual IPiecePtr GetIPiecePtr(int row, int col) const = 0;
	virtual std::vector<std::pair<int, int>> GetMoves(int row, int col) const = 0;
	virtual IPieceList GetCapturedPieces(EColor color) const = 0;
	virtual EColor GetCurrentPlayer() const = 0;

	virtual bool IsGameOver() const = 0;

	virtual void MakeMovement(int initialRow, int initialColumn, int finalRow, int finalColumn) = 0;

	virtual void UpgradePawn(EType upgradeType) = 0;
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

	virtual void AddListener(IChessGameListenerPtr listener) = 0;
	virtual void RemoveListener(IChessGameListenerPtr listener) = 0;

	virtual ~IChessGame() = default;
};

inline BoardPosition::BoardPosition(char c, char r)
	: col(c)
	, row(r)
{
}

