#include "Utility.h"

#include "gtest/gtest.h"

TEST(TestBishopPossibleMoves, Test_Moves_On_Empty_Squares)
{
	// Declare board //

	std::array<std::array<char, 8>, 8> alternativeBoard =
	{
		//   0    1    2    3    4    5    6    7

			' ', 'K', ' ', ' ', ' ', ' ', ' ', ' ',   // 0
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 1		
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 2
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 3
			' ', ' ', ' ', 'b', ' ', ' ', ' ', ' ',   // 4
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 5
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 6
			' ', 'k', ' ', ' ', ' ', ' ', ' ', ' '    // 7
	};

	// Tests //

	ChessGame game(alternativeBoard, EColor::White);

	PositionList bishopPossibleMoves = game.GetPossibleMoves(Position(4, 3));
	PositionList bishopExpectedMoves = { Position(3,2),Position(2, 1) ,Position(1, 0) ,Position(3,4),Position(2, 5) ,Position(1, 6) , Position(0, 7)
	,Position(5, 2),Position(6, 1),Position(7, 0),Position(5, 4),Position(6, 5),Position(7, 6) };

	ComparePositionLists(bishopPossibleMoves, bishopExpectedMoves);
}