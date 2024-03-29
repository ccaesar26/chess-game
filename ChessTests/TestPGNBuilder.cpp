#include "gtest/gtest.h"

#include "PGNBuilder.h"

#include <vector>
#include <string>

using MoveList = std::vector<std::string>;

MoveList GetMoveList(const std::string& str)
{
	std::string move;
	MoveList moveList;

	for (char c : str)
	{
		if (c != ' ' || move.back() == '.')
			move += c;
		else
		{
			moveList.push_back(move);
			move.clear();
		}
	}
	return moveList;
}

TEST(TestPGNReader, TestAddMove_1)
{
	PGNBuilder builder;

	std::string expectedPGNFormat = "1. a4 h6 2. a5 h5 3. a6 h4 4. axb7 h3 5. bxa8=B Rh7 6. c4 Rh6 7. c5 Rh5 8. c6 f6 9. cxd7+ Kf7 10. dxc8=B Rh4 11. g3 Rh5 12. g4 f5 13. gxh5 f4 14. h6 f3 15. h7 Kg6 16. hxg8=B Kg5 17. Bgd5 Kh6 18. Bdc6 Qe8 19. e3 Qf7 20. Bfa6 Qg6 21. Bc6b7 Qh5 22. Bc6 Qh4 23. Ba6b7 Qg4 24. Ba6 Qg5 25. Bc8b7 Qg6 26. Bc8 Qf6 27. Ba8b7 Qf5 28. Ba8 Qh7 29. Bxf3 Qh8 30. Bfe2 Kg5 31. Bc6 g6 32. Bc6b7 e6 33. Bc6 e5 34. B8b7 e4 35. Bc8 Kh4 36. Bab7 g5 37. Bba6 ";

	MoveList moveList = GetMoveList(expectedPGNFormat);
	for (const auto& move : moveList)
		builder.AddMove(move);

	EXPECT_EQ(builder.GetPGNFormat(), expectedPGNFormat);
}

TEST(TestPGNReader, TestAddMove_2)
{
	PGNBuilder builder;

	std::string expectedPGNFormat = "1. h4 g5 2. f4 e5 3. d4 c5 4. b4 a5 5. bxa5 cxd4 6. hxg5 exf4 7. Nf3 Qxg5 8. g3 Nc6 9. Bh3 d6 10. 0-0 Bxh3 11. Qxd4 0-0-0 12. Qxh8 Qc5+ 13. Kh2 ";

	MoveList moveList = GetMoveList(expectedPGNFormat);
	for (const auto& move : moveList)
		builder.AddMove(move);

	EXPECT_EQ(builder.GetPGNFormat(), expectedPGNFormat);
}