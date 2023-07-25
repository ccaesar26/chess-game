#pragma once

class IChessGameListener
{
public:
	virtual void OnMoveMade(int ir, int ic, int fr, int fc) = 0;
	virtual void OnGameOver() = 0;
	virtual void OnPawnUpgrade() = 0;
	virtual void OnCheckState() = 0;

	virtual ~IChessGameListener() = default;
};