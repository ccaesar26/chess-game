#pragma once

#include <memory>
#include <array>
#include <unordered_set>
#include <functional>

using PiecePtr = std::shared_ptr<class IPiece>;

struct Position
{
	int row, col;

	Position(int r = 0, int c = 0);

	bool operator==(const Position& P) const;
};

inline Position::Position(int r, int c)
	: row(r)
	, col(c)
{}

inline bool Position::operator==(const Position & P) const
{
	return (row == P.row && col == P.col);
}

struct HashFunctor
{
	bool operator()(const Position& pos) const
	{
		return pos.row ^ pos.col;
	}
};

using PositionPieceSet = std::unordered_set<Position, HashFunctor>;

enum class EColor
{
	White,
	Black
};

enum class EName
{
	Rook,
	Horse,
	King,
	Queen,
	Bishop,
	Pawn
};

struct BoardPosition
{
	int row;
	char col;

	BoardPosition(int r, char c);

};

inline BoardPosition::BoardPosition(int r, char c)
	: row(r)
	, col(c)
{}

class IPiece
{

public:

	virtual EColor GetColor() const = 0;

	virtual BoardPosition GetBoardPosition() const = 0;

	virtual EName GetName() const = 0; 

	virtual void GetMovesPossible(Position currentPos, std::function<PiecePtr(Position)> GetPieceFromBoard, PositionPieceSet& possibleMoves) const = 0;

};