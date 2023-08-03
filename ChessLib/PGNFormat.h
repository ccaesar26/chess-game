#pragma once

#include <string>

class PGNFormat
{

public:

	PGNFormat();

	std::string GetPGNFormat() const;

	/*void SetDate(const std::string& date);
	void Set(EHeaderType type, const std::string& value);*/

	void AddMove(const std::string& move);

	bool Save(const std::string& filename);

private:

	std::string m_PGNString;
};

