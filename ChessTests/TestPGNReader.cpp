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

	bool canLoad = reader.LoadFromFile(".\\TestsForLoadingPGN\\Test1Pass.pgn");


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

TEST(TestLoadFromFile, TestFromFile_2)
{
	PGNReader reader;

	bool canLoad = reader.LoadFromFile(".\\TestsForLoadingPGN\\Test2Pass.pgn");


	EXPECT_EQ(canLoad, true);

	StringMoveList moveList = reader.GetMoves();

	StringMoveList expectedMoveList = { "d4" , "Nf6" , "h4" , "e6" , "h5" , "Ba3" , "h6" , "0-0" , "hg7" , "e5" , "gf8=N" 
		, "Ne8" , "Nh7" , "f5" , "Be3" , "f4" , "Nc3" , "f3" , "Qd2" , "fg2" , "0-0-0" , "gh1=Q" , "Ne4" , "Bb4" , "Nf3" 
		, "a6" , "Neg5" , "a5" , "Ne4" , "a4" , "Nfg5" , "a3" , "Nf3" , "ab2" , "Kb1" , "Bc5" , "Nhg5" , "Bd6" , "c4" , "b5" 
		, "Kc2" , "b1=B" , "Kc1" , "Be4" , "a3" , "Bb4" , "a4" , "d5" , "a5" , "Be6" , "Nh7" , "Qf6" , "a6" , "Qg6" , "a7" 
		, "Qh4" , "ab8=Q" , "Qhg4" , "Qa7" , "B4f5" , "Qa6" , "Be4" , "Qa5" , "B6f5" , "Qa4" , "Be6" , "Qa3" , "Q6f5" , "Qaa2" 
		, "Qfg6" , "Qb4" , "Q6h5" , "Qd6" , "Nf6" , "Qe6" , "Kh8" , "Qf6" , "Kg8" , "cd5" , "b4" , "d6" , "Kh7" , "Rd3" , "b3" 
		, "Rc3" , "b2" , "Kd2" , "b1=N" , "Ke1" , "c5" , "Qa6" , "Na3" , "Qa8" , "Nc2" , "Rc2" , "c4" , "Rc4" , "Bb1" , "Rc7" 
		, "Qd7" , "Rd7" , "Qf7" , "Rf7" };

	EXPECT_EQ(CompareStringMoveLists(moveList, expectedMoveList), true);
}