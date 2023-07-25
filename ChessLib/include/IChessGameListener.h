#pragma once

class IChessGameListener
{
public:
	virtual void OnMoveMade() const = 0;
	virtual void OnGameOver() const = 0;
	virtual void OnPawnUpgrade() const = 0;
	virtual void OnDrawProposal() const = 0;

	virtual void Update() = 0;

	virtual ~IChessGameListener() = default;
};