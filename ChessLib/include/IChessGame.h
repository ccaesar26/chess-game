#pragma once

#include "IPiece.h"
#include "IChessGameListener.h"

#include <vector>
#include <string>

using IChessGamePtr = std::shared_ptr<class IChessGame>;
using MoveList = std::vector<std::string>;
using CharBoard = std::array<std::array<char, 8>, 8>;
using CastleValues = std::array<std::array<bool, 2>, 2>;

enum class EDrawOperation
{
	Request,
	Accept,
	Decline
};

enum class ESide
{
	Queenside,
	Kingside
};

class IChessGame
{
public:
	static  IChessGamePtr CreateGame();

	virtual void StartGame(const int& timerSeconds = -1) = 0;

	virtual void ResetGame() = 0;
	virtual void RestoreGame(const CharBoard& inputConfig, EColor turn = EColor::White, CastleValues castle = { true, true, true, true }) = 0;

	//virtual void CopyGame(const ChessGame& game) = 0;

	virtual IPiecePtr GetIPiecePtr(Position pos) const = 0;
	virtual PositionList GetPossibleMoves(Position currentPos) const = 0;
	virtual IPieceList GetCapturedPieces(EColor color) const = 0;
	virtual EColor GetCurrentPlayer() const = 0;
	virtual CharBoard GetBoardAtIndex(int index) const = 0;
	virtual int GetNumberOfMoves() const = 0;

	virtual bool LoadPGNFromFile(const std::string& fileName) = 0;
	virtual bool SavePGNFormat(const std::string& fileName) const = 0;
	virtual std::string GetPGNFormat() const = 0;

	virtual void MakeMove(Position initialPos, Position finalPos, bool EnableNotification = true, EType upgradeType = EType::Pawn) = 0;

	virtual void UpgradePawn(EType upgradeType) = 0;
	
	virtual void DrawOperation(EDrawOperation op) = 0;

	virtual bool IsGameOver() const = 0;
	virtual bool IsDraw() const = 0;
	virtual bool IsWaitingForDrawResponse() const = 0;

	virtual bool IsWon(EColor player) const = 0;
	virtual bool IsWaitingForUpgrade() const = 0;
	virtual bool IsCheckState() const = 0;

	virtual bool IsCastlingAvailable(EColor color, ESide side) const = 0;

	virtual void AddListener(IChessGameListenerPtr listener) = 0;
	virtual void RemoveListener(IChessGameListener* listener) = 0;

	virtual int GetRemainingTime(EColor color) = 0;
	//virtual void StopTimers() = 0;

	virtual ~IChessGame() = default;
};