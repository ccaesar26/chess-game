#include "gtest/gtest.h"

#include "ChessGame.h"
#include "Utility.h"

TEST(TestCastle, Test_White_Castle_1)
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
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 5
			'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',   // 6
			'r', ' ', ' ', ' ', 'k', ' ', ' ', 'r'    // 7
	};

	ChessGame game(alternativeBoard, EColor::White);

	// Tests //

	PositionList kingPossbileMoves = game.GetPossibleMoves(Position(7, 4));
	PositionList kingExpectedMoves = {Position(7,5),Position(7,3), Position(7,2), Position(7,6)};

	EXPECT_EQ(ComparePositionLists(kingPossbileMoves, kingExpectedMoves), true);
}