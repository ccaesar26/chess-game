#pragma once

#include "IPiece.h"

using IBoardPtr = std::shared_ptr<class IBoard>;

class IBoard
{
public:
	virtual IPiecePtr At(char column, int row) = 0;

	virtual ~IBoard() = default;
};
