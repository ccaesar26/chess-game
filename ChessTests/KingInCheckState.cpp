#include "gtest/gtest.h"

#include "ChessGame.h"



TEST(KingInCheckState, ByHorse)
{
	ChessGame g;
	g.MakeMovement('f', 2, 'f', 3);
	g.MakeMovement('e', 7, 'e', 6);
	g.MakeMovement('a', 2, 'a', 3);
	g.MakeMovement('d', 8, 'h', 4);
	g.MakeMovement('e', 1, 'f', 2);
}