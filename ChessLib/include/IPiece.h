#pragma once

#include <memory>
#include <array>
#include <vector>
#include <functional>

using PositionList = std::vector<Position>;

enum class EColor
{
	White,
	Black
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

struct Position
{
	int row, col;

	Position(int r = 0, int c = 0);

	bool operator==(const Position& P) const;
};

class IPiece
{

public:

	virtual EColor GetColor() const = 0;

	virtual EType GetType() const = 0; 

	// virtual void GetMovesPossible(Position currentPos, std::function<IPiecePtr(Position)> GetPieceFromBoard, PositionPieceSet& possibleMoves) const = 0;

};

using IPiecePtr = std::shared_ptr<IPiece>;
using IPieceList = std::vector<IPiece>;

inline Position::Position(int r, int c)
	: row(r)
	, col(c)
{}

inline bool Position::operator==(const Position& P) const
{
	return (row == P.row && col == P.col);
}