#pragma once

class IChessGameListener
{
public:
	virtual void OnMoveMade(int ir, int ic, int fr, int fc) const = 0;
	virtual void OnGameOver() const = 0;
	virtual void OnPawnUpgrade(int r, int c, char t) const = 0;
	virtual void OnDrawProposal() const = 0;

	virtual ~IChessGameListener() = default;
};