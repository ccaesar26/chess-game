#pragma once

#include <stdexcept>

// Generic exception class //

/**
 * @brief Base exception class for chess-related errors.
 *
 * This exception class is derived from `std::logic_error` and serves as the base class for all
 * chess-related exception classes. It provides constructors for creating exceptions with or
 * without custom error messages.
 */
class ChessException : public std::logic_error
{
public:
	/**
	 * @brief Default constructor for the base exception class.
	 *
	 * Constructs a `ChessException` with a default error message ("Unknown exception").
	 */
	ChessException();

	/**
	 * @brief Constructor for the base exception class with a custom message.
	 *
	 * @param message A custom error message describing the exception.
	 */
	ChessException(const std::string& message);
};

/**
 * @brief Inline constructor implementation for the default ChessException constructor.
 */
inline ChessException::ChessException()
	: std::logic_error("Unknown exception")
{
}

/**
 * @brief Inline constructor implementation for the ChessException constructor with a custom message.
 *
 * @param message A custom error message describing the exception.
 */
inline ChessException::ChessException(const std::string& message)
	: std::logic_error(message)
{
}


 // Specialized exception classes //

 // 1.	Invalid move:
 //		a.	Out of bounds
 //		b.	Occupied square
 //			i.	By enemy piece
 //			ii.	By own piece
 //		c.	NotInPossibleMovesException	
 //		d.	InitialSquareIsEmptyException

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

class OccupiedByEnemyPieceException : public OccupiedSquareException
{
public:
	OccupiedByEnemyPieceException(const std::string&);
};

inline OccupiedByEnemyPieceException::OccupiedByEnemyPieceException(const std::string& message)
	: OccupiedSquareException(message)
{
}

class OccupiedByOwnPieceException : public OccupiedSquareException
{
public:
	OccupiedByOwnPieceException(const std::string&);
};

inline OccupiedByOwnPieceException::OccupiedByOwnPieceException(const std::string& message)
	: OccupiedSquareException(message)
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

class InitialSquareIsEmptyException : public InvalidMoveException
{
public:
	InitialSquareIsEmptyException(const std::string&);
};

inline InitialSquareIsEmptyException::InitialSquareIsEmptyException(const std::string& message)
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

inline InvalidStateException::InvalidStateException(const std::string& message)
	: ChessException(message)
{
}