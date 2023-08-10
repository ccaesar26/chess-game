#pragma once

#include <utility>
#include <vector>

struct Position
{
	int row, col;

	Position(int r = 0, int c = 0);
	Position(std::pair<int, int> p);

	std::pair<int, int> ToPair();

	bool operator==(const Position& P) const;

	bool operator!=(const Position& P) const;
};

inline Position::Position(int r, int c)
	: row(r)
	, col(c)
{
}

inline Position::Position(std::pair<int, int> p)
	: row(p.first)
	, col(p.second)
{
}

inline std::pair<int, int> Position::ToPair()
{
	return std::make_pair(row, col);
}

inline bool Position::operator==(const Position& P) const
{
	return (row == P.row && col == P.col);
}

inline bool Position::operator!=(const Position& P) const
{
	return (row != P.row || col != P.col);
}

using PositionList = std::vector<Position>;