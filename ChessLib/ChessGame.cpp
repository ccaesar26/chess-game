#include "ChessGame.h"
#include "Piece.h"

#include <ctype.h>

// Local Static Functions //

static EType GetType(char c)
{
	// white pieces: p r h b q k
	// black pieces: P R H B Q K
	// empty tile: ' '

	switch (tolower(c))
	{
	case 'p':
		return EType::Pawn;
	case 'r':
		return EType::Rook;
	case 'h':
		return EType::Horse;
	case 'b':
		return EType::Bishop;
	case 'q':
		return EType::Queen;
	case 'k':
		return EType::King;
	}
}

static EColor GetColor(char c)
{
	return islower(c) ? EColor::White : EColor::Black;
}

// Producer //

IChessGamePtr IChessGame::CreateBoard()
{
	return std::make_shared<ChessGame>();
}

// Constructor //

ChessGame::ChessGame()
	: m_turn(EColor::White)
	, m_kingPositions({Position(7 ,4), Position(0, 4)})
	, m_checkState(false)
{
	for (int j = 0; j < 8; j++)
	{
		m_board[6][j] = Piece::Produce(EType::Pawn, EColor::White);
		m_board[1][j] = Piece::Produce(EType::Pawn, EColor::Black);
	}

	const std::vector<EType> TYPES = {EType::Rook, EType::Horse, EType::Bishop, EType::Queen, EType::King, EType::Bishop, EType::Horse, EType::Rook};

	for (int i = 0; i < TYPES.size(); i++)
	{
		m_board[0][i] = Piece::Produce(TYPES[i], EColor::Black);
		m_board[7][i] = Piece::Produce(TYPES[i], EColor::White);
	}
}

ChessGame::ChessGame(const CharBoard& inputConfig, EColor turn)
{
	m_turn = turn;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j< 8; j++)
		{
			if (inputConfig[i][j] == ' ')
				continue;

			EType type = GetType(inputConfig[i][j]);
			EColor color = GetColor(inputConfig[i][j]);

			m_board[i][j] = Piece::Produce(type, color);
			if (type == EType::King)
			{
				m_kingPositions[(int)color] = Position(i, j);
			}
		}
	}
	if (CanBeCaptured(m_board, m_kingPositions[(int)turn]))
		m_checkState = true;
}

// Virtual Implementations //

IPiecePtr ChessGame::GetIPiece(char col, int ln) const
{
	if (col >= 'a')
	{
		return m_board[8 - ln][col - 'a'];
	}
	return m_board[8 - ln][col - 'A'];
}

std::vector<BoardPosition> ChessGame::GetMoves(char col, int row) const
{
	std::vector<BoardPosition> possibleBoardPositions;
	PositionList possiblePositions = GetPossibleMoves(ConvertToPosition(col, row));
	for (int i = 0; i < possiblePositions.size(); i++)
	{
		possibleBoardPositions.push_back(ConvertToBoardPosition(possiblePositions.at(i)));
	}
	return possibleBoardPositions;
}

IPieceList ChessGame::GetCapturedPieces(EColor color) const
{
	return color == EColor::White ? m_whitePiecesCaptured : m_blackPiecesCaptured;
}

EColor ChessGame::GetCurrentPlayer() const
{
	return m_turn;
}

bool ChessGame::IsGameOver() const
{
	if (!m_checkState)
	{
		return false;
	}

	Position checkPiecePos;
	PieceList checkPieces = GetCheckPieces(checkPiecePos);

	PositionList kingPossibleMoves = GetPossibleMoves(m_kingPositions[(int)m_turn]);

	if (!kingPossibleMoves.empty())
	{
		return false;
	}
	if (checkPieces.size() > 1)
	{
		return true;
	}

	if (CheckPieceCanBeCaptured(checkPiecePos))
	{
		return false;
	}

	// Case 3 // 

	if (checkPieces.at(0)->GetType() == EType::King ||
		checkPieces.at(0)->GetType() == EType::Pawn ||
		checkPieces.at(0)->GetType() == EType::Horse)
	{
		return true;
	}

	

	if (toBlockPositions.empty() == true) 
		return true;
 
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (m_board[i][j] && m_board[i][j]->GetColor() == m_turn)
			{
				PositionList possibleMoves = GetPossibleMoves(Position(i, j));
				for (auto pos : toBlockPositions)
				{
					if (std::find(possibleMoves.begin(), possibleMoves.end(), pos) != possibleMoves.end()) 
						return false;
				}
			}
		}
	}

	return true;
}

