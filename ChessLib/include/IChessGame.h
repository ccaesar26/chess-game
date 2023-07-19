#pragma once

#include "IPiece.h"

using IChessGamePtr = std::shared_ptr<class IChessGame>;

struct BoardPosition
{
	char col;
	int row;
	BoardPosition(char c, int r);
};

class IChessGame
{
public:
	static  IChessGamePtr CreateBoard();

	virtual IPiecePtr GetIPiece(char col, int ln) const = 0;
	virtual std::vector<BoardPosition> GetMoves(char col, int row) const = 0;
	virtual IPieceList GetCapturedPieces(EColor color) const = 0;
	virtual EColor GetCurrentPlayer() const = 0;

	virtual bool IsGameOver() const = 0;

	virtual void MakeMovement(char initialColumn, int initialRow, char finalColumn, int finalRow) = 0;

	virtual ~IChessGame() = default;
};

inline BoardPosition::BoardPosition(char c, int r)
	: col(c)
	, row(r)
{
}

