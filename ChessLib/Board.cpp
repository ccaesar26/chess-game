#include "Board.h"

Board::Board(std::array<std::array<PiecePtr, 8>, 8> boardArr)
	: m_board(boardArr)
{
	
}

IPiecePtr Board::GetElem(int i, int j)
{
	//throw std::logic_error("The method or operation is not implemented.");
	return /*std::make_shared<IPiece>*/(m_board[i][j]);
}
