#pragma once

class IChessGameListener
{
public:
	virtual void OnMoveMade(int ir, int ic, int fr, int fc) = 0; // position
	virtual void OnGameOver() = 0; // winner/ draw enum
	virtual void OnPawnUpgrade() = 0; // params... int int etype
	virtual void OnCheck() = 0;
	virtual void OnGameRestarted() = 0;

	virtual ~IChessGameListener() = default;
};