#pragma once

#include "IPiece.h"

class IBoard
{
public:
	virtual IPiecePtr GetElem(int i, int j) = 0;

	virtual ~IBoard() = default;
};
