#include "IChessGameListener.h"
#include "ChessGame.h"
#include "ChessException.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"


class MockListener : public IChessGameListener
{

public:

	MOCK_METHOD(void, OnMoveMade, (Position init, Position fin), (override));

	MOCK_METHOD(void, OnGameOver, (EGameResult result), (override));

	MOCK_METHOD(void, OnPawnUpgrade, (Position init, Position upPos), (override));

	MOCK_METHOD(void, OnCheck, (), (override));

	MOCK_METHOD(void, OnGameRestarted, (), (override));

};

TEST(OnMoveMadeIsCalled, LegalMove1) 
{
	ChessGame game;

	auto listener = std::make_shared<MockListener>();

	game.AddListener(listener);

	EXPECT_CALL(*listener, OnMoveMade(Position(6, 4), Position(4, 4)))
		.Times(1);

	game.MakeMovement(Position(6, 4), Position(4, 4));

}

TEST(OnMoveMadeIsCalled, IllegalMove1)
{
	ChessGame game;

	auto listener = std::make_shared<MockListener>();

	game.AddListener(listener);


	EXPECT_CALL(*listener, OnMoveMade(Position(7, 6), Position(6, 4)))
		.Times(0);

	try
	{
		EXPECT_THROW(game.MakeMovement(Position(7, 6), Position(6, 4)), OccupiedByOwnPieceException);
	}
	catch (const std::exception&)
	{}

}