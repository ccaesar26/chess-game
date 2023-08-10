#pragma once

#include "IPiece.h"
#include "IChessGameListener.h"

#include "IChessGameControl.h"
#include "IChessGameStorage.h"
#include "IChessGameStatus.h"
#include "IChessGameTimedMode.h"

#include <vector>
#include <string>

using IChessGamePtr = std::shared_ptr<class IChessGame>;
using MoveList = std::vector<std::string>;

class IChessGame 
	: public IChessGameControl
	, public IChessGameStorage
	, public IChessGameTimedMode
{
public:

	static  IChessGamePtr CreateGame();
	virtual ~IChessGame() = default;

	virtual void AddListener(IChessGameListenerPtr listener) = 0;
	virtual void RemoveListener(IChessGameListener * listener) = 0;

	virtual const IChessGameStatus* GetStatus() const = 0;
};