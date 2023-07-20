#include "gtest/gtest.h"

#include "ChessGame.h"

bool ComparePositionLists(const PositionList& piecePossibleMoves, const PositionList& pieceExpectedMoves)
{
	if (piecePossibleMoves.size() != pieceExpectedMoves.size()) return false;
	for (int i = 0; i < pieceExpectedMoves.size(); i++)
	{
		if (piecePossibleMoves[i] != pieceExpectedMoves[i]) return false;
	}
	return true;
}

TEST(HorsePossibleMoves, Test1)
{
	// Declare board //

	std::array<std::array<char, 8>, 8> alternativeBoard =
	{
		//   0    1    2    3    4    5    6    7

			'K', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 0
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 1		
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 2
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 3
			' ', ' ', ' ', 'h', ' ', ' ', ' ', ' ',   // 4
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 5
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 6
			'k', ' ', ' ', ' ', ' ', ' ', ' ', ' '    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::White);

	PositionList horsepossibleMoves = game.GetPossibleMoves(Position(4,3));
	PositionList expectedHorseMoves = { Position(2,2),Position(2, 4) ,Position(3, 1) ,Position(3, 5), Position(5, 1) ,Position(5, 5),Position(6, 2),Position(6, 4) };

	ComparePositionLists(horsepossibleMoves, expectedHorseMoves);
}

TEST(HorsePossibleMoves, Test2)
{
	// Declare board // 

	std::array<std::array<char, 8>, 8> alternativeBoard =
	{
		//   0    1    2    3    4    5    6    7

			'K', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 0
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 1		
			' ', ' ', 'p', ' ', 'p', ' ', ' ', ' ',   // 2
			' ', 'p', ' ', ' ', ' ', 'p', ' ', ' ',   // 3
			' ', ' ', ' ', 'h', ' ', ' ', ' ', ' ',   // 4
			' ', 'p', ' ', ' ', ' ', 'p', ' ', ' ',   // 5
			' ', ' ', 'p', ' ', 'p', ' ', ' ', ' ',   // 6
			'k', ' ', ' ', ' ', ' ', ' ', ' ', ' '    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::White);

	PositionList horsepossibleMoves = game.GetPossibleMoves(Position(4, 3));
	EXPECT_EQ(horsepossibleMoves.size(), 0);
}

TEST(HorsePossibleMoves, Test3)
{
	// Declare board // 

	std::array<std::array<char, 8>, 8> alternativeBoard =
	{
		//   0    1    2    3    4    5    6    7

			'K', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 0
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 1		
			' ', ' ', 'P', ' ', 'P', ' ', ' ', ' ',   // 2
			' ', 'P', ' ', ' ', ' ', 'P', ' ', ' ',   // 3
			' ', ' ', ' ', 'h', ' ', ' ', ' ', ' ',   // 4
			' ', 'P', ' ', ' ', ' ', 'P', ' ', ' ',   // 5
			' ', ' ', 'P', ' ', 'P', ' ', ' ', ' ',   // 6
			'k', ' ', ' ', ' ', ' ', ' ', ' ', ' '    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::White);

	PositionList horsepossibleMoves = game.GetPossibleMoves(Position(4, 3));
	PositionList expectedHorseMoves = { Position(2,2),Position(2, 4) ,Position(3, 1) ,Position(3, 5), Position(5, 1) ,Position(5, 5),Position(6, 2),Position(6, 4) };

	ComparePositionLists(horsepossibleMoves, expectedHorseMoves);
}

TEST(HorsePossibleMoves, Test4)
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
			'k', ' ', ' ', ' ', ' ', ' ', ' ', 'h'    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::White);

	PositionList horsepossibleMoves = game.GetPossibleMoves(Position(7, 7));
	PositionList expectedHorseMoves = { Position(5,6),Position(6, 5) };

	ComparePositionLists(horsepossibleMoves, expectedHorseMoves);
}

TEST(HorsePossibleMoves, Test5)
{
	// Declare board // 

	std::array<std::array<char, 8>, 8> alternativeBoard =
	{
		//   0    1    2    3    4    5    6    7

			' ', ' ', ' ', ' ', ' ', ' ', ' ', 'K',   // 0
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 1		
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 2
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 3
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 4
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 5
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 6
			'h', ' ', ' ', ' ', ' ', ' ', ' ', 'k'    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::White);

	PositionList horsepossibleMoves = game.GetPossibleMoves(Position(7, 0));
	PositionList expectedHorseMoves = { Position(5,1),Position(6, 2) };

	ComparePositionLists(horsepossibleMoves, expectedHorseMoves);
}

TEST(HorsePossibleMoves, Test6)
{
	// Declare board // 

	std::array<std::array<char, 8>, 8> alternativeBoard =
	{
		//   0    1    2    3    4    5    6    7

			'h', ' ', ' ', ' ', ' ', ' ', ' ', 'K',   // 0
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 1		
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 2
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 3
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 4
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 5
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 6
			' ', ' ', ' ', ' ', ' ', ' ', ' ', 'k'    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::White);

	PositionList horsepossibleMoves = game.GetPossibleMoves(Position(0, 0));
	PositionList expectedHorseMoves = { Position(1,2),Position(2, 1) };

	ComparePositionLists(horsepossibleMoves, expectedHorseMoves);
}

