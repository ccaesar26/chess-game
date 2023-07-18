#include "Board.h"

Board::Board(std::array<std::array<PiecePtr, 8>, 8> boardArr)
	: m_board(boardArr)
{
	
}

IPiecePtr Board::At(char column, int row)
{
	if (column >= 'a')
	{
		return m_board[8 - row][column - 'a'];
	}
	return m_board[8 - row][column - 'A'];
}
