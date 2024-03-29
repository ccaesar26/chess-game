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

TEST(TestKingPossibleMoves, Test_Moves_On_Ocupied_Squares_With_Same_Color)
{
	// Declare board //

	std::array<std::array<char, 8>, 8> alternativeBoard =
	{
		//   0    1    2    3    4    5    6    7

			'K', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 0
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 1		
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 2
			' ', ' ', 'p', 'p', 'p', ' ', ' ', ' ',   // 3
			' ', ' ', 'p', 'k', 'p', ' ', ' ', ' ',   // 4
			' ', ' ', 'p', 'p', 'p', ' ', ' ', ' ',   // 5
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 6
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::White);

	PositionList kingPossibleMoves = game.GetPossibleMoves(Position(4, 3));

	EXPECT_EQ(kingPossibleMoves.size(),0);
}

TEST(TestKingPossibleMoves, Test_Moves_On_Ocupied_Squares_With_Enemy_Color)
{
	// Declare board //

	std::array<std::array<char, 8>, 8> alternativeBoard =
	{
		//   0    1    2    3    4    5    6    7

			'K', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 0
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 1		
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 2
			' ', ' ', ' ', ' ', 'H', ' ', ' ', ' ',   // 3
			' ', ' ', ' ', 'k', 'H', ' ', ' ', ' ',   // 4
			' ', ' ', ' ', ' ', 'H', ' ', ' ', ' ',   // 5
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 6
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::White);

	PositionList kingPossibleMoves = game.GetPossibleMoves(Position(4, 3));
	PositionList kingExpectedMoves = { Position(3,4),Position(4,4),Position(5,4) };

	EXPECT_EQ(ComparePositionLists(kingPossibleMoves, kingExpectedMoves), true);
}

TEST(TestKingPossibleMoves, Test_Moves_From_Top_Left_Corner)
{
	// Declare board //

	std::array<std::array<char, 8>, 8> alternativeBoard =
	{
		//   0    1    2    3    4    5    6    7

			'k', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 0
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 1		
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 2
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 3
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 4
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 5
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 6
			'K', ' ', ' ', ' ', ' ', ' ', ' ', ' '    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::White);

	PositionList kingPossibleMoves = game.GetPossibleMoves(Position(0, 0));
	PositionList kingExpectedMoves = { Position(0,1),Position(1,1),Position(1,0) };

	EXPECT_EQ(ComparePositionLists(kingPossibleMoves, kingExpectedMoves), true);
}

TEST(TestKingPossibleMoves, Test_Moves_From_Top_Right_Corner)
{
	// Declare board //

	std::array<std::array<char, 8>, 8> alternativeBoard =
	{
		//   0    1    2    3    4    5    6    7

			' ', ' ', ' ', ' ', ' ', ' ', ' ', 'k',   // 0
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 1		
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 2
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 3
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 4
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 5
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 6
			'K', ' ', ' ', ' ', ' ', ' ', ' ', ' '    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::White);

	PositionList kingPossibleMoves = game.GetPossibleMoves(Position(0, 7));
	PositionList kingExpectedMoves = { Position(1,7),Position(1,6),Position(0,6) };

	EXPECT_EQ(ComparePositionLists(kingPossibleMoves, kingExpectedMoves), true);
}

TEST(TestKingPossibleMoves, Test_Moves_From_Bottom_Right_Corner)
{
	// Declare board //

	std::array<std::array<char, 8>, 8> alternativeBoard =
	{
		//   0    1    2    3    4    5    6    7

			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 0
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 1		
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 2
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 3
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 4
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 5
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 6
			'K', ' ', ' ', ' ', ' ', ' ', ' ', 'k'    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::White);

	PositionList kingPossibleMoves = game.GetPossibleMoves(Position(7, 7));
	PositionList kingExpectedMoves = { Position(6,6),Position(6,7),Position(7,6) };

	EXPECT_EQ(ComparePositionLists(kingPossibleMoves, kingExpectedMoves), true);
}

TEST(TestKingPossibleMoves, Test_Moves_From_Bottom_Left_Corner)
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
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 6
			'k', ' ', ' ', ' ', ' ', ' ', ' ', ' '    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::White);

	PositionList kingPossibleMoves = game.GetPossibleMoves(Position(7, 0));
	PositionList kingExpectedMoves = { Position(6,0),Position(6,1),Position(7,1) };

	EXPECT_EQ(ComparePositionLists(kingPossibleMoves, kingExpectedMoves), true);
}

TEST(TestKingPossibleMoves, Test_Moves_While_King_In_Check_From_Rook)
{
	// Declare board //

	std::array<std::array<char, 8>, 8> alternativeBoard =
	{
		//   0    1    2    3    4    5    6    7

			'K', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 0
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 1		
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 2
			' ', ' ', ' ', 'R', ' ', ' ', ' ', ' ',   // 3
			' ', ' ', ' ', 'k', ' ', ' ', ' ', ' ',   // 4
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 5
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 6
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::White);

	PositionList kingPossibleMoves = game.GetPossibleMoves(Position(4, 3));
	PositionList kingExpectedMoves = { Position(3,3),Position(4,4),Position(5,4),Position(5,2),Position(4,2) };

	EXPECT_EQ(ComparePositionLists(kingPossibleMoves, kingExpectedMoves), true);
}

TEST(TestKingPossibleMoves, Test_Moves_While_King_In_Check_From_Bishop)
{
	// Declare board //

	std::array<std::array<char, 8>, 8> alternativeBoard =
	{
		//   0    1    2    3    4    5    6    7

			'K', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 0
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 1		
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 2
			' ', ' ', ' ', ' ', 'B', ' ', ' ', ' ',   // 3
			' ', ' ', ' ', 'k', ' ', ' ', ' ', ' ',   // 4
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 5
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 6
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::White);

	PositionList kingPossibleMoves = game.GetPossibleMoves(Position(4, 3));
	PositionList kingExpectedMoves = { Position(3,2),Position(3,3),Position(3,4),Position(4,4),Position(5,4),Position(5,3),Position(4,2) };

	EXPECT_EQ(ComparePositionLists(kingPossibleMoves, kingExpectedMoves), true);
}
