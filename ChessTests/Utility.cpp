#include "Utility.h"

#include <iostream>
#include <regex>

bool ComparePositionLists(const PositionList& piecePossibleMoves, const PositionList& pieceExpectedMoves)
{
	if (piecePossibleMoves.size() != pieceExpectedMoves.size()) 
		return false;
	for (int i = 0; i < pieceExpectedMoves.size(); i++)
	{
		if (piecePossibleMoves[i] != pieceExpectedMoves[i]) 
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