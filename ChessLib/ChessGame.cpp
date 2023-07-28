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

	static const EType types[] = { EType::Pawn,EType::Rook, EType::Horse, EType::Bishop, EType::Queen, EType::King };

	std::string str = "prhbqk";
	int pos = str.find_first_of(tolower(c));

	return types[pos];
}

static EColor GetColor(char c)
{
	return islower(c) ? EColor::White : EColor::Black;
}

// Producer //

IChessGamePtr IChessGame::CreateGame()
{
	return std::make_shared<ChessGame>();
}

// Constructor //

ChessGame::ChessGame()
{
	InitializeChessGame();
}

ChessGame::ChessGame(const CharBoard& inputConfig, EColor turn) 
	: m_turn(turn)
	, m_state(EGameState::MovingPiece)
{
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			m_Castle[i][j] = true;

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

void ChessGame::InitializeChessGame()
{
	m_turn = EColor::White;
	m_kingPositions = { Position(7 ,4), Position(0, 4) };
	m_state = EGameState::MovingPiece;

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			m_Castle[i][j] = true;

	for (int j = 0; j < 8; j++)
	{
		m_board[6][j] = Piece::Produce(EType::Pawn, EColor::White);
		m_board[1][j] = Piece::Produce(EType::Pawn, EColor::Black);
	}

	const std::vector<EType> TYPES = { EType::Rook, EType::Horse, EType::Bishop, EType::Queen, EType::King, EType::Bishop, EType::Horse, EType::Rook };

	for (int i = 0; i < TYPES.size(); i++)
	{
		m_board[0][i] = Piece::Produce(TYPES[i], EColor::Black);
		m_board[7][i] = Piece::Produce(TYPES[i], EColor::White);
	}
}

void ChessGame::ResetGame()
{
	ResetBoard();

	m_whitePiecesCaptured.clear();
	m_blackPiecesCaptured.clear();
	m_boardConfigurationsRepetitons.clear();

	InitializeChessGame();

	Notify(ENotification::Reset);
}

void ChessGame::SetCastleValues(const CastleValues& Castle)
{
	m_Castle = Castle;
}

// Virtual Implementations //

IPiecePtr ChessGame::GetIPiecePtr(Position pos) const
{
	if(IsInMatrix(pos))
		return m_board[pos.row][pos.col];

	throw InvalidBoardPositionException("Position out of range");
}

IPieceList ChessGame::GetCapturedPieces(EColor color) const
{
	return color == EColor::White ? m_whitePiecesCaptured : m_blackPiecesCaptured;
}

EColor ChessGame::GetCurrentPlayer() const
{
	return m_turn;
}

bool ChessGame::IsStaleMate() const
{
	if (m_state != EGameState::MovingPiece)
		return false;
	
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (m_board[i][j] && m_board[i][j]->GetColor() == m_turn)
			{
				PositionList possibleMoves = GetPossibleMoves(Position(i, j));
				if (!possibleMoves.empty())
					return false;
			}
		}
	}
	return true;
}

bool ChessGame::IsGameOver() const
{
	if (m_state == EGameState::Draw || m_state == EGameState::WonByWhitePlayer || m_state == EGameState::WonByBlackPlayer)
	{
		//Notify(ENotification::GameOver);
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
		//Notify(ENotification::GameOver);
		return true;
	}

	if (CheckPieceCanBeCaptured(checkPiecePos))
	{
		return false;
	}

	if (checkPieces.front()->Is({ EType::King, EType::Pawn, EType::Horse }))
	{
		//Notify(ENotification::GameOver);
		return true;
	}

	PositionList toBlockPositions = GetToBlockPositions(checkPiecePos);

	if (toBlockPositions.empty())
	{
		//Notify(ENotification::GameOver);
		return true;
	}
	if (KingsWayCanBeBlocked(toBlockPositions))
	{
		return false;
	}

	//Notify(ENotification::GameOver);
	return true;
}

