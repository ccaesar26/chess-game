#include "PGNReader.h"

#include <fstream>
#include <regex>

PGNReader::PGNReader()
	:m_PGNString("")
{
	m_moves.resize(0);
}

bool PGNReader::LoadFromFile(std::string& fileName)
{
	std::ifstream fileStream(fileName);

	if (!fileStream.is_open())
		return false;

	char c;
	std::string move = "";

	while (fileStream >> c)
	{
		m_PGNString += c;
		if (c != ' ')
			move += c;
		else
		{
			move = std::regex_replace(move, std::regex("\\b\\d+\\. |[+#x*]|1/2-1/2|\\s*"), "");
			m_moves.push_back(move);
		}
	}
	return true;
}

const StringMoveList& PGNReader::GetMoves()
{
	return m_moves;
}
