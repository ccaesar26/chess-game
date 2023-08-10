#pragma once

class IChessGameTimedMode
{
public:
	virtual ~IChessGameTimedMode() = default;

	virtual void EnableTimedMode(int seconds) = 0;
	virtual void Pause() = 0;
	virtual void Resume() = 0;
};
