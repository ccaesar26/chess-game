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