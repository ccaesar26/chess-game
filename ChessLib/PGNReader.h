#pragma once

#include <vector>
#include <string>

using StringMoveList = std::vector<std::string>;

class PGNReader
{

public:

	PGNReader();

	bool LoadFromFile(std::string& fileName);
	bool LoadFromString(const std::string& str);

	const StringMoveList& GetMoves();

private:

	StringMoveList m_moves;
};


