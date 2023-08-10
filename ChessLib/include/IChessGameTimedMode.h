#pragma once

class IChessGameTimedMode
{
public:
	virtual ~IChessGameTimedMode() = default;

	virtual void EnableTimedMode(int seconds) = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual int GetRemainingTime(EColor color) const = 0;

	virtual bool IsPaused() const = 0;
};
