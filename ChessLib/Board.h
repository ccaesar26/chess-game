#pragma once
#include "IBoard.h"
#include "Piece.h"

class Board : public IBoard
{
public:
	Board(std::array<std::array<PiecePtr, 8>, 8>& board);

	IPiecePtr GetElem(int i, int j) override;

private:
	std::array<std::array<PiecePtr, 8>, 8>& m_board;
};

