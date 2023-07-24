#include "ChessGame.h"
#include "Piece.h"
#include "ChessException.h"

#include <cctype>

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
	, m_state(EGameState::MovingPiece)
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
	: m_turn(turn)
	, m_state(EGameState::MovingPiece)
{
	m_turn = turn;
	m_kingPositions.resize(2);

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j< 8; j++)
		{
			if (inputConfig[i][j] == ' ')
			{
				continue;
			}

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
	{
		m_state = EGameState::CheckState;
	}
}

// Virtual Implementations //

IPiecePtr ChessGame::GetIPiece(char col, int ln) const
{
	if (ln <= 0 || ln >= 8)
	{
		throw InvalidBoardPositionException("Line out of range");
	}
	if (col >= 'a' && col <= 'h')
	{
		return m_board[8 - ln][col - 'a'];
	}
	if (col >= 'A' && col <= 'H')
	{
		return m_board[8 - ln][col - 'A'];
	}
	throw InvalidBoardPositionException("Column out of range");
}

std::vector<BoardPosition> ChessGame::GetMoves(char col, char row) const
{
	std::vector<BoardPosition> possibleBoardPositions;
	PositionList possiblePositions = GetPossibleMoves(ConvertToMemoryPosition(col, row));
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
	if (m_state == EGameState::Draw || m_state == EGameState::WonByWhitePlayer || m_state == EGameState::WonByBlackPlayer)
	{
		return true;
	}

	if (m_state != EGameState::CheckState)
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

	if (checkPieces.at(0)->GetType() == EType::King ||
		checkPieces.at(0)->GetType() == EType::Pawn ||
		checkPieces.at(0)->GetType() == EType::Horse)
	{
		return true;
	}

	PositionList toBlockPositions = GetToBlockPositions(checkPiecePos);

	if (toBlockPositions.empty())
	{
		return true;
	}
	if (KingsWayCanBeBlocked(toBlockPositions))
	{
		return false;
	}

	return true;
}

void ChessGame::MakeMovement(char initialColumn, char initialRow, char finalColumn, char finalRow)
{
	MakeMove(ConvertToMemoryPosition(initialColumn, initialRow), ConvertToMemoryPosition(finalColumn, finalRow));
	if (IsGameOver())
	{
		if (m_turn == EColor::White)
		{
			m_state = EGameState::WonByBlackPlayer;
		}
		else
		{
			m_state = EGameState::WonByWhitePlayer;
		}
	}
}

void ChessGame::UpgradePawn(std::string upgradeType)
{
	for (auto i = 0; i < upgradeType.size(); i++)
	{
		tolower(upgradeType[i]);
	}

	Position upgradePos;
	if (m_turn == EColor::White)
	{
		for (int i = 0; i < 8; i++)
		{
			if (m_board[0][i] && m_board[0][i]->GetType() == EType::Pawn)
			{
				upgradePos.row = 0;
				upgradePos.col = i;
			}
		}
	}
	else
	{
		for (int i = 0; i < 8; i++)
		{
			if (m_board[0][i] && m_board[7][i]->GetType() == EType::Pawn)
			{
				upgradePos.row = 7;
				upgradePos.col = i;
			}
		}
	}

	if (upgradeType == "queen")
	{
		m_board[upgradePos.row][upgradePos.col] = Piece::Produce(EType::Queen, m_turn);
	}
	else if (upgradeType == "bishop")
	{
		m_board[upgradePos.row][upgradePos.col] = Piece::Produce(EType::Bishop, m_turn);
	}
	else if (upgradeType == "rook")
	{
		m_board[upgradePos.row][upgradePos.col] = Piece::Produce(EType::Rook, m_turn);
	}
	else if(upgradeType == "horse")
	{
		m_board[upgradePos.row][upgradePos.col] = Piece::Produce(EType::Horse, m_turn);
	}
	else
	{
		std::string m = "The type " + upgradeType + " is not a valid upgrade";
		throw InvalidUpgradeException(m);
	}

	m_state = EGameState::MovingPiece;

	SwitchTurn();

	if (CanBeCaptured(m_board, m_kingPositions[(int)m_turn]) == true)
	{
		m_state = EGameState::CheckState;
	}
}

