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

TEST(HorsePossibleMoves, Test2)
{
	// Declare board // 

	std::array<std::array<char, 8>, 8> alternativeBoard =
	{
		//   0    1    2    3    4    5    6    7

			'K', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 0
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 1		
			' ', ' ', 'p', ' ', 'p', ' ', ' ', ' ',   // 2
			' ', 'p', ' ', ' ', ' ', 'p', ' ', ' ',   // 3
			' ', ' ', ' ', 'h', ' ', ' ', ' ', ' ',   // 4
			' ', 'p', ' ', ' ', ' ', 'p', ' ', ' ',   // 5
			' ', ' ', 'p', ' ', 'p', ' ', ' ', ' ',   // 6
			'k', ' ', ' ', ' ', ' ', ' ', ' ', ' '    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::White);

	PositionList horsepossibleMoves = game.GetPossibleMoves(Position(4, 3));
	EXPECT_EQ(horsepossibleMoves.size(), 0);
}