//#include "gtest/gtest.h"
//
//#include "ChessGame.h"
//
//TEST(InitialPiecesPlacementOnBoard, BlackRook)
//{
//	ChessGame g;
//
//	EXPECT_EQ(g.GetBoard()[0][0]->GetName(), EType::Rook);
//	EXPECT_EQ(g.GetBoard()[0][0]->GetColor(), EColor::Black);
//	EXPECT_EQ(g.GetBoard()[0][7]->GetName(), EType::Rook);
//	EXPECT_EQ(g.GetBoard()[0][7]->GetColor(), EColor::Black);
//}
//
//TEST(InitialPiecesPlacementOnBoard, BlackHorse)
//{
//	ChessGame g;
//
//	EXPECT_EQ(g.GetBoard()[0][1]->GetName(), EType::Horse);
//	EXPECT_EQ(g.GetBoard()[0][1]->GetColor(), EColor::Black);
//	EXPECT_EQ(g.GetBoard()[0][6]->GetName(), EType::Horse);
//	EXPECT_EQ(g.GetBoard()[0][6]->GetColor(), EColor::Black);
//}
//
//TEST(InitialPiecesPlacementOnBoard, BlackBishop)
//{
//	ChessGame g;
//
//	EXPECT_EQ(g.GetBoard()[0][2]->GetName(), EType::Bishop);
//	EXPECT_EQ(g.GetBoard()[0][2]->GetColor(), EColor::Black);
//	EXPECT_EQ(g.GetBoard()[0][5]->GetName(), EType::Bishop);
//	EXPECT_EQ(g.GetBoard()[0][5]->GetColor(), EColor::Black);
//}
//
//TEST(InitialPiecesPlacementOnBoard, BlackQueen)
//{
//	ChessGame g;
//
//	EXPECT_EQ(g.GetBoard()[0][3]->GetName(), EType::Queen);
//	EXPECT_EQ(g.GetBoard()[0][3]->GetColor(), EColor::Black);
//}
//
//TEST(InitialPiecesPlacementOnBoard, BlackKing)
//{
//	ChessGame g;
//
//	EXPECT_EQ(g.GetBoard()[0][4]->GetName(), EType::King);
//	EXPECT_EQ(g.GetBoard()[0][4]->GetColor(), EColor::Black);
//}
//
//TEST(InitialPiecesPlacementOnBoard, BlackPawn)
//{
//	ChessGame g;
//
//	for (int i = 0; i < 8; i++)
//	{
//		EXPECT_EQ(g.GetBoard()[1][i]->GetName(), EType::Pawn);
//		EXPECT_EQ(g.GetBoard()[1][i]->GetColor(), EColor::Black);
//	}
//}
//
//TEST(InitialPiecesPlacementOnBoard, WhiteRook)
//{
//	ChessGame g;
//
//	EXPECT_EQ(g.GetBoard()[7][0]->GetName(), EType::Rook);
//	EXPECT_EQ(g.GetBoard()[7][0]->GetColor(), EColor::White);
//	EXPECT_EQ(g.GetBoard()[7][7]->GetName(), EType::Rook);
//	EXPECT_EQ(g.GetBoard()[7][7]->GetColor(), EColor::White);
//}
//
//TEST(InitialPiecesPlacementOnBoard, WhiteHorse)
//{
//	ChessGame g;
//
//	EXPECT_EQ(g.GetBoard()[7][1]->GetName(), EType::Horse);
//	EXPECT_EQ(g.GetBoard()[7][1]->GetColor(), EColor::White);
//	EXPECT_EQ(g.GetBoard()[7][6]->GetName(), EType::Horse);
//	EXPECT_EQ(g.GetBoard()[7][6]->GetColor(), EColor::White);
//}
//
//TEST(InitialPiecesPlacementOnBoard, WhiteBishop)
//{
//	ChessGame g;
//
//	EXPECT_EQ(g.GetBoard()[7][2]->GetName(), EType::Bishop);
//	EXPECT_EQ(g.GetBoard()[7][2]->GetColor(), EColor::White);
//	EXPECT_EQ(g.GetBoard()[7][5]->GetName(), EType::Bishop);
//	EXPECT_EQ(g.GetBoard()[7][5]->GetColor(), EColor::White);
//}
//
//TEST(InitialPiecesPlacementOnBoard, WhiteQueen)
//{
//	ChessGame g;
//
//	EXPECT_EQ(g.GetBoard()[7][3]->GetName(), EType::Queen);
//	EXPECT_EQ(g.GetBoard()[7][3]->GetColor(), EColor::White);
//}
//
//TEST(InitialPiecesPlacementOnBoard, WhiteKing)
//{
//	ChessGame g;
//
//	EXPECT_EQ(g.GetBoard()[7][4]->GetName(), EType::King);
//	EXPECT_EQ(g.GetBoard()[7][4]->GetColor(), EColor::White);
//}
//
//TEST(InitialPiecesPlacementOnBoard, WhitePawn)
//{
//	ChessGame g;
//
//	for (int i = 0; i < 8; i++)
//	{
//		EXPECT_EQ(g.GetBoard()[6][i]->GetName(), EType::Pawn);
//		EXPECT_EQ(g.GetBoard()[6][i]->GetColor(), EColor::White);
//	}
//}