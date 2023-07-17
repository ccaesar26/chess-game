#include "IChessGame.h"

int main()
{
	std::shared_ptr<class IChessGame> Table = IChessGame::CreateBoard();
	return 0;
}