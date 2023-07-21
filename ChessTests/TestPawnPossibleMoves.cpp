#include "Utility.h"

#include "gtest/gtest.h"

TEST(TestPawnPossibleMoves, Test_White_Moves_On_Empty_Squares)
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
			' ', ' ', ' ', ' ', ' ', ' ', 'p', ' ',   // 6
			'k', ' ', ' ', ' ', ' ', ' ', ' ', ' '    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::White);

	PositionList pawnPossibleMoves = game.GetPossibleMoves(Position(6, 6));
	PositionList pawnExpectedMoves = { Position(5,6),Position(4,6) };

	EXPECT_EQ(ComparePositionLists(pawnPossibleMoves, pawnExpectedMoves), true);
}

TEST(TestPawnPossibleMoves, Test_White_Moves_On_Ocupied_Squares_With_Same_Color)
{
	// Declare board //

	std::array<std::array<char, 8>, 8> alternativeBoard =
	{
		//   0    1    2    3    4    5    6    7

			'K', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 0
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 1		
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 2
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 3
			' ', ' ', ' ', ' ', ' ', 'p', ' ', 'p',   // 4
			' ', ' ', ' ', ' ', ' ', ' ', 'p', ' ',   // 5
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 6
			'k', ' ', ' ', ' ', ' ', ' ', ' ', ' '    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::White);

	PositionList pawnPossibleMoves = game.GetPossibleMoves(Position(5, 6));
	PositionList pawnExpectedMoves = { Position(4,6) };

	EXPECT_EQ(ComparePositionLists(pawnPossibleMoves, pawnExpectedMoves), true);
}

TEST(TestPawnPossibleMoves, Test_White_Moves_On_Ocupied_Squares_With_Enemy_Color)
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

// black // 

TEST(TestPawnPossibleMoves, Test_Black_Moves_On_Empty_Squares)
{
	// Declare board //

	std::array<std::array<char, 8>, 8> alternativeBoard =
	{
		//   0    1    2    3    4    5    6    7

			'K', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 0
			' ', ' ', ' ', ' ', ' ', ' ', 'P', ' ',   // 1		
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 2
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 3
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 4
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 5
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 6
			'k', ' ', ' ', ' ', ' ', ' ', ' ', ' '    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::Black);

	PositionList pawnPossibleMoves = game.GetPossibleMoves(Position(1, 6));
	PositionList pawnExpectedMoves = { Position(2,6),Position(3,6) };

	EXPECT_EQ(ComparePositionLists(pawnPossibleMoves, pawnExpectedMoves), true);
}

TEST(TestPawnPossibleMoves, Test_Black_Moves_On_Ocupied_Squares_With_Same_Color)
{
	// Declare board //

	std::array<std::array<char, 8>, 8> alternativeBoard =
	{
		//   0    1    2    3    4    5    6    7

			'K', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 0
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 1		
			' ', ' ', ' ', ' ', ' ', ' ', 'P', ' ',   // 2
			' ', ' ', ' ', ' ', ' ', 'P', ' ', 'P',   // 3
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 4
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 5
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 6
			'k', ' ', ' ', ' ', ' ', ' ', ' ', ' '    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::Black);

	PositionList pawnPossibleMoves = game.GetPossibleMoves(Position(2, 6));
	PositionList pawnExpectedMoves = { Position(3,6) };

	EXPECT_EQ(ComparePositionLists(pawnPossibleMoves, pawnExpectedMoves), true);
}

TEST(TestPawnPossibleMoves, Test_Black_Moves_On_Ocupied_Squares_With_Enemy_Color)
{
	// Declare board //

	std::array<std::array<char, 8>, 8> alternativeBoard =
	{
		//   0    1    2    3    4    5    6    7

			'K', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 0
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 1		
			' ', ' ', ' ', ' ', ' ', ' ', 'P', ' ',   // 2
			' ', ' ', ' ', ' ', ' ', 'p', ' ', 'p',   // 3
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 4
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 5
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 6
			'k', ' ', ' ', ' ', ' ', ' ', ' ', ' '    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::Black);

	PositionList pawnPossibleMoves = game.GetPossibleMoves(Position(2, 6));
	PositionList pawnExpectedMoves = { Position(3,6),Position(3,5),Position(3,7) };

	EXPECT_EQ(ComparePositionLists(pawnPossibleMoves, pawnExpectedMoves), true);
}