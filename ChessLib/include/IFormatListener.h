#pragma once

#include "IPiece.h"

class IFormatListener
{
public:
	//virtual void OnMoveMade(Position initPos, Position finalPos, ) = 0;

	virtual ~IFormatListener() = default;
};