#pragma once

#include "Enums.h"
#include "Position.h"

#include <memory>
#include <array>
#include <vector>
#include <functional>

class IPiece
{
public:
	virtual EColor GetColor() const = 0;
	virtual EType GetType() const = 0;

	virtual ~IPiece() = default;
};

using IPiecePtr = std::shared_ptr<IPiece>;
using IPieceList = std::vector<IPiecePtr>;