void ChessGame::MakeMovement(Position initialPos, Position finalPos)
{
	MakeMove(initialPos, finalPos);

	Notify(ENotification::MoveMade, initialPos, finalPos);

	switch (m_state)
	{
	case EGameState::Draw:
	case EGameState::WonByWhitePlayer:
	case EGameState::WonByBlackPlayer:
		Notify(ENotification::GameOver);
		break;
	case EGameState::UpgradePawn:
		Notify(ENotification::PawnUpgrade, initialPos, finalPos);
		break;
	case EGameState::CheckState:
		Notify(ENotification::Check);
		break;
	default:
		break;
	}
}

void ChessGame::UpgradePawn(EType upgradeType)
{
	/*for (auto i = 0; i < upgradeType.size(); i++)
	{
		upgradeType[i] = tolower(upgradeType[i]);
	}*/

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
			if (m_board[7][i] && m_board[7][i]->GetType() == EType::Pawn)
			{
				upgradePos.row = 7;
				upgradePos.col = i;
			}
		}
	}

	m_board[upgradePos.row][upgradePos.col] = Piece::Produce(upgradeType, m_turn);
	
	m_state = EGameState::MovingPiece;

	SwitchTurn();

	if (CanBeCaptured(m_board, m_kingPositions[(int)m_turn]) == true)
	{
		m_state = EGameState::CheckState;
	}

	if (IsStaleMate())
	{
		m_state = EGameState::Draw;
	}

	if (IsGameOver())
	{
		m_state = m_turn == EColor::White ? EGameState::WonByBlackPlayer : EGameState::WonByWhitePlayer;
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
	return m_state == EGameState::Draw;
}

bool ChessGame::IsWonByWhitePlayer() const
{
	return m_state == EGameState::WonByWhitePlayer;
}

bool ChessGame::IsWonByBlackPlayer() const
{
	return m_state == EGameState::WonByBlackPlayer;
}

bool ChessGame::IsWaitingForUpgrade() const
{
	return m_state == EGameState::UpgradePawn;
}

bool ChessGame::IsWaitingForDrawResponse() const
{
	return m_state == EGameState::WaitingForDrawResponse;
}

bool ChessGame::IsCheckState() const
{
	return m_state == EGameState::CheckState;
}

// Observers //

void ChessGame::AddListener(IChessGameListenerPtr listener)
{
	m_listeners.push_back(listener);
}

void ChessGame::RemoveListener(IChessGameListener* listener)
{
	/*
	for (auto it = m_listeners.begin(); it != m_listeners.end();)
	{
		if (auto sp = it->lock())
		{
			if (sp.get())
			{
				it = m_listeners.erase(it);
			}
			else
			{
				it++;
			}
		}
		else
		{
			m_listeners.erase(it);
		}
	}
	*/
	auto f = [listener](IChessGameListenerWeakPtr& weak) {
		auto sp = weak.lock();

		return !sp || sp.get() == listener;
	};

	m_listeners.erase(std::remove_if(m_listeners.begin(), m_listeners.end(), f));
}

void ChessGame::Notify(ENotification notif, Position init, Position fin)
{
	for (auto it = m_listeners.begin(); it != m_listeners.end(); it++)
	{
		if (auto sp = it->lock())
		{
			if (notif == ENotification::MoveMade)
			{
				sp->OnMoveMade(init, fin);
			}
			else if (notif == ENotification::PawnUpgrade)
			{
				sp->OnPawnUpgrade(init, fin);
			}
		}
	}
}

void ChessGame::Notify(ENotification notif)
{
	for (auto it = m_listeners.begin(); it != m_listeners.end(); it++)
	{
		if (auto sp = it->lock())
		{
			switch (notif)
			{
			case ENotification::GameOver:
			{
				auto result = EGameResult::Draw;
				if (IsWonByWhitePlayer())
					result = EGameResult::WhitePlayerWon;
				if (IsWonByBlackPlayer())
					result = EGameResult::BlackPlayerWon;
				sp->OnGameOver(result);
				break;
			}
			case ENotification::Check:
				sp->OnCheck();
				break;
			case ENotification::Reset:
				sp->OnGameRestarted();
			default:
				break;
			}
		}
	}
}

