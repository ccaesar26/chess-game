#include "gtest/gtest.h"

#include "ChessGame.h"

#include <iostream>

TEST(PawnMakeMove, PawnMakeMove1)
{
	ChessGame g;
	g.MakeMovement('d', 2, 'd', 4);
	EXPECT_EQ(g.GetIPiece('d', 2).use_count(), 0);
	EXPECT_EQ(g.GetIPiece('d', 4)->GetType(), EType::Pawn);
}

TEST(PawnMakeMove, PawnMakeMove2)
{
	ChessGame g;
	g.SwitchTurn();
	g.MakeMovement('d', 7, 'd', 6);
	EXPECT_EQ(g.GetIPiece('d', 7).use_count(), 0);
	EXPECT_EQ(g.GetIPiece('d', 6)->GetType(), EType::Pawn);
}

TEST(PawnMakeMove, PawnCapture1)
{
	/*ChessGame g;
	g.MakeMovement('e', 2, 'e', 4);
	g.MakeMovement('f', 7, 'f', 5);
	PiecePtr captured = g.GetPiece(Position(3, 5));
	g.MakeMovement('e', 4, 'f', 5);
	EXPECT_EQ(g.GetIPiece('f', 5)->GetColor(), EColor::White);
	EXPECT_EQ(g.GetIPiece('f', 5).use_count(), 0);
	EXPECT_EQ(g.GetBlackPiecesCaptured().size(), 1);
	EXPECT_EQ(g.GetBlackPiecesCaptured().front(), captured);*/
}

TEST(HorseMakeMove, HorseMakeMove1)
{
	ChessGame g;
	g.MakeMovement('b', 1, 'a', 3);
	EXPECT_EQ(g.GetIPiece('b', 1).use_count(), 0);
	EXPECT_EQ(g.GetIPiece('a', 3)->GetType(), EType::Horse);
}

TEST(HorseMakeMove, HorseMakeMove2)
{
	ChessGame g;
	g.SwitchTurn();
	g.MakeMovement('b', 8, 'C', 6);
	EXPECT_EQ(g.GetIPiece('b', 8).use_count(), 0);
	EXPECT_EQ(g.GetIPiece('C', 6)->GetType(), EType::Horse);
}