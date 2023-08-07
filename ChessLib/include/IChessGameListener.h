#pragma once

#include "IPiece.h"

#include <string>

enum class EGameResult
{
	WhitePlayerWon,
	BlackPlayerWon,
	Draw
};

class IChessGameListener
{
public:
	virtual void OnMoveMade(Position init, Position fin) = 0;

	virtual void OnGameOver(EGameResult result) = 0;
	
	virtual void OnPawnUpgrade(Position pos) = 0;
	
	virtual void OnCheck() = 0;
	
	virtual void OnGameRestarted() = 0;

	virtual void OnHistoryUpdate(std::string move) = 0;

	virtual void OnClockUpdate() = 0;

	virtual ~IChessGameListener() = default;
};

using IChessGameListenerWeakPtr = std::weak_ptr<IChessGameListener>;
using IChessGameListenerPtr = std::shared_ptr<IChessGameListener>;