// Game's Logic //

PiecePtr ChessGame::GetPiece(Position pos, const ArrayBoard& board) const
{
	return board[pos.row][pos.col];
}

void ChessGame::AddCastle(Position kingPosition, PositionList& kingPossibleMoves) const
{
	PiecePtr king = m_board[kingPosition.row][kingPosition.col];

	ArrayBoard boardAfterMove = m_board;

	// Add Left Castle //

	PositionList toCheckPositions = { kingPosition,Position(kingPosition.row,kingPosition.col - 1)
		, Position(kingPosition.row,kingPosition.col - 2) };

	if (m_Castle[(int)king->GetColor()][0] == true)
	{
		if (m_board[kingPosition.row][0] && m_board[kingPosition.row][0]->Is(EType::Rook)
			&& m_board[kingPosition.row][0]->GetColor() == m_turn)
		{
			if (!m_board[kingPosition.row][kingPosition.col - 1] && !m_board[kingPosition.row][kingPosition.col - 2] && !m_board[kingPosition.row][kingPosition.col - 3])
			{
				bool leftCastle = true;
				for (auto pos : toCheckPositions)
				{
					if (pos != kingPosition)
					{
						boardAfterMove[pos.row][pos.col] = boardAfterMove[pos.row][pos.col + 1];
						boardAfterMove[pos.row][pos.col + 1].reset();
					}

					if (CanBeCaptured(boardAfterMove, pos))
					{
						leftCastle = false;
						break;
					}
				}

				if (leftCastle)
					kingPossibleMoves.push_back(Position(kingPosition.row, kingPosition.col - 2));
			}
		}	
	}

	// Add Right Castle //

	boardAfterMove = m_board;

	toCheckPositions = { kingPosition,Position(kingPosition.row,kingPosition.col + 1)
		, Position(kingPosition.row,kingPosition.col + 2) };

	if (m_Castle[(int)king->GetColor()][1] == true)
	{
		if (m_board[kingPosition.row][7] && m_board[kingPosition.row][7]->GetType() == EType::Rook
			&& m_board[kingPosition.row][7]->GetColor() == m_turn)
		{
			if (!m_board[kingPosition.row][kingPosition.col + 1] && !m_board[kingPosition.row][kingPosition.col + 2])
			{
				bool rightCastle = true;
				for (auto pos : toCheckPositions)
				{
					if (pos != kingPosition)
					{
						boardAfterMove[pos.row][pos.col] = boardAfterMove[pos.row][pos.col - 1];
						boardAfterMove[pos.row][pos.col - 1].reset();
					}

					if (CanBeCaptured(boardAfterMove, pos))
					{
						rightCastle = false;
						break;
					}
				}

				if (rightCastle)
					kingPossibleMoves.push_back(Position(kingPosition.row, kingPosition.col + 2));
			}
		}
	}
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

	if (currentPiece && currentPiece->GetType() == EType::King)
	{
		AddCastle(currentPos, possibleMoves);
	}

	return possibleMoves;
}

