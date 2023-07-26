#pragma once

#include "IPiece.h"
#include "IChessGameListener.h"

using IChessGamePtr = std::shared_ptr<class IChessGame>;

class IChessGame
{
public:
	static  IChessGamePtr CreateGame();

	virtual void ResetGame() = 0;

	virtual IPiecePtr GetIPiecePtr(Position pos) const = 0;

	virtual PositionList GetPossibleMoves(Position currentPos) const = 0;

	virtual IPieceList GetCapturedPieces(EColor color) const = 0;

	virtual EColor GetCurrentPlayer() const = 0;

	virtual bool IsGameOver() const = 0;

	virtual void MakeMovement(Position initialPos, Position finalPos) = 0; // Position p1, Position p2

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

	virtual void AddListener(IChessGameListenerPtr listener) = 0;
	virtual void RemoveListener(IChessGameListener* listener) = 0;

	virtual ~IChessGame() = default;
};
