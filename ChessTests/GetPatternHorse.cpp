#include "gtest/gtest.h"

#include "ChessGame.h"

TEST(HorsePossibleMoves, Test1)
{
	std::array<std::array<char, 8>, 8> alternativeBoard;

	// Declare board // 

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			alternativeBoard[i][j] = ' ';

	alternativeBoard[4][3] = 'h';
	alternativeBoard[0][0] = 'k';
	alternativeBoard[7][7] = 'K';

	// Tests //

	ChessGame game(alternativeBoard, EColor::White);

	PositionList horsepossibleMoves = game.GetPossibleMoves(Position(4,3));
	PositionList expectedHorseMoves = { Position(2,2),Position(2, 4) ,Position(3, 1) ,Position(3, 5), Position(5, 1) ,Position(5, 5),Position(6, 2),Position(6, 4) };

	for (int i = 0; i < horsepossibleMoves.size(); i++)
	{
		EXPECT_EQ(horsepossibleMoves[i], expectedHorseMoves[i]);
	}

	
}