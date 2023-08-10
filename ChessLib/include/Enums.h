#pragma once

enum class EDrawOperation
{
	Request,
	Accept,
	Decline
};

enum class ESide
{
	Queenside,
	Kingside
};

enum class EColor
{
	White, // 0
	Black  // 1
};

enum class EType
{
	Rook,
	Horse,
	King,
	Queen,
	Bishop,
	Pawn
};

enum class EGameResult
{
	WhitePlayerWon,
	BlackPlayerWon,
	Draw
};