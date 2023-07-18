#include "gtest/gtest.h"

#include "ChessGame.h"

#include <iostream>

TEST(PawnMakeMove, PawnMakeMove1)
{
	ChessGame g;
	g.MakeMovement('d', 2, 'd', 4);
	EXPECT_EQ(g.GetIPiece('d', 2).use_count(), 0);
	EXPECT_EQ(g.GetIPiece('d', 4)->GetType(), EType::Pawn);
	/*g.MakeMovement('b', 1, 'a', 3);
	EXPECT_EQ(g.GetIPiece('b', 1).use_count(), 0);
	EXPECT_EQ(g.GetIPiece('a', 3)->GetType(), EType::Pawn);*/
}

TEST(HorseMakeMove, HorseMakeMove1)
{

}