void ChessGame::MakeMovement(char initialColumn, int initialRow, char finalColumn, int finalRow)
{
	MakeMove(ConvertToPosition(initialColumn, initialRow), ConvertToPosition(finalColumn, finalRow));
}

// Game's Logic //

PiecePtr ChessGame::GetPiece(Position pos, const ArrayBoard& board) const
{
	return board[pos.row][pos.col];
}

PieceList ChessGame::GetCheckPieces(Position& checkPos) const
{
	PieceList checkPieces;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (m_board[i][j] && m_board[i][j]->GetColor() != m_turn)
			{
				PositionList enemyPiecePositions = m_board[i][j]->GetPattern(Position(i, j),
					std::bind(&ChessGame::GetPiece, this, std::placeholders::_1, m_board));

				for (auto pos : enemyPiecePositions)
				{
					if (pos == m_kingPositions[(int)m_turn])
					{
						if (checkPieces.empty())
						{
							checkPieces.push_back(m_board[i][j]);
							checkPos = Position(i, j);
						}
						else
						{
							checkPieces.push_back(m_board[i][j]);
							break;
						}
					}
				}
			}
		}
	}
}

bool ChessGame::CheckPieceCanBeCaptured(const Position& checkPiecePos) const
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (m_board[i][j] && m_board[i][j]->GetColor() == m_turn)
			{
				PositionList ownPiecePositions = GetPossibleMoves(Position(i, j));
				for (auto pos : ownPiecePositions)
				{
					if (pos == checkPiecePos)
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

Position ChessGame::GetMovingDirections(const Position& checkPiecePos) const
{
	int movingRow;
	int movingCol;

	Position kingPosition = m_kingPositions[(int)m_turn];

	if (kingPosition.row < checkPiecePos.row)
	{
		movingRow = -1;
	}
	else if (kingPosition.row > checkPiecePos.row)
	{
		movingRow = 1;
	}
	else
	{
		movingRow = 0;
	}

	if (kingPosition.col < checkPiecePos.col)
	{
		movingCol = -1;
	}
	else if (kingPosition.col > checkPiecePos.col)
	{
		movingCol = 1;
	}
	else
	{
		movingCol = 0;
	}

	return Position(movingRow, movingCol);
}

PositionList ChessGame::GetToBlockPositions(const Position& checkPiecePos) const
{
	Position kingPosition = m_kingPositions[(int)m_turn];
	PositionList toBlockPositions;
	Position movingDirections = GetMovingDirections(checkPiecePos);

	/*for (
		int i = checkPiecePos.row + movingDirections.row, 
			 j = checkPiecePos.col + movingDirections.col;
		i != kingPosition.row && j != kingPosition.col; 
		i += movingDirections.row, j += movingDirections.col)
	{

	}*/

	// de rescris while -> for

	int i_row = checkPiecePos.row + movingRow;
	int i_col = checkPiecePos.col + movingCol;

	while (i_row != kingPosition.row && i_col != kingPosition.col)
	{
		toBlockPositions.push_back(Position(i_row, i_col));
		i_row += movingRow;
		i_col += movingCol;
	}
}

void ChessGame::SwitchTurn()
{
	if (m_turn == EColor::White)
	{
		m_turn = EColor::Black;
	}
	else
	{
		m_turn = EColor::White;
	}
}

bool ChessGame::CanBeCaptured(const ArrayBoard& board, Position toCapturePos) const
{
	EColor pieceColor = board[toCapturePos.row][toCapturePos.col]->GetColor();

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j] && board[i][j]->GetColor() != pieceColor)
			{
				Position atackingPiecePosition(i, j);
				PositionList enemyPiecePositions = board[i][j]->GetPattern(atackingPiecePosition, 
					std::bind(&ChessGame::GetPiece, this, std::placeholders::_1, board));

				for (auto pos : enemyPiecePositions)
				{
					if (pos == toCapturePos)
						return true;
				}
			}
		}
	}
	return false;
}

