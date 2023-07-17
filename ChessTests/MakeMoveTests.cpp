#include "gtest/gtest.h"

#include "ChessGame.h"

TEST(PawnMakeMove, PawnMakeMove1)
{
	ChessGame g;
	g.PlayTurn(BoardPosition(2, 'D'), BoardPosition(4, 'D'));
	EXPECT_EQ(g.GetBoard()[4][3]->GetName(), EType::Pawn);
}