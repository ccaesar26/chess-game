#include "IChessGameListener.h"
#include "ChessGame.h"
#include "ChessException.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::InSequence; 
using ::testing::_;

class MockListener : public IChessGameListener
{

public:

	MOCK_METHOD(void, OnMoveMade, (Position init, Position fin), (override));

	MOCK_METHOD(void, OnGameOver, (EGameResult result), (override));

	MOCK_METHOD(void, OnPawnUpgrade, (Position init, Position upPos), (override));

	MOCK_METHOD(void, OnCheck, (), (override));

	MOCK_METHOD(void, OnGameRestarted, (), (override));

};

//TEST(OnMoveMadeIsCalled, LegalMove1) 
//{
//	ChessGame game;
//
//	auto listener = std::make_shared<MockListener>();
//
//	game.AddListener(listener);
//
//	EXPECT_CALL(*listener, OnMoveMade(Position(6, 4), Position(4, 4)))
//		.Times(1);
//
//	game.MakeMovement(Position(6, 4), Position(4, 4));
//}
//
//TEST(OnMoveMadeIsCalled, IllegalMove1)
//{
//	ChessGame game;
//
//	auto listener = std::make_shared<MockListener>();
//
//	game.AddListener(listener);
//
//
//	EXPECT_CALL(*listener, OnMoveMade(::testing::_, ::testing::_))
//		.Times(0);
//
//	try
//	{
//		EXPECT_THROW(game.MakeMovement(Position(7, 6), Position(6, 4)), OccupiedByOwnPieceException);
//	}
//	catch (const std::exception&)
//	{}
//}
//
//TEST(OnMoveMadeIsCalled, IllegalMove2)
//{
//	ChessGame game;
//
//	auto listener = std::make_shared<MockListener>();
//
//	game.AddListener(listener);
//
//
//	EXPECT_CALL(*listener, OnMoveMade(::testing::_, ::testing::_))
//		.Times(0);
//
//	try
//	{
//		EXPECT_THROW(game.MakeMovement(Position(8, 3), Position(3, 9)), OutOfBoundsException);
//	}
//	catch (const std::exception&)
//	{}
//}
//
//TEST(OnMoveMadeIsCalled, IllegalMove3)
//{
//	ChessGame game;
//
//	auto listener = std::make_shared<MockListener>();
//
//	game.AddListener(listener);
//
//
//	EXPECT_CALL(*listener, OnMoveMade(::testing::_, ::testing::_))
//		.Times(0);
//
//	try
//	{
//		EXPECT_THROW(game.MakeMovement(Position(6, 0), Position(5, 1)), NotInPossibleMovesException);
//	}
//	catch (const std::exception&)
//	{}
//}
//
//TEST(OnMoveMadeIsCalled, IllegalMove4)
//{
//
//	std::array<std::array<char, 8>, 8> alternativeBoard =
//	{
//		//   0    1    2    3    4    5    6    7
//
//			'K', 'R', ' ', ' ', ' ', ' ', ' ', ' ',   // 0
//			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 1		
//			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 2
//			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 3
//			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 4
//			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',   // 5
//			' ', 'r', ' ', ' ', ' ', ' ', ' ', ' ',   // 6
//			' ', 'k', ' ', ' ', ' ', ' ', ' ', ' '    // 7
//	};
//
//	ChessGame game(alternativeBoard, EColor::White);
//
//	auto listener = std::make_shared<MockListener>();
//
//	game.AddListener(listener);
//
//
//	EXPECT_CALL(*listener, OnMoveMade(::testing::_, ::testing::_))
//		.Times(0);
//
//	try
//	{
//		EXPECT_THROW(game.MakeMovement(Position(6, 1), Position(6, 7)), NotInPossibleMovesException);
//	}
//	catch (const std::exception&)
//	{}
//}
//
////TEST(OnMoveMadeIsCalled, IllegalMove5)
////{
////	ChessGame game;
////
////	auto listener = std::make_shared<MockListener>();
////
////	game.AddListener(listener);
////
////
////	EXPECT_CALL(*listener, OnMoveMade(::testing::_, ::testing::_))
////		.Times(0);
////
////	try
////	{
////		EXPECT_THROW(game.MakeMovement(Position(1, 0), Position(2, 0)), InitialSquareIsEmptyException);
////	}
////	catch (const std::exception&)
////	{}
////}

TEST(ListenersFunction, GameSimulation_1)
{
	ChessGame game;
	auto listener = std::make_shared<MockListener>();
	game.AddListener(listener);

	// Expect // 

	{
		InSequence sequence;

		EXPECT_CALL(*listener, OnMoveMade(Position(6, 3), Position(4, 3)))
			.Times(1);

		EXPECT_CALL(*listener, OnMoveMade(Position(1, 2), Position(3, 2)))
			.Times(1);

		EXPECT_CALL(*listener, OnMoveMade(Position(4, 3), Position(3, 2)))
			.Times(1);

		EXPECT_CALL(*listener, OnMoveMade(Position(0, 3), Position(1, 2)))
			.Times(1);

		EXPECT_CALL(*listener, OnMoveMade(Position(7, 3), Position(6, 3)))
			.Times(1);

		EXPECT_CALL(*listener, OnMoveMade(Position(1, 2), Position(3, 2)))
			.Times(1);

		EXPECT_CALL(*listener, OnMoveMade(Position(6, 3), Position(1, 3)))
			.Times(1);

		EXPECT_CALL(*listener, OnCheck())
			.Times(1);

		

	}

	// Actual moves // 

	game.MakeMovement(Position(6, 3), Position(4, 3));  // White
	game.MakeMovement(Position(1, 2), Position(3, 2));  // Black
	game.MakeMovement(Position(4, 3), Position(3, 2));  // White
	game.MakeMovement(Position(0, 3), Position(1, 2));	// Black
	game.MakeMovement(Position(7, 3), Position(6, 3));	// White
	game.MakeMovement(Position(1, 2), Position(3, 2));	// Black
	game.MakeMovement(Position(6, 3), Position(1, 3));	// White
	
	try
	{
		EXPECT_THROW(game.MakeMovement(Position(0, 0), Position(1, 3)),NotInPossibleMovesException);	// Black
	}
	catch (const std::exception&)
	{}

}