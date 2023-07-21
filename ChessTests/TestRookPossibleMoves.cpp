#include "Utility.h"

#include "gtest/gtest.h"

TEST(TestRookPossibleMoves, Test_Moves_On_Empty_Squares)
{
	// Declare board //

	std::array<std::array<char, 8>, 8> alternativeBoard =
	{
		//   0    1    2    3    4    5    6    7

			'K', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 0
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 1		
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 2
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 3
			' ', ' ', ' ', 'r', ' ', ' ', ' ', ' ',   // 4
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 5
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 6
			'k', ' ', ' ', ' ', ' ', ' ', ' ', ' '    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::White);

	PositionList rookPossibleMoves = game.GetPossibleMoves(Position(4, 3));
	PositionList rookExpectedMoves = { Position(3, 3),Position(2, 3),Position(1, 3),Position(0, 3),Position(5, 3),Position(6, 3),Position(7, 3),
		Position(4, 2),Position(4, 1),Position(4, 0),Position(4, 4),Position(4, 5),Position(4, 6),Position(4, 7) };

	EXPECT_EQ(ComparePositionLists(rookPossibleMoves, rookExpectedMoves), true);
}

TEST(TestRookPossibleMoves, Test_Moves_On_Ocupied_Squares_With_Same_Color)
{
	// Declare board //

	std::array<std::array<char, 8>, 8> alternativeBoard =
	{
		//   0    1    2    3    4    5    6    7

			'K', ' ', ' ', 'h', ' ', ' ', ' ', ' ',   // 0
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 1		
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 2
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 3
			' ', ' ', 'h', 'r', ' ', ' ', 'h', ' ',   // 4
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 5
			' ', ' ', ' ', 'h', ' ', ' ', ' ', ' ',   // 6
			'k', ' ', ' ', ' ', ' ', ' ', ' ', ' '    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::White);

	PositionList rookPossibleMoves = game.GetPossibleMoves(Position(4, 3));
	PositionList rookExpectedMoves = { Position(3, 3),Position(2, 3),Position(1, 3),Position(5, 3),Position(4, 4),Position(4, 5) };

	EXPECT_EQ(ComparePositionLists(rookPossibleMoves, rookExpectedMoves), true);
}