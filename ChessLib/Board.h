#pragma once

#include "IBoard.h"
#include "Piece.h"

using ArrayBoard = std::array<std::array<PiecePtr, 8>, 8>;

class Board : public IBoard
{
public:
	Board(std::array<std::array<PiecePtr, 8>, 8> boardArr);

	IPiecePtr At(char column, int row) override;

private:
	ArrayBoard& m_board;
};

