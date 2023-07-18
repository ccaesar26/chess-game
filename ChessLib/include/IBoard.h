#pragma once

#include "IPiece.h"

using IBoardPtr = std::shared_ptr<class IBoard>;

class IBoard
{
public:
	virtual IPiecePtr GetElem(int i, int j) = 0;

	virtual ~IBoard() = default;
};
