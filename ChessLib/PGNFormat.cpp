#include "PGNFormat.h"

#include <fstream>

PGNFormat::PGNFormat()
	:m_PGNString("")
{}

std::string PGNFormat::GetPGNFormat() const
{
	return m_PGNString;
}

void PGNFormat::AddMove(const std::string& move)
{
	m_PGNString += move;
}

bool PGNFormat::Save(const std::string& filename)
{
	std::ofstream fout(filename);
	fout << m_PGNString;
	fout.close();
	return true;
}
