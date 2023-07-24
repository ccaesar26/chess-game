#pragma once

#include <stdexcept>

// Generic exception class //

class ChessException : public std::logic_error
{
public:
	ChessException();
	ChessException(const std::string&);
};

inline ChessException::ChessException()
	: std::logic_error("Unknown exception")
{
}

inline ChessException::ChessException(const std::string& message)
	: std::logic_error(message)
{
}

 // Specialized exception classes //

 // 1.	Invalid move:
 //		a.	Out of bounds
 //		b.	Occupied square
 //		c.	NotInPossibleMovesException	

class InvalidMoveException : public ChessException
{
public:
	InvalidMoveException(const std::string&);
};

inline InvalidMoveException::InvalidMoveException(const std::string& message)
	: ChessException(message)
{
}

class OutOfBoundsException : public InvalidMoveException
{
public:
	OutOfBoundsException(const std::string&);

private:

};

inline OutOfBoundsException::OutOfBoundsException(const std::string& message)
	: InvalidMoveException(message)
{
}

class OccupiedSquareException : public InvalidMoveException
{
public:
	OccupiedSquareException(const std::string&);

private:

};

inline OccupiedSquareException::OccupiedSquareException(const std::string& message)
	: InvalidMoveException(message)
{
}

class NotInPossibleMovesException : public InvalidMoveException
{
public:
	NotInPossibleMovesException(const std::string&);

private:

};

inline NotInPossibleMovesException::NotInPossibleMovesException(const std::string& message)
	: InvalidMoveException(message)
{
}


// 2.	Invalid input:
//		a.	Invalid answer
//		b.	Invalid upgrade
//		c.	Invalid position
//			i.	Invalid BoardPosition
//			ii.	Invalid MemoryPosition

class InvalidInputException : public ChessException
{
public:
	InvalidInputException(const std::string&);
};

inline InvalidInputException::InvalidInputException(const std::string& message)
	: ChessException(message)
{
}

class InvalidAnswerException : public InvalidInputException
{
public:
	InvalidAnswerException(const std::string&);
};

inline InvalidAnswerException::InvalidAnswerException(const std::string& message)
	: InvalidInputException(message)
{
}

class InvalidUpgradeException : public InvalidInputException
{
public:
	InvalidUpgradeException(const std::string&);
};

inline InvalidUpgradeException::InvalidUpgradeException(const std::string& message)
	: InvalidInputException(message)
{
}

class InvalidPositionException : public InvalidInputException
{
public:
	InvalidPositionException(const std::string&);
};

inline InvalidPositionException::InvalidPositionException(const std::string& message)
	: InvalidInputException(message)
{
}

class InvalidBoardPositionException : public InvalidPositionException
{
public:
	InvalidBoardPositionException(const std::string&);
};

inline InvalidBoardPositionException::InvalidBoardPositionException(const std::string& message)
	: InvalidPositionException(message)
{
}

class InvalidMemoryPositionException : public InvalidPositionException
{
public:
	InvalidMemoryPositionException(const std::string&);
};

inline InvalidMemoryPositionException::InvalidMemoryPositionException(const std::string& message)
	: InvalidPositionException(message)
{
}

// 3.	Invalid state 

class InvalidStateException : public ChessException
{
public:
	InvalidStateException(const std::string&);

private:

};

InvalidStateException::InvalidStateException(const std::string& message)
	: ChessException(message)
{
}
