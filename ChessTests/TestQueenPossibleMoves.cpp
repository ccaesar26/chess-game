#include "Utility.h"

#include "gtest/gtest.h"

TEST(TestQueenPossibleMoves, Test_Moves_On_Empty_Squares)
{
	// Declare board //

	std::array<std::array<char, 8>, 8> alternativeBoard =
	{
		//   0    1    2    3    4    5    6    7

			'K', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 0
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 1		
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 2
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 3
			' ', ' ', ' ', 'q', ' ', ' ', ' ', ' ',   // 4
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 5
			'k', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 6
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::White);

	PositionList queenPossibleMoves = game.GetPossibleMoves(Position(4, 3));
	PositionList queenExpectedMoves = { Position(3,2),Position(2, 1) ,Position(1, 0) ,Position(3,4),Position(2, 5) ,Position(1, 6) , Position(0, 7)
	,Position(5, 2),Position(6, 1),Position(7, 0),Position(5, 4),Position(6, 5),Position(7, 6),Position(3, 3),Position(2, 3),Position(1, 3)
	,Position(0, 3),Position(5, 3),Position(6, 3),Position(7, 3),Position(4, 2),Position(4, 1),Position(4, 0),Position(4, 4),Position(4, 5),Position(4, 6),Position(4, 7) };

	EXPECT_EQ(ComparePositionLists(queenPossibleMoves, queenExpectedMoves), true);
}

TEST(TestQueenPossibleMoves, Test_Moves_On_Ocupied_Squares_With_Same_Color)
{
	// Declare board //

	std::array<std::array<char, 8>, 8> alternativeBoard =
	{
		//   0    1    2    3    4    5    6    7

			'K', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 0
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 1		
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 2
			' ', ' ', 'p', 'p', 'p', ' ', ' ', ' ',   // 3
			' ', ' ', 'p', 'q', 'p', ' ', ' ', ' ',   // 4
			' ', ' ', 'p', 'p', 'p', ' ', ' ', ' ',   // 5
			'k', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 6
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::White);

	PositionList queenPossibleMoves = game.GetPossibleMoves(Position(4, 3));

	EXPECT_EQ(queenPossibleMoves.size(), 0);
}