#pragma once

#include <vector>
#include <string>

using StringMoveList = std::vector<std::string>;

class PGNReader
{

public:

	PGNReader();

	bool LoadFromFile(std::string& fileName);

	const StringMoveList& GetMoves();

private:

	std::string m_PGNString;
	StringMoveList m_moves;
};


