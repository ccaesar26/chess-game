#include "gtest/gtest.h"

#include "ChessGame.h"

TEST(InitialPiecesPlacementOnBoard, BlackRook)
{
	ChessGame g;

	EXPECT_EQ(g.GetIPiece('A', 8)->GetType(), EType::Rook);
	EXPECT_EQ(g.GetIPiece('a', 8)->GetColor(), EColor::Black);
	EXPECT_EQ(g.GetIPiece('h', 8)->GetType(), EType::Rook);
	EXPECT_EQ(g.GetIPiece('h', 8)->GetColor(), EColor::Black);
}

TEST(InitialPiecesPlacementOnBoard, BlackHorse)
{
	ChessGame g;

	EXPECT_EQ(g.GetIPiece('b', 8)->GetType(), EType::Horse);
	EXPECT_EQ(g.GetIPiece('b', 8)->GetColor(), EColor::Black);
	EXPECT_EQ(g.GetIPiece('g', 8)->GetType(), EType::Horse);
	EXPECT_EQ(g.GetIPiece('g', 8)->GetColor(), EColor::Black);
}

TEST(InitialPiecesPlacementOnBoard, BlackBishop)
{
	ChessGame g;

	EXPECT_EQ(g.GetIPiece('c', 8)->GetType(), EType::Bishop);
	EXPECT_EQ(g.GetIPiece('c', 8)->GetColor(), EColor::Black);
	EXPECT_EQ(g.GetIPiece('f', 8)->GetType(), EType::Bishop);
	EXPECT_EQ(g.GetIPiece('f', 8)->GetColor(), EColor::Black);
}

TEST(InitialPiecesPlacementOnBoard, BlackQueen)
{
	ChessGame g;

	EXPECT_EQ(g.GetIPiece('d', 8)->GetType(), EType::Queen);
	EXPECT_EQ(g.GetIPiece('d', 8)->GetColor(), EColor::Black);
}

TEST(InitialPiecesPlacementOnBoard, BlackKing)
{
	ChessGame g;

	EXPECT_EQ(g.GetIPiece('e', 8)->GetType(), EType::King);
	EXPECT_EQ(g.GetIPiece('e', 8)->GetColor(), EColor::Black);
}

TEST(InitialPiecesPlacementOnBoard, BlackPawn)
{
	ChessGame g;

	for (int i = 0; i < 8; i++)
	{
		EXPECT_EQ(g.GetIPiece(i + 'a', 7)->GetType(), EType::Pawn);
		EXPECT_EQ(g.GetIPiece(i + 'a', 7)->GetColor(), EColor::Black);
	}
}

TEST(InitialPiecesPlacementOnBoard, WhiteRook)
{
	ChessGame g;

	EXPECT_EQ(g.GetIPiece('a', 1)->GetType(), EType::Rook);
	EXPECT_EQ(g.GetIPiece('a', 1)->GetColor(), EColor::White);
	EXPECT_EQ(g.GetIPiece('h', 1)->GetType(), EType::Rook);
	EXPECT_EQ(g.GetIPiece('h', 1)->GetColor(), EColor::White);
}

TEST(InitialPiecesPlacementOnBoard, WhiteHorse)
{
	ChessGame g;

	EXPECT_EQ(g.GetIPiece('b', 1)->GetType(), EType::Horse);
	EXPECT_EQ(g.GetIPiece('b', 1)->GetColor(), EColor::White);
	EXPECT_EQ(g.GetIPiece('g', 1)->GetType(), EType::Horse);
	EXPECT_EQ(g.GetIPiece('g', 1)->GetColor(), EColor::White);
}

TEST(InitialPiecesPlacementOnBoard, WhiteBishop)
{
	ChessGame g;

	EXPECT_EQ(g.GetIPiece('c', 1)->GetType(), EType::Bishop);
	EXPECT_EQ(g.GetIPiece('c', 1)->GetColor(), EColor::White);
	EXPECT_EQ(g.GetIPiece('f', 1)->GetType(), EType::Bishop);
	EXPECT_EQ(g.GetIPiece('f', 1)->GetColor(), EColor::White);
}

TEST(InitialPiecesPlacementOnBoard, WhiteQueen)
{
	ChessGame g;

	EXPECT_EQ(g.GetIPiece('d', 1)->GetType(), EType::Queen);
	EXPECT_EQ(g.GetIPiece('d', 1)->GetColor(), EColor::White);
}

TEST(InitialPiecesPlacementOnBoard, WhiteKing)
{
	ChessGame g;

	EXPECT_EQ(g.GetIPiece('e', 1)->GetType(), EType::King);
	EXPECT_EQ(g.GetIPiece('e', 1)->GetColor(), EColor::White);
}

TEST(InitialPiecesPlacementOnBoard, WhitePawn)
{
	ChessGame g;

	for (int i = 0; i < 8; i++)
	{
		EXPECT_EQ(g.GetIPiece(i + 'a', 2)->GetType(), EType::Pawn);
		EXPECT_EQ(g.GetIPiece(i + 'a', 2)->GetColor(), EColor::White);
	}
}