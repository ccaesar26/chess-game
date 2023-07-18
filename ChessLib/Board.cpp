#include "Board.h"

Board::Board(std::array<std::array<PiecePtr, 8>, 8>& board)
	: m_board(board)
{
	
}

IPiecePtr Board::GetElem(int i, int j)
{
	//throw std::logic_error("The method or operation is not implemented.");
	return m_board[i][j];
}
