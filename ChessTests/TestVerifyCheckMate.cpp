#include "Utility.h"

#include "gtest/gtest.h"

TEST(CheckCheckMate, King_In_Check_From_Two_Pieces_1)
{
	// Declare board //

	std::array<std::array<char, 8>, 8> alternativeBoard =
	{
		//   0    1    2    3    4    5    6    7

			'K', ' ', ' ', ' ', ' ', ' ', ' ', 'R',   // 0
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 1		
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 2
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 3
			' ', ' ', ' ', ' ', 'B', ' ', ' ', ' ',   // 4
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 5
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 6
			' ', ' ', ' ', ' ', ' ', ' ', ' ', 'k'    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::White);

	EXPECT_EQ(game.CheckCheckMate(), false);
}

TEST(CheckCheckMate, King_In_Check_From_Two_Pieces_2)
{
	// Declare board //

	std::array<std::array<char, 8>, 8> alternativeBoard =
	{
		//   0    1    2    3    4    5    6    7

			'K', ' ', ' ', ' ', ' ', ' ', ' ', 'R',   // 0
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 1		
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 2
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 3
			' ', ' ', ' ', 'B', 'B', ' ', ' ', ' ',   // 4
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 5
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 6
			' ', ' ', ' ', ' ', ' ', ' ', ' ', 'k'    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::White);

	EXPECT_EQ(game.CheckCheckMate(), true);
}

TEST(CheckCheckMate, King_In_Check_From_One_Piece_1)
{
	// Declare board //

	std::array<std::array<char, 8>, 8> alternativeBoard =
	{
		//   0    1    2    3    4    5    6    7

			'K', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 0
			' ', ' ', ' ', ' ', ' ', ' ', ' ', 'r',   // 1		
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 2
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 3
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 4
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 5
			'R', ' ', ' ', ' ', ' ', ' ', ' ', 'Q',   // 6
			' ', ' ', ' ', ' ', ' ', ' ', ' ', 'k'    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::White);

	EXPECT_EQ(game.CheckCheckMate(), false);
}

TEST(CheckCheckMate, King_In_Check_From_One_Piece_2)
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
			'R', ' ', ' ', ' ', ' ', ' ', ' ', 'Q',   // 6
			' ', ' ', ' ', ' ', ' ', ' ', ' ', 'k'    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::White);

	EXPECT_EQ(game.CheckCheckMate(), true);
}

TEST(CheckCheckMate, King_In_Check_From_One_Piece_3)
{
	// Declare board //

	std::array<std::array<char, 8>, 8> alternativeBoard =
	{
		//   0    1    2    3    4    5    6    7

			'K', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 0
			'b', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 1		
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 2
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 3
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 4
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 5
			'R', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 6
			'R', ' ', ' ', ' ', ' ', ' ', ' ', 'k'    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::White);

	EXPECT_EQ(game.CheckCheckMate(), false);
}

TEST(CheckCheckMate, King_In_Check_From_One_Piece_4)
{
	// Declare board //

	std::array<std::array<char, 8>, 8> alternativeBoard =
	{
		//   0    1    2    3    4    5    6    7

			'K', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 0
			' ', ' ', ' ', ' ', ' ', ' ', 'r', ' ',   // 1		
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 2
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 3
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 4
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 5
			'R', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 6
			'R', ' ', ' ', ' ', ' ', ' ', ' ', 'k'    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::White);

	EXPECT_EQ(game.CheckCheckMate(), false);
}

TEST(CheckCheckMate, King_In_Check_From_One_Piece_5)
{
	// Declare board //

	std::array<std::array<char, 8>, 8> alternativeBoard =
	{
		//   0    1    2    3    4    5    6    7

			'K', ' ', ' ', ' ', ' ', ' ', ' ', 'R',   // 0
			'B', 'B', ' ', ' ', ' ', ' ', ' ', ' ',   // 1		
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 2
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 3
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 4
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 5
			' ', ' ', ' ', ' ', ' ', ' ', 'r', ' ',   // 6
			' ', ' ', ' ', ' ', ' ', ' ', ' ', 'k'    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::White);

	EXPECT_EQ(game.CheckCheckMate(), true);
}
