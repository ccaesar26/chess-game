#pragma once

#include <memory>
#include <array>
#include <vector>
#include <functional>

struct Position
{
	int row, col;

	Position(int r = 0, int c = 0);

	bool operator==(const Position& P) const;

	bool operator!=(const Position& P) const;
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

class IPiece
{
public:
	virtual EColor GetColor() const = 0;
	virtual EType GetType() const = 0; 
};

inline Position::Position(int r, int c)
	: row(r)
	, col(c)
{}

inline bool Position::operator==(const Position& P) const
{
	return (row == P.row && col == P.col);
}

inline bool Position::operator!=(const Position& P) const
{
	return (row != P.row || col != P.col);
}

using PositionList = std::vector<Position>;
using IPiecePtr = std::shared_ptr<IPiece>;
using IPieceList = std::vector<IPiecePtr>;