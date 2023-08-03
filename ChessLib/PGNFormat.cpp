#include "PGNFormat.h"

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
