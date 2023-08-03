#pragma once

#include <string>

class PGNBuilder
{

public:

	PGNBuilder();

	std::string GetPGNFormat() const;

	void AddMove(const std::string& move);

private:

	std::string m_PGNString;
};

