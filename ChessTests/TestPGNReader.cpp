#include "gtest/gtest.h"

#include "PGNReader.h"
#include "Utility.h"


bool CompareStringMoveLists(const StringMoveList List1, const StringMoveList List2)
{
	if (List1.size() != List2.size())
		return false;

	for (int i = 0; i < List1.size(); i++)
	{
		if (List1[i] != List2[i])
			return false;
	}
	return true;
}

TEST(TestLoadFromFile, TestFromFile_1)
{
	PGNReader reader;

	bool canLoad = reader.LoadFromFile(".\\TestsForLoadingPGN\\FourBishopTest.pgn");


	EXPECT_EQ(canLoad, true);

	StringMoveList moveList = reader.GetMoves();
	
	StringMoveList expectedMoveList = { "a4" , "h6" , "a5" , "h5" , "a6" , "h4" , "ab7" , "h3" , "ba8=B" , "Rh7" 
		, "c4" , "Rh6" , "c5" , "Rh5" , "c6" , "f6" , "cd7" , "Kf7" , "dc8=B" , "Rh4" , "g3" , "Rh5" , "g4" , "f5" 
		, "gh5" , "f4" , "h6" , "f3" , "h7" , "Kg6" , "hg8=B" , "Kg5" , "Bgd5" , "Kh6" , "Bdc6" , "Qe8" , "e3" , "Qf7" 
		, "Bfa6" , "Qg6" , "Bc6b7" , "Qh5" , "Bc6" , "Qh4" , "Ba6b7" , "Qg4" , "Ba6" , "Qg5" , "Bc8b7" , "Qg6" , "Bc8" 
		, "Qf6" , "Ba8b7" , "Qf5" , "Ba8" , "Qh7" , "Bf3" , "Qh8" , "Bfe2" , "Kg5" , "Bc6" , "g6" , "Bc6b7" , "e6" 
		, "Bc6" , "e5" , "B8b7" , "e4" , "Bc8" , "Kh4" , "Bab7" , "g5" , "Bba6" };

	EXPECT_EQ(CompareStringMoveLists(moveList,expectedMoveList),true);
}

//TEST(TestLoadFromFile, TestFromFile_2)
//{
//	PGNReader reader;
//
//	bool canLoad = reader.LoadFromFile("C:\\Users\\gplosnita\\source\\repos\\CezarGame.pgn");
//
//
//	EXPECT_EQ(canLoad, true);
//
//	StringMoveList moveList = reader.GetMoves();
//
//	StringMoveList expectedMoveList = { "a4" , "h6" , "a5" , "h5" , "a6" , "h4" , "ab7" , "h3" , "ba8=B" , "Rh7"
//		, "c4" , "Rh6" , "c5" , "Rh5" , "c6" , "f6" , "cd7" , "Kf7" , "dc8=B" , "Rh4" , "g3" , "Rh5" , "g4" , "f5"
//		, "gh5" , "f4" , "h6" , "f3" , "h7" , "Kg6" , "hg8=B" , "Kg5" , "Bgd5" , "Kh6" , "Bdc6" , "Qe8" , "e3" , "Qf7"
//		, "Bfa6" , "Qg6" , "Bc6b7" , "Qh5" , "Bc6" , "Qh4" , "Ba6b7" , "Qg4" , "Ba6" , "Qg5" , "Bc8b7" , "Qg6" , "Bc8"
//		, "Qf6" , "Ba8b7" , "Qf5" , "Ba8" , "Qh7" , "Bf3" , "Qh8" , "Bfe2" , "Kg5" , "Bc6" , "g6" , "Bc6b7" , "e6"
//		, "Bc6" , "e5" , "B8b7" , "e4" , "Bc8" , "Kh4" , "Bab7" , "g5" , "Bba6" };
//
//	EXPECT_EQ(CompareStringMoveLists(moveList, expectedMoveList), true);
//}