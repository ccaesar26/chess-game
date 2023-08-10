#pragma once

#include "Enums.h"
#include "Position.h"
#include "IPiece.h"

#include <array>

using CastleValues = std::array<std::array<bool, 2>, 2>;
using CharBoard = std::array<std::array<char, 8>, 8>;

class IChessGameControl
{
public:
	virtual ~IChessGameControl() = default;

	virtual void ResetGame() = 0;
	virtual void RestoreGame(const CharBoard& inputConfig, EColor turn = EColor::White, CastleValues castle = { true, true, true, true }) = 0;

	virtual void MakeMove(Position initialPos, Position finalPos, bool EnableNotification = true, EType upgradeType = EType::Pawn) = 0;
	virtual void UpgradePawn(EType upgradeType) = 0;
	virtual void DrawOperation(EDrawOperation op) = 0;
};
