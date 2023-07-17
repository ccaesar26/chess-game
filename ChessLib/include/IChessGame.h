#pragma once

#include "IPiece.h"

using Board = std::array<std::array<PiecePtr, 8>, 8>;

using IChessGamePtr = std::shared_ptr<class IChessGame>;

using PieceSet = std::unordered_set<PiecePtr>;

class IChessGame
{

public:

	static IChessGamePtr CreateBoard();

	virtual bool IsGameOver() const = 0;

	virtual void PlayTurn(BoardPosition initialPos, BoardPosition finalPos) = 0;

	virtual Board GetBoard() const = 0;

	virtual PieceSet GetWhitePiecesAlive() = 0;

	virtual PieceSet GetBlackPiecesAlive() = 0;

	virtual PieceSet GetWhitePiecesCaptured() = 0;

	virtual PieceSet GetBlackPiecesCaptured() = 0;

	~IChessGame() = default;

};