void ChessGame::RequestDraw()
{
	m_state = EGameState::WaitingForDrawResponse;
}

void ChessGame::AcceptDrawProposal()
{
	m_state = EGameState::Draw;
}

void ChessGame::DeclineDrawProposal()
{
	m_state = EGameState::MovingPiece;
}

bool ChessGame::IsDraw() const
{
	return m_state == EGameState::Draw ? true : false;
}

bool ChessGame::IsWonByWhitePlayer() const
{
	return m_state == EGameState::WonByWhitePlayer ? true : false;
}

bool ChessGame::IsWonByBlackPlayer() const
{
	return m_state == EGameState::WonByBlackPlayer ? true : false;
}

bool ChessGame::IsWaitingForUpgrade() const
{
	return m_state == EGameState::UpgradePawn ? true : false;
}

bool ChessGame::IsWaitingForDrawResponse() const
{
	return m_state == EGameState::WaitingForDrawResponse ? true : false;
}

bool ChessGame::IsCheckState() const
{
	return m_state == EGameState::CheckState ? true : false;
}

// Game's Logic //

PiecePtr ChessGame::GetPiece(Position pos, const ArrayBoard& board) const
{
	return board[pos.row][pos.col];
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
		{
			kingPosition = pos;
		}

		if (CanBeCaptured(boardAfterMove, kingPosition))
		{
			possibleMoves.erase(std::find(possibleMoves.begin(), possibleMoves.end(), pos));
			i--;
		}
	}

	return possibleMoves;
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
	return checkPieces;
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

	Position iterator_pos(checkPiecePos.row + movingDirections.row, checkPiecePos.col + movingDirections.col);

	while (iterator_pos != kingPosition)
	{
		toBlockPositions.push_back(iterator_pos);
		iterator_pos.row += movingDirections.row;
		iterator_pos.col += movingDirections.col;
	}

	return toBlockPositions;
}

bool ChessGame::KingsWayCanBeBlocked(const PositionList& toBlockPositions) const
{
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
					{
						return true;
					}
				}
			}
		}
	}
	return false;
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
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

void ChessGame::MakeMove(Position initialPosition, Position finalPosition)
{
	if (m_state == EGameState::UpgradePawn)
	{
		throw "You must upgrade pawn";
	}

	PositionList possibleMoves = GetPossibleMoves(initialPosition);
	if (std::find(possibleMoves.begin(), possibleMoves.end(), finalPosition) == possibleMoves.end()) 
	{
		throw "Your move is not possible !"; 
	}

	if (m_board[finalPosition.row][finalPosition.col])
	{
		if (m_turn == EColor::White) 
		{
			m_blackPiecesCaptured.push_back(m_board[finalPosition.row][finalPosition.col]);
		}
		else
		{
			m_whitePiecesCaptured.push_back(m_board[finalPosition.row][finalPosition.col]);
		}
	}

	m_board[finalPosition.row][finalPosition.col] = m_board[initialPosition.row][initialPosition.col];
	m_board[initialPosition.row][initialPosition.col].reset();

	if (m_board[finalPosition.row][finalPosition.col]->GetType() == EType::King)
	{
		m_kingPositions[(int)m_turn] = finalPosition;
	}
	else if (m_board[finalPosition.row][finalPosition.col]->GetType() == EType::Pawn)
	{
		if (m_board[finalPosition.row][finalPosition.col]->GetColor() == EColor::White && finalPosition.row == 0)
		{
			m_state = EGameState::UpgradePawn;
			return;
		}
	}

	SwitchTurn();

	if (CanBeCaptured(m_board, m_kingPositions[(int)m_turn]) == true)
	{
		m_state = EGameState::CheckState;
	}
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
Position ChessGame::ConvertToMemoryPosition(char col, char row) const
{
	if (col >= 'a') 
	{
		return Position(8 - (row - '0'), col - 'a');
	}
	return Position(8 - (row - '0'), col - 'A');
}

BoardPosition ChessGame::ConvertToBoardPosition(Position pos) const
{
	return BoardPosition(pos.col + 'A', 8 - pos.row + '0');
}