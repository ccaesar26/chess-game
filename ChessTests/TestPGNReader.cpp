#include "gtest/gtest.h"

#include "PGNReader.h"
#include "Utility.h"

#include <iostream>
#include <regex>


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

// This function is used to generate the string moves in a specific format but is not used in the program//

std::string GetMoveStringForTests(const std::string& str)
{
	std::string move;
	std::string new_string;

	for (char c : str)
	{
		if (c != ' ')
			move += c;
		else
		{
			move = std::regex_replace(move, std::regex("(\\b\\d+\\.\\s*)|\\s+|[+#x*]|1/2-1/2"), "");
			if (!move.empty())
				new_string = new_string + "\"" + move + "\"" + " , ";
			move.clear();
		}
	}
	return new_string;
}

TEST(TestLoadFromFile, TestFromFilePass_1)
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

TEST(TestLoadFromFile, TestFromFilePass_2)
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

TEST(TestLoadFromFile, TestFromFilePass_3)
{
	PGNReader reader;

	bool canLoad = reader.LoadFromFile(".\\TestsForLoadingPGN\\Test3Pass.pgn");

	EXPECT_EQ(canLoad, true);

	StringMoveList moveList = reader.GetMoves();

	StringMoveList expectedMoveList = { "h4" , "g5" , "f4" , "e5" , "d4" , "c5" , "b4" , "a5" , "ba5" , "cd4" , "hg5" 
		, "ef4" , "Nf3" , "Qg5" , "g3" , "Nc6" , "Bh3" , "d6" , "0-0" , "Bh3" , "Qd4" , "0-0-0" , "Qh8" , "Qc5" , "Kh2" };

	EXPECT_EQ(CompareStringMoveLists(moveList, expectedMoveList), true);
}

TEST(TestLoadFromFile, TestFromFilePass_4)
{
	PGNReader reader;

	bool canLoad = reader.LoadFromFile(".\\TestsForLoadingPGN\\Test4Pass.pgn");

	EXPECT_EQ(canLoad, true);

	StringMoveList moveList = reader.GetMoves();

	StringMoveList expectedMoveList = { "f4" , "e6" , "g4" , "Qh4" };

	EXPECT_EQ(CompareStringMoveLists(moveList, expectedMoveList), true);
}

TEST(TestLoadFromFile, TestFromFilePass_5)
{
	PGNReader reader;

	bool canLoad = reader.LoadFromFile(".\\TestsForLoadingPGN\\Test5Pass.pgn");

	EXPECT_EQ(canLoad, true);

	StringMoveList moveList = reader.GetMoves();

	StringMoveList expectedMoveList = { "e4" , "f5" , "Qf3" , "g5" , "Qh5" };

	EXPECT_EQ(CompareStringMoveLists(moveList, expectedMoveList), true);
}