TEST(HorsePossibleMoves, Test7)
{
	// Declare board // 

	std::array<std::array<char, 8>, 8> alternativeBoard =
	{
		//   0    1    2    3    4    5    6    7

			'K', ' ', ' ', ' ', ' ', ' ', ' ', 'h',   // 0
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

	PositionList horsepossibleMoves = game.GetPossibleMoves(Position(0, 7));
	PositionList expectedHorseMoves = { Position(1,5),Position(2, 6) };

	ComparePositionLists(horsepossibleMoves, expectedHorseMoves);
}

TEST(HorsePossibleMoves, Test8)
{
	// Declare board // 

	std::array<std::array<char, 8>, 8> alternativeBoard =
	{
		//   0    1    2    3    4    5    6    7

			'K', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 0
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 1		
			' ', ' ', 'R', ' ', ' ', ' ', ' ', ' ',   // 2
			' ', ' ', ' ', ' ', 'h', ' ', ' ', ' ',   // 3
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 4
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 5
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 6
			' ', ' ', 'k', ' ', ' ', ' ', ' ', ' '    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::White);

	PositionList horsepossibleMoves = game.GetPossibleMoves(Position(3, 4));
	PositionList expectedHorseMoves = { Position(2,2),Position(4, 2) };

	ComparePositionLists(horsepossibleMoves, expectedHorseMoves);
}

TEST(HorsePossibleMoves, Test9)
{
	// Declare board // 

	std::array<std::array<char, 8>, 8> alternativeBoard =
	{
		//   0    1    2    3    4    5    6    7

			'K', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 0
			' ', ' ', ' ', ' ', ' ', 'h', ' ', ' ',   // 1		
			' ', ' ', ' ', ' ', ' ', ' ', ' ', 'B',   // 2
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 3
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 4
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 5
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 6
			' ', ' ', 'k', ' ', ' ', ' ', ' ', ' '    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::White);

	PositionList horsepossibleMoves = game.GetPossibleMoves(Position(1, 5));
	PositionList expectedHorseMoves = { Position(2,7),Position(3, 6) };

	ComparePositionLists(horsepossibleMoves, expectedHorseMoves);
}

TEST(HorsePossibleMoves, Test10)
{
	// Declare board // 

	std::array<std::array<char, 8>, 8> alternativeBoard =
	{
		//   0    1    2    3    4    5    6    7

			'K', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 0
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 1		
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 2
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 3
			' ', 'h', ' ', ' ', ' ', ' ', ' ', ' ',   // 4
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 5
			' ', ' ', 'H', ' ', ' ', ' ', ' ', ' ',   // 6
			'k', ' ', ' ', ' ', ' ', ' ', ' ', ' '    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::White);

	PositionList horsepossibleMoves = game.GetPossibleMoves(Position(4, 1));
	PositionList expectedHorseMoves = { Position(6,2) };

	ComparePositionLists(horsepossibleMoves, expectedHorseMoves);
}

TEST(HorsePossibleMoves, Test11)
{
	// Declare board // 

	std::array<std::array<char, 8>, 8> alternativeBoard =
	{
		//   0    1    2    3    4    5    6    7

			'K', ' ', ' ', 'R', ' ', ' ', ' ', ' ',   // 0
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 1		
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 2
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 3
			' ', ' ', ' ', 'h', ' ', ' ', ' ', ' ',   // 4
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 5
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 6
			' ', ' ', ' ', 'k', ' ', ' ', ' ', ' '    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::White);

	PositionList horsepossibleMoves = game.GetPossibleMoves(Position(4, 3));
	EXPECT_EQ(horsepossibleMoves.size(), 0);
}

TEST(HorsePossibleMoves, Test12)
{
	// Declare board // 

	std::array<std::array<char, 8>, 8> alternativeBoard =
	{
		//   0    1    2    3    4    5    6    7

			'K', ' ', ' ', ' ', ' ', ' ', ' ', 'B',   // 0
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 1		
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 2
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 3
			' ', ' ', ' ', 'h', ' ', ' ', ' ', ' ',   // 4
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 5
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 6
			'k', ' ', ' ', ' ', ' ', ' ', ' ', ' '    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::White);

	PositionList horsepossibleMoves = game.GetPossibleMoves(Position(4, 3));
	EXPECT_EQ(horsepossibleMoves.size(), 0);
}

TEST(HorsePossibleMoves, Test13)
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
			' ', ' ', 'h', ' ', ' ', ' ', ' ', ' ',   // 5
			' ', ' ', 'H', ' ', ' ', ' ', ' ', ' ',   // 6
			'k', ' ', ' ', ' ', ' ', ' ', ' ', ' '    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::White);

	PositionList horsepossibleMoves = game.GetPossibleMoves(Position(5, 2));
	EXPECT_EQ(horsepossibleMoves.size(), 0);
}

TEST(HorsePossibleMoves, Test14)
{
	// Declare board // 

	std::array<std::array<char, 8>, 8> alternativeBoard =
	{
		//   0    1    2    3    4    5    6    7

			'K', 'R', ' ', ' ', ' ', ' ', ' ', ' ',   // 0
			' ', ' ', ' ', ' ', ' ', ' ', ' ', 'B',   // 1		
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 2
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 3
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 4
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 5
			' ', ' ', 'h', ' ', ' ', ' ', ' ', ' ',   // 6
			' ', 'k', ' ', ' ', ' ', ' ', ' ', ' '    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::White);

	PositionList horsepossibleMoves = game.GetPossibleMoves(Position(6, 2));
	EXPECT_EQ(horsepossibleMoves.size(), 0);
}