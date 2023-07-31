#pragma once

#include "IPiece.h"
#include "IChessGameListener.h"

#include <vector>
#include <string>

using IChessGamePtr = std::shared_ptr<class IChessGame>;
using MoveList = std::vector<std::string>;
using CharBoard = std::array<std::array<char, 8>, 8>;
using CastleValues = std::array<std::array<bool, 2>, 2>;

class IChessGame
{
public:
	static  IChessGamePtr CreateGame();

	virtual void ResetGame() = 0;
	virtual void RestoreGame(const CharBoard& inputConfig, EColor turn = EColor::White, CastleValues castle = { true, true, true, true }) = 0;

	virtual IPiecePtr GetIPiecePtr(Position pos) const = 0;

	virtual PositionList GetPossibleMoves(Position currentPos) const = 0;

	virtual IPieceList GetCapturedPieces(EColor color) const = 0;

	virtual EColor GetCurrentPlayer() const = 0;

	virtual MoveList GetMoveHistory() const = 0;

	virtual bool IsGameOver() const = 0;

	virtual void MakeMove(Position initialPos, Position finalPos) = 0; // Position p1, Position p2

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

	virtual bool IsWhiteKingsideCastlingAvailable() const = 0;
	virtual bool IsWhiteQueensideCastlingAvailable() const = 0;
	virtual bool IsBlackKingsideCastlingAvailable() const = 0;
	virtual bool IsBlackQueensideCastlingAvailable() const = 0;

	virtual void AddListener(IChessGameListenerPtr listener) = 0;
	virtual void RemoveListener(IChessGameListener* listener) = 0;

	virtual ~IChessGame() = default;
};