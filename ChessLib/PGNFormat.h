#pragma once

#include <string>

class PGNFormat
{

public:

	PGNFormat();

	std::string GetPGNFormat() const;

	void AddMove(const std::string& move);

private:

	std::string m_PGNString;
};