void ChessGame::ResetBoard()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			m_board[i][j].reset();
		}
	}
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
	m_turn = m_turn == EColor::White ? EColor::Black : EColor::White;
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
	if (!IsInMatrix(initialPosition))
	{
		throw OutOfBoundsException("Initial position is not a valid position");
	}
	if (!IsInMatrix(finalPosition))
	{
		throw OutOfBoundsException("Final position is not a valid position");
	}

	if (m_state == EGameState::UpgradePawn)
	{
		throw InvalidStateException("You must upgrade pawn");
	}

	PositionList possibleMoves = GetPossibleMoves(initialPosition);
	if (std::find(possibleMoves.begin(), possibleMoves.end(), finalPosition) == possibleMoves.end())
	{
		if (!m_board[finalPosition.row][finalPosition.col])
		{
			throw NotInPossibleMovesException("Your move is not possible");
		}
		if (m_board[finalPosition.row][finalPosition.col]->GetColor() != m_turn)
		{
			throw OccupiedByEnemyPieceException("Your move is not possible !");
		}
		else
		{
			throw OccupiedByOwnPieceException("The final square is occupied by own piece");
		}
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

	m_state = EGameState::MovingPiece;
	
	// Make Castle Inaccessible if Rook moved // 

	if (initialPosition.row == 0 || initialPosition.row == 7)   
	{
		if (initialPosition.col == 0)
		{
			m_Castle[(int)m_turn][0] = false;
		}
		else if (initialPosition.col == 7)
		{
			m_Castle[(int)m_turn][1] = false;
		}
	}

	// End of Make Castle Inaccessible if Rook moved //

	// Make Castle Inaccessible if King moved // 

	if (m_board[finalPosition.row][finalPosition.col]->GetType() == EType::King)
	{
		m_kingPositions[(int)m_turn] = finalPosition;
		m_Castle[(int)m_turn][0] = false;
		m_Castle[(int)m_turn][1] = false;
		if (initialPosition.col - finalPosition.col == 2)
		{
			m_board[finalPosition.row][finalPosition.col + 1] = m_board[finalPosition.row][0];
			m_board[finalPosition.row][0].reset();
			Notify(ENotification::MoveMade, Position(finalPosition.row, 0), Position(finalPosition.row, finalPosition.col + 1));
		}
		else if (initialPosition.col - finalPosition.col == -2)
		{
			m_board[finalPosition.row][finalPosition.col - 1] = m_board[finalPosition.row][7];
			m_board[finalPosition.row][7].reset();
			Notify(ENotification::MoveMade, Position(finalPosition.row, 7), Position(finalPosition.row, finalPosition.col - 1));
		}
	}  
	// End of Make Castle Inaccessible if King moved //
	else if (m_board[finalPosition.row][finalPosition.col]->GetType() == EType::Pawn)
	{
		if (m_board[finalPosition.row][finalPosition.col]->GetColor() == EColor::White && finalPosition.row == 0)
		{
			m_state = EGameState::UpgradePawn;
			//Notify(ENotification::PawnUpgrade);
			return;
		}
		if (m_board[finalPosition.row][finalPosition.col]->GetColor() == EColor::Black && finalPosition.row == 7)
		{
			m_state = EGameState::UpgradePawn;
			//Notify(ENotification::PawnUpgrade);
			return;
		}
	}
	
	// v  Save current configuration

	if (SaveCurrentConfig() >= 2)
	{
		m_state = EGameState::Draw;
	}

	// ^  End of save current config

	SwitchTurn();

	if (CanBeCaptured(m_board, m_kingPositions[(int)m_turn]) == true)
	{
		m_state = EGameState::CheckState;
		//Notify(ENotification::CheckState);
	}

	if (IsStaleMate())
	{
		m_state = EGameState::Draw;
		return;
	}

	if (IsGameOver())
	{
		m_state = m_turn == EColor::White ? EGameState::WonByBlackPlayer : EGameState::WonByWhitePlayer;
	}
}

int ChessGame::SaveCurrentConfig()
{
	// r h b q k p -> white pieces
	// R H B Q K P -> black pieces
	std::array<std::array<char, 8>, 8> currConfig;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (m_board[i][j])
			{
				currConfig[i][j] = m_board[i][j]->ToLetter();
			}
			else
			{
				currConfig[i][j] = ' ';
			}
		}
	}

	m_boardConfigurationsRepetitons[currConfig]++;
	return m_boardConfigurationsRepetitons[currConfig];
}

// Static Methods //

bool ChessGame::IsInMatrix(Position pos)
{
	return pos.row >= 0 && pos.row < 8 
		&& pos.col >= 0 && pos.col < 8;
}
