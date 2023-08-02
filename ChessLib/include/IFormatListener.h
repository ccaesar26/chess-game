#pragma once

#include "IPiece.h"

class IFormatListener
{
public:
	virtual void OnMoveMade(const std::array<std::array<char, 8>, 8>& board, Position initPos, Position finalPos) = 0;

	virtual ~IFormatListener() = default;
};