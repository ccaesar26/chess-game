#pragma once

#include <string>

enum class EFormat
{
	Pgn
};

class IChessGameStorage
{
public:
	virtual ~IChessGameStorage() = default;

	virtual bool LoadFromFile(EFormat format, const std::string& fileName) = 0;
	virtual bool SaveFormat(EFormat format, const std::string& fileName) const = 0;

	virtual std::string GetFormat(EFormat format) const = 0;
};
