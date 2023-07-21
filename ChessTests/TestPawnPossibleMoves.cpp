#include "Utility.h"

#include "gtest/gtest.h"

TEST(TestPawnPossibleMoves, Test_White_Moves_On_Empty_Squares_1)
{
	// Declare board //

	std::array<std::array<char, 8>, 8> alternativeBoard =
	{
		//   0    1    2    3    4    5    6    7

			'K', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 0
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 1		
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 2
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 3
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 4
			' ', ' ', ' ', ' ', ' ', 'P', ' ', 'P',   // 5
			' ', ' ', ' ', ' ', ' ', ' ', 'p', ' ',   // 6
			'k', ' ', ' ', ' ', ' ', ' ', ' ', ' '    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::White);

	PositionList pawnPossibleMoves = game.GetPossibleMoves(Position(6, 6));
	PositionList pawnExpectedMoves = { Position(5,6),Position(4,6),Position(5,5),Position(5,7) };

	EXPECT_EQ(ComparePositionLists(pawnPossibleMoves, pawnExpectedMoves), true);
}

TEST(TestPawnPossibleMoves, Test_White_Moves_On_Empty_Squares_2)
{
	// Declare board //

	std::array<std::array<char, 8>, 8> alternativeBoard =
	{
		//   0    1    2    3    4    5    6    7

			'K', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 0
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 1		
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 2
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 3
			' ', ' ', ' ', ' ', ' ', 'P', ' ', 'P',   // 4
			' ', ' ', ' ', ' ', ' ', ' ', 'p', ' ',   // 5
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 6
			'k', ' ', ' ', ' ', ' ', ' ', ' ', ' '    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::White);

	PositionList pawnPossibleMoves = game.GetPossibleMoves(Position(5, 6));
	PositionList pawnExpectedMoves = { Position(4,6),Position(4,5),Position(4,7) };

	EXPECT_EQ(ComparePositionLists(pawnPossibleMoves, pawnExpectedMoves), true);
}