#include "PGNBuilder.h"

PGNBuilder::PGNBuilder()
	:m_PGNString("")
{}

std::string PGNBuilder::GetPGNFormat() const
{
	return m_PGNString;
}

void PGNBuilder::AddMove(const std::string& move)
{
	m_PGNString = m_PGNString + move + " ";
}
