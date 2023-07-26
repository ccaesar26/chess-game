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

static char GetPieceLetter(PiecePtr p)
{
	// white pieces: p r h b q k
	// black pieces: P R H B Q K
	char l;
	switch (p->GetType())
	{
	case EType::Rook:
		l = 'r';
		break;
	case EType::Horse:
		l = 'h';
		break;
	case EType::King:
		l = 'k';
		break;
	case EType::Queen:
		l = 'q';
		break;
	case EType::Bishop:
		l = 'b';
		break;
	case EType::Pawn:
		l = 'p';
		break;
	default:
		break;
	}
	if (p->GetColor() == EColor::Black)
	{
		l = l - 'a' + 'A';
	}

	return l;
}

// Producer //

IChessGamePtr IChessGame::CreateBoard()
{
	return std::make_shared<ChessGame>();
}

// Constructor //

ChessGame::ChessGame()
{
	RestartChessGame();
}

ChessGame::ChessGame(const CharBoard& inputConfig, EColor turn) 
	: m_turn(turn)
	, m_state(EGameState::MovingPiece)
{
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			m_Castle[i][j] = true;

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

void ChessGame::RestartChessGame()
{
	m_turn = EColor::White;
	m_kingPositions = { Position(7 ,4), Position(0, 4) };
	m_state = EGameState::MovingPiece;

	m_whitePiecesCaptured.clear();
	m_blackPiecesCaptured.clear();
	m_boardConfigurationsRepetitons.clear();

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

	for (int i = 2; i <= 5; i++)
		for (int j = 0; j < 8; j++)
			m_board[i][j].reset();
}

void ChessGame::SetCastleValues(const std::array<std::array<bool, 2>, 2>& Castle)
{
	m_Castle = Castle;
}

// Virtual Implementations //

IPiecePtr ChessGame::GetIPiecePtr(int row, int col) const
{
	if (row < 0 || row >= 8)
	{
		throw InvalidBoardPositionException("Line out of range");
	}
	if (col >= 0 && col < 8)
	{
		return m_board[row][col];
	}
	throw InvalidBoardPositionException("Column out of range");
}

std::vector<std::pair<int, int>> ChessGame::GetMoves(int row, int col) const
{
	std::vector<std::pair<int, int>> possibleBoardPositions;
	PositionList possiblePositions = GetPossibleMoves(Position(row, col));
	for (int i = 0; i < possiblePositions.size(); i++)
	{
		possibleBoardPositions.push_back(std::make_pair(possiblePositions.at(i).row, possiblePositions.at(i).col));
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

	if (checkPieces.at(0)->GetType() == EType::King ||
		checkPieces.at(0)->GetType() == EType::Pawn ||
		checkPieces.at(0)->GetType() == EType::Horse)
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

void ChessGame::MakeMovement(int initialRow, int initialColumn, int finalRow, int finalColumn)
{
	MakeMove(Position(initialRow, initialColumn), Position(finalRow, finalColumn));

	Notify(ENotification::MoveMade, initialRow, initialColumn, finalRow, finalColumn);

	if (IsGameOver())
	{
		if (m_state == EGameState::Draw)
		{
			Notify(ENotification::GameOver);
			return;
		}
		if (m_turn == EColor::White)
		{
			m_state = EGameState::WonByBlackPlayer;
		}
		else
		{
			m_state = EGameState::WonByWhitePlayer;
		}
		Notify(ENotification::GameOver);
	}

	switch (m_state)
	{
	/*case EGameState::MovingPiece:
		break;*/
	case EGameState::Draw:
		Notify(ENotification::GameOver);
		break;
	case EGameState::WonByWhitePlayer:
		Notify(ENotification::GameOver);
		break;
	case EGameState::WonByBlackPlayer:
		Notify(ENotification::GameOver);
		break;
	case EGameState::UpgradePawn:
		Notify(ENotification::PawnUpgrade);
		break;
	case EGameState::CheckState:
		Notify(ENotification::CheckState);
		break;
	case EGameState::WaitingForDrawResponse:
		break;
	default:
		break;
	}
}

void ChessGame::UpgradePawn(std::string upgradeType)
{
	for (auto i = 0; i < upgradeType.size(); i++)
	{
		upgradeType[i] = tolower(upgradeType[i]);
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
			if (m_board[7][i] && m_board[7][i]->GetType() == EType::Pawn)
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
	else if(upgradeType == "knight")
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
		//Notify(ENotification::CheckState);
	}
}

void ChessGame::RequestDraw()
{
	m_state = EGameState::WaitingForDrawResponse;
	//Notify(ENotification::DrawProposal);
}

void ChessGame::AcceptDrawProposal()
{
	m_state = EGameState::Draw;
	//Notify(ENotification::GameOver);
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

// Observers //

void ChessGame::AddListener(IChessGameListenerPtr listener)
{
	m_listeners.push_back(listener);
}

void ChessGame::RemoveListener(IChessGameListenerPtr listener)
{
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
}

void ChessGame::Notify(ENotification notif, int ir /*= 0*/, int ic /*= 0*/, int fr /*= 0*/, int fc /*= 0*/)
{
	
	for (auto it = m_listeners.begin(); it != m_listeners.end(); it++)
	{
		if (auto sp = it->lock())
		{
			switch (notif)
			{
			case ENotification::MoveMade:
				sp->OnMoveMade(ir, ic, fr, fc);
				break;
			case ENotification::PawnUpgrade:
				sp->OnPawnUpgrade();
				break;
			case ENotification::GameOver:
				sp->OnGameOver();
				break;
			case ENotification::CheckState:
				sp->OnCheck();
				break;
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
		if (m_board[kingPosition.row][0] && m_board[kingPosition.row][0]->GetType() == EType::Rook
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
			throw OccupiedByEnemyPieceException("Your move is not possible");
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
		}
		else if (initialPosition.col - finalPosition.col == -2)
		{
			m_board[finalPosition.row][finalPosition.col - 1] = m_board[finalPosition.row][7];
			m_board[finalPosition.row][7].reset();
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

	SaveCurrentConfig();

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
		//Notify(ENotification::GameOver);
	}
}

void ChessGame::SaveCurrentConfig()
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
				currConfig[i][j] = GetPieceLetter(m_board[i][j]);
			}
			else
			{
				currConfig[i][j] = ' ';
			}
		}
	}
	m_boardConfigurationsRepetitons[currConfig]++;
	if (m_boardConfigurationsRepetitons[currConfig] >= 3)
	{
		m_state = EGameState::Draw;
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
