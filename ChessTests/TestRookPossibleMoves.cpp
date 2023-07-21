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

TEST(TestRookPossibleMoves, Test_Moves_On_Ocupied_Squares_With_Enemy_Color)
{
	// Declare board //

	std::array<std::array<char, 8>, 8> alternativeBoard =
	{
		//   0    1    2    3    4    5    6    7

			'K', ' ', ' ', 'H', ' ', ' ', ' ', ' ',   // 0
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 1		
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 2
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 3
			' ', ' ', 'H', 'r', ' ', ' ', 'H', ' ',   // 4
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 5
			' ', ' ', ' ', 'H', ' ', ' ', ' ', ' ',   // 6
			'k', ' ', ' ', ' ', ' ', ' ', ' ', ' '    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::White);

	PositionList rookPossibleMoves = game.GetPossibleMoves(Position(4, 3));
	PositionList rookExpectedMoves = { Position(3, 3),Position(2, 3),Position(1, 3),Position(0, 3),
		Position(5, 3),Position(6, 3),Position(4, 2),Position(4, 4),Position(4, 5),Position(4, 6) };

	EXPECT_EQ(ComparePositionLists(rookPossibleMoves, rookExpectedMoves), true);
}

TEST(TestRookPossibleMoves, Test_Moves_While_King_In_Check_From_Rook_1)
{
	// Declare board //

	std::array<std::array<char, 8>, 8> alternativeBoard =
	{
		//   0    1    2    3    4    5    6    7

			'K', 'R', ' ', ' ', ' ', ' ', ' ', ' ',   // 0
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 1		
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 2
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 3
			' ', ' ', ' ', 'r', ' ', ' ', ' ', ' ',   // 4
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 5
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 6
			' ', 'k', ' ', ' ', ' ', ' ', ' ', ' '    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::White);

	PositionList rookPossibleMoves = game.GetPossibleMoves(Position(4, 3));
	PositionList rookExpectedMoves = { Position(4,1) };

	EXPECT_EQ(ComparePositionLists(rookPossibleMoves, rookExpectedMoves), true);
}

TEST(TestRookPossibleMoves, Test_Moves_While_King_In_Check_From_Rook_2)
{
	// Declare board //

	std::array<std::array<char, 8>, 8> alternativeBoard =
	{
		//   0    1    2    3    4    5    6    7

			'K', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 0
			' ', 'R', ' ', ' ', ' ', ' ', ' ', 'r',   // 1		
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 2
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 3
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 4
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 5
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 6
			' ', 'k', ' ', ' ', ' ', ' ', ' ', ' '    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::White);

	PositionList rookPossibleMoves = game.GetPossibleMoves(Position(1, 7));
	PositionList rookExpectedMoves = { Position(1,1) };

	EXPECT_EQ(ComparePositionLists(rookPossibleMoves, rookExpectedMoves), true);
}

TEST(TestRookPossibleMoves, Test_Moves_While_King_In_Check_From_Bishop_1)
{
	// Declare board //

	std::array<std::array<char, 8>, 8> alternativeBoard =
	{
		//   0    1    2    3    4    5    6    7

			'K', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 0
			' ', ' ', ' ', ' ', ' ', ' ', 'B', ' ',   // 1		
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 2
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 3
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 4
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 5
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 6
			'k', ' ', ' ', ' ', ' ', ' ', 'r', ' '    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::White);

	PositionList rookPossibleMoves = game.GetPossibleMoves(Position(7, 6));
	PositionList rookExpectedMoves = { Position(1,6) };

	EXPECT_EQ(ComparePositionLists(rookPossibleMoves, rookExpectedMoves), true);
}

TEST(TestRookPossibleMoves, Test_Moves_While_King_In_Check_From_Bishop_2)
{
	// Declare board //

	std::array<std::array<char, 8>, 8> alternativeBoard =
	{
		//   0    1    2    3    4    5    6    7

			'K', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 0
			' ', ' ', ' ', ' ', ' ', ' ', 'B', ' ',   // 1		
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 2
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 3
			' ', ' ', ' ', ' ', ' ', ' ', ' ', 'r',   // 4
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 5
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 6
			'k', ' ', ' ', ' ', ' ', ' ', ' ', ' '    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::White);

	PositionList rookPossibleMoves = game.GetPossibleMoves(Position(4, 7));
	PositionList rookExpectedMoves = { Position(4,3) };

	EXPECT_EQ(ComparePositionLists(rookPossibleMoves, rookExpectedMoves), true);
}

TEST(TestRookPossibleMoves, Test_Moves_While_King_In_Check_From_Horse)
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
			' ', 'H', ' ', ' ', ' ', ' ', ' ', 'r',   // 5
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 6
			'k', ' ', ' ', ' ', ' ', ' ', ' ', ' '    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::White);

	PositionList rookPossibleMoves = game.GetPossibleMoves(Position(5, 7));
	PositionList rookExpectedMoves = { Position(5,1) };

	EXPECT_EQ(ComparePositionLists(rookPossibleMoves, rookExpectedMoves), true);
}