PositionList ChessGame::GetPossibleMoves(Position currentPos) const
{
	PositionList possibleMoves;
	PiecePtr currentPiece = m_board[currentPos.row][currentPos.col];

	if (currentPiece)
	{
		if (currentPiece->GetColor() == m_turn)
		{
			possibleMoves = currentPiece->GetPattern(currentPos, 
				std::bind(&ChessGame::GetPiece, this, std::placeholders::_1, m_board));
		}
	}

	for (int i = 0; i < possibleMoves.size(); i++)
	{
		Position pos = possibleMoves[i];  // The pos variable is for iterating the possible moves //

		PiecePtr currentPieceCopy = m_board[currentPos.row][currentPos.col];
		PiecePtr finalPieceCopy = m_board[pos.row][pos.col];

		// Create alternative board  My code //

		ArrayBoard boardAfterMove = m_board;
		Position kingPosition = m_kingPositions[(int)m_turn];

		boardAfterMove[pos.row][pos.col] = boardAfterMove[currentPos.row][currentPos.col];
		boardAfterMove[currentPos.row][currentPos.col].reset();

		if (boardAfterMove[pos.row][pos.col]->GetType() == EType::King)
			kingPosition = pos;

		if (CanBeCaptured(boardAfterMove, kingPosition))
		{
			possibleMoves.erase(std::find(possibleMoves.begin(), possibleMoves.end(), pos));
			i--;
		}
	}
	
	return possibleMoves;
}

void ChessGame::MakeMove(Position initialPosition, Position finalPosition)
{
	PositionList possibleMoves = GetPossibleMoves(initialPosition);
	if (std::find(possibleMoves.begin(), possibleMoves.end(), finalPosition) == possibleMoves.end()) 
		throw "Your move is not possible !";

	if (m_board[finalPosition.row][finalPosition.col])
	{
		if (m_turn == EColor::White) 
			m_blackPiecesCaptured.push_back(m_board[finalPosition.row][finalPosition.col]);
		else 
			m_whitePiecesCaptured.push_back(m_board[finalPosition.row][finalPosition.col]);
	}

	m_board[finalPosition.row][finalPosition.col] = m_board[initialPosition.row][initialPosition.col];
	m_board[initialPosition.row][initialPosition.col].reset();

	if (m_board[finalPosition.row][finalPosition.col]->GetType() == EType::King)
	{
		m_kingPositions[(int)m_turn] = finalPosition;
	}

	SwitchTurn();

	if (CanBeCaptured(m_board, m_kingPositions[(int)m_turn]) == true)
		m_checkState = true;
}

// Static Methods //

bool ChessGame::IsInMatrix(Position piecePosition)
{
	if (piecePosition.row < 0 || piecePosition.row > 7 || 
		piecePosition.col < 0 || piecePosition.col > 7)
	{
		return false;
	}
	return true;
}
Position ChessGame::ConvertToPosition(char col, int ln)
{
	if (col >= 'a')
	{
		return Position(8 - ln, col - 'a');
	}
	return Position(8 - ln, col - 'A');
}

BoardPosition ChessGame::ConvertToBoardPosition(Position pos)
{
	return BoardPosition(pos.col + 'A', 8 - pos.row);
}