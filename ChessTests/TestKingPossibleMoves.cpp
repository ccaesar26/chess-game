#include "Utility.h"

#include "gtest/gtest.h"

TEST(TestKingPossibleMoves, Test_Moves_On_Empty_Squares)
{
	// Declare board //

	std::array<std::array<char, 8>, 8> alternativeBoard =
	{
		//   0    1    2    3    4    5    6    7

			'K', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 0
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 1		
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 2
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 3
			' ', ' ', ' ', 'k', ' ', ' ', ' ', ' ',   // 4
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 5
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 6
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::White);

	PositionList kingPossibleMoves = game.GetPossibleMoves(Position(4, 3));
	PositionList kingExpectedMoves = { Position(3,2),Position(3,3),Position(3,4),Position(4,4),Position(5,4),Position(5,3),Position(5,2), Position(4,2) };

	EXPECT_EQ(ComparePositionLists(kingPossibleMoves, kingExpectedMoves), true);
}

