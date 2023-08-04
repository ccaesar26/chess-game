#include "gtest/gtest.h"

#include "ChessGame.h"
#include "ChessException.h"
#include "Utility.h"

TEST(TestLoadPGNFromFile, LoadPass_1)
{
	ChessGame game;

	bool isLoaded = game.LoadPGNFromFile(".\\TestsForLoadingPGN\\Test1Pass.pgn");
	EXPECT_EQ(isLoaded, true);

	std::array<std::array<char, 8>, 8> expectedBoard =
	{
		' ', 'H', 'b', ' ', ' ', 'B', ' ', 'Q',
		'P', ' ', 'P', ' ', ' ', ' ', ' ', ' ',
		'b', ' ', 'b', ' ', ' ', ' ', ' ', ' ',
		' ', ' ', ' ', ' ', ' ', ' ', 'P', ' ',
		' ', ' ', ' ', ' ', 'P', ' ', ' ', 'K',
		' ', ' ', ' ', ' ', 'p', ' ', ' ', 'P',
		' ', 'p', ' ', 'p', 'b', 'p', ' ', 'p',
		'r', 'h', 'b', 'q', 'k', ' ', 'h', 'r'
	};

	EXPECT_EQ(CompareCharBoardWithNormalBoard(expectedBoard, game), true);
}

TEST(TestLoadPGNFromFile, LoadPass_2)
{
	ChessGame game;

	bool isLoaded = game.LoadPGNFromFile(".\\TestsForLoadingPGN\\Test2Pass.pgn");
	EXPECT_EQ(isLoaded, true);

	std::array<std::array<char, 8>, 8> expectedBoard =
	{
		'q', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
		' ', ' ', ' ', ' ', ' ', 'r', ' ', 'K',
		' ', ' ', ' ', 'p', ' ', 'q', ' ', ' ',
		' ', ' ', ' ', ' ', 'P', ' ', ' ', ' ',
		' ', ' ', ' ', 'p', ' ', ' ', ' ', ' ',
		' ', ' ', ' ', ' ', 'b', 'h', ' ', ' ',
		' ', ' ', ' ', ' ', 'p', 'p', ' ', ' ',
		' ', 'B', ' ', ' ', 'k', 'b', ' ', ' '
	};

	EXPECT_EQ(CompareCharBoardWithNormalBoard(expectedBoard, game), true);
}

TEST(TestLoadPGNFromFile, LoadPass_3)
{
	ChessGame game;

	bool isLoaded = game.LoadPGNFromFile(".\\TestsForLoadingPGN\\Test3Pass.pgn");
	EXPECT_EQ(isLoaded, true);

	std::array<std::array<char, 8>, 8> expectedBoard =
	{
		' ', ' ', 'K', 'R', ' ', 'B', 'H', 'q',
		' ', 'P', ' ', ' ', ' ', 'P', ' ', 'P',
		' ', ' ', 'H', 'P', ' ', ' ', ' ', ' ',
		'p', ' ', 'Q', ' ', ' ', ' ', ' ', ' ',
		' ', ' ', ' ', ' ', ' ', 'P', ' ', ' ',
		' ', ' ', ' ', ' ', ' ', 'h', 'p', 'B',
		'p', ' ', 'p', ' ', 'p', ' ', ' ', 'k',
		'r', 'h', 'b', ' ', ' ', 'r', ' ', ' '
	};

	EXPECT_EQ(CompareCharBoardWithNormalBoard(expectedBoard, game), true);
}

TEST(TestLoadPGNFromFile, LoadPass_4)
{
	ChessGame game;

	bool isLoaded = game.LoadPGNFromFile(".\\TestsForLoadingPGN\\Test4Pass.pgn");
	EXPECT_EQ(isLoaded, true);

	std::array<std::array<char, 8>, 8> expectedBoard =
	{
		'R', 'H', 'B', ' ', 'K', 'B', 'H', 'R',
		'P', 'P', 'P', 'P', ' ', 'P', 'P', 'P',
		' ', ' ', ' ', ' ', 'P', ' ', ' ', ' ',
		' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
		' ', ' ', ' ', ' ', ' ', 'p', 'p', 'Q',
		' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
		'p', 'p', 'p', 'p', 'p', ' ', ' ', 'p',
		'r', 'h', 'b', 'q', 'k', 'b', 'h', 'r'
	};

	EXPECT_EQ(CompareCharBoardWithNormalBoard(expectedBoard, game), true);
}

TEST(TestLoadPGNFromFile, LoadPass_5)
{
	ChessGame game;

	bool isLoaded = game.LoadPGNFromFile(".\\TestsForLoadingPGN\\Test5Pass.pgn");
	EXPECT_EQ(isLoaded, true);

	std::array<std::array<char, 8>, 8> expectedBoard =
	{
		'R', 'H', 'B', 'Q', 'K', 'B', 'H', 'R',
		'P', 'P', 'P', 'P', 'P', ' ', ' ', 'P',
		' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
		' ', ' ', ' ', ' ', ' ', 'P', 'P', 'q',
		' ', ' ', ' ', ' ', 'p', ' ', ' ', ' ',
		' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
		'p', 'p', 'p', 'p', ' ', 'p', 'p', 'p',
		'r', 'h', 'b', ' ', 'k', 'b', 'h', 'r'
	};

	EXPECT_EQ(CompareCharBoardWithNormalBoard(expectedBoard, game), true);
}