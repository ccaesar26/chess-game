#include "ChessGame.h"
#include "Bishop.h"
#include "Horse.h"
#include "King.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"

IChessGamePtr IChessGame::CreateBoard()
{
	return std::make_shared<ChessGame>();
}

// Constructor //

ChessGame::ChessGame()
	: m_turn(EColor::White)
	, m_blackKingPosition(0, 4)
	, m_whiteKingPosition(7,4)
	, m_checkStateWhiteKing(false)
	, m_checkStateBlackKing(false)
{
	// Pawn Declaration 
	for (int j = 0; j < 8; j++)
	{
		m_board[1][j] = std::make_shared<Pawn>(EColor::Black);
		m_board[6][j] = std::make_shared<Pawn>(EColor::White);
	}

	// Rook Declaration
	m_board[0][0] = std::make_shared<Rook>(EColor::Black);
	m_board[0][7] = std::make_shared<Rook>(EColor::Black);
	m_board[7][0] = std::make_shared<Rook>(EColor::White);
	m_board[7][7] = std::make_shared<Rook>(EColor::White);

	// Horse Declaration
	m_board[0][1] = std::make_shared<Horse>(EColor::Black);
	m_board[0][6] = std::make_shared<Horse>(EColor::Black);
	m_board[7][1] = std::make_shared<Horse>(EColor::White);
	m_board[7][6] = std::make_shared<Horse>(EColor::White);

	// Bishop Declaration
	m_board[0][2] = std::make_shared<Bishop>(EColor::Black);
	m_board[0][5] = std::make_shared<Bishop>(EColor::Black);
	m_board[7][2] = std::make_shared<Bishop>(EColor::White);
	m_board[7][5] = std::make_shared<Bishop>(EColor::White);

	// Queen Declaration
	m_board[0][3] = std::make_shared<Queen>(EColor::Black);
	m_board[7][3] = std::make_shared<Queen>(EColor::White);

	// King Declaration
	m_board[0][4] = std::make_shared<King>(EColor::Black);
	m_board[7][4] = std::make_shared<King>(EColor::White);
}

ChessGame::ChessGame(std::array<std::array<char, 8>, 8> inputConfig,
	bool checkStateBlackKing, bool checkStateWhiteKing, EColor turn)
{
	m_checkStateWhiteKing = checkStateWhiteKing;
	m_checkStateBlackKing = checkStateBlackKing;
	m_turn = turn;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j< 8; j++)
		{
			// white pieces: p r h b q k
			// black pieces: P R H B Q K
			// empty tile: anything else
			switch (inputConfig[i][j])
			{
			case 'p':
				m_board[i][j] = std::make_shared<Pawn>(EColor::White);
				break;
			case 'P':
				m_board[i][j] = std::make_shared<Pawn>(EColor::Black);
				break;
			case 'r':
				m_board[i][j] = std::make_shared<Rook>(EColor::White);
				break;
			case 'R':
				m_board[i][j] = std::make_shared<Rook>(EColor::Black);
				break;
			case 'h':
				m_board[i][j] = std::make_shared<Horse>(EColor::White);
				break;
			case 'H':
				m_board[i][j] = std::make_shared<Horse>(EColor::Black);
				break;
			case 'b':
				m_board[i][j] = std::make_shared<Bishop>(EColor::White);
				break;
			case 'B':
				m_board[i][j] = std::make_shared<Bishop>(EColor::Black);
				break;
			case 'q':
				m_board[i][j] = std::make_shared<Queen>(EColor::White);
				break;
			case 'Q':
				m_board[i][j] = std::make_shared<Queen>(EColor::Black);
				break;
			case 'k':
				m_board[i][j] = std::make_shared<King>(EColor::White);
				m_whiteKingPosition = Position(i, j);
				break;
			case 'K':
				m_board[i][j] = std::make_shared<King>(EColor::Black);
				m_blackKingPosition = Position(i, j);
				break;
			default:
				break;
			}
		}
	}
}

// Public Methods //

//void ChessGame::PlayTurn(Position initialPos, Position finalPos)
//{
//	Position init;
//	 // To do
//	
//	PiecePtr p = m_board[0][0];
//	PositionPieceSet set = p->GetMovesPossible(init, std::bind(&ChessGame::GetPiece, this, std::placeholders::_1));
//}

IPieceList ChessGame::GetWhitePiecesCaptured()
{
	return m_whitePiecesCaptured;
}

IPieceList ChessGame::GetBlackPiecesCaptured()
{
	return m_blackPiecesCaptured;
}

bool ChessGame::IsGameOver()
{
	if (m_turn == EColor::White)
	{
		if (m_checkStateWhiteKing == false) return false;
	}
	else
	{
		if (m_checkStateBlackKing == false) return false;
	}

	PiecePtr checkPiece1;  // Memorize the Pieces that puts my king in check //
	Position checkPiece1Pos;

	PiecePtr checkPiece2;  // Memorize the Pieces that puts my king in check //
	
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (m_board[i][j])
			{
				if (m_board[i][j]->GetColor() != m_turn)
				{
					Position piecePosition(i, j);
					PositionList enemyPiecePositions = m_board[i][j]->GetPattern(piecePosition, std::bind(&ChessGame::GetPiece, this, std::placeholders::_1));
					for (auto pos : enemyPiecePositions)
					{
						if (m_turn == EColor::White)
						{
							if (pos == m_whiteKingPosition)
							{
								if (!checkPiece1)
								{
									checkPiece1 = m_board[i][j];
									checkPiece1Pos.row = i;
									checkPiece1Pos.col = j;
								}
								else if (!checkPiece2) checkPiece2 == m_board[i][j];
								else break;
							}
						}
						else
						{
							if (pos == m_blackKingPosition)
							{
								if (!checkPiece1)
								{
									checkPiece1 = m_board[i][j];

								}
								else if (!checkPiece2) checkPiece2 == m_board[i][j];
								else break;
							}
						}
					}
				}
			}
		}
	}

	// Verify the 3 cases // 

	// Case 1 // 

	PositionList kingPossibleMoves;
	if (m_turn == EColor::White) kingPossibleMoves = GetPossibleMoves(m_whiteKingPosition);
	else kingPossibleMoves = GetPossibleMoves(m_blackKingPosition);

	if (kingPossibleMoves.empty() == false) return false;
	else
	{
		if (checkPiece1 && checkPiece2) return true;
	}

	// Case 2 //

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (m_board[i][j])
			{
				if (m_board[i][j]->GetColor() == m_turn)
				{
					Position piecePosition(i, j);
					PositionList ownPiecePositions = GetPossibleMoves(piecePosition);
					for (auto pos : ownPiecePositions)
					{
						if (pos == checkPiece1Pos) return false;
					}
				}
			}
		}
	}

	// Case 3 // 

	Position kingPosition;
	if (m_turn == EColor::White) kingPosition = m_whiteKingPosition;
	else kingPosition = m_blackKingPosition;

	PositionList toBlockPositions;

	int movingRow;
	int movingCol;

	if (checkPiece1->GetType() == EType::King || checkPiece1->GetType() == EType::Pawn || checkPiece1->GetType() == EType::Horse) return true;

	if (kingPosition.row < checkPiece1Pos.row) movingRow = -1;
	else if (kingPosition.row > checkPiece1Pos.row) movingRow = 1;
	else movingRow = 0;

	if (kingPosition.col < checkPiece1Pos.col) movingCol = -1;
	else if (kingPosition.col > checkPiece1Pos.col) movingCol = 1;
	else movingCol = 0;

	int i_row = checkPiece1Pos.row + movingRow;
	int i_col = checkPiece1Pos.col + movingCol;

	while (i_row != kingPosition.row && i_col != kingPosition.col)
	{
		toBlockPositions.push_back(Position(i_row, i_col));
		i_row += movingRow;
		i_col += movingCol;
	}

	if (toBlockPositions.empty() == true) return true;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (m_board[i][j])
			{
				if (m_board[i][j]->GetColor() == m_turn)
				{
					PositionList possibleMoves;
					possibleMoves = GetPossibleMoves(Position(i, j));
					for (auto pos : toBlockPositions)
					{
						if (std::find(possibleMoves.begin(), possibleMoves.end(), pos) != possibleMoves.end()) return false;
					}
				}
			}
		}
	}

	return true;
}

// Private Methods //

PiecePtr ChessGame::GetPiece(Position pos) const
{
	return m_board[pos.row][pos.col];
}

IBoardPtr ChessGame::GetBoard() const
{
	return std::make_shared<Board>(m_board);
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

EColor ChessGame::GetCurrentPlayer() const
{
	return m_turn;
}

void ChessGame::MakeMovement(char initialColumn, int initialRow, char finalColumn, int finalRow)
{
	MakeMove(ConvertToPosition(initialColumn, initialRow), ConvertToPosition(finalColumn, finalRow));
}

bool ChessGame::IsKingInCheckState()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (m_board[i][j])
			{
				if (m_board[i][j]->GetColor() != m_turn)
				{
					Position piecePosition(i, j);
					PositionList enemyPiecePositions = m_board[i][j]->GetPattern(piecePosition, std::bind(&ChessGame::GetPiece, this, std::placeholders::_1));
					for (auto pos : enemyPiecePositions)
					{
						if (m_turn == EColor::White)
						{
							if (pos == m_whiteKingPosition) return true;
						}
						else 
						{
							if (pos == m_blackKingPosition) return true;
						}
					}
				}
			}
		}
	}
	return false;
}

Position ChessGame::ConvertToPosition(char col, int ln)
{
	if (col >= 'a')
	{
		return Position(8 - ln, col - 'a');
	}
	return Position(8 - ln, col - 'A');
}

PositionList ChessGame::GetPossibleMoves(Position currentPos)
{
	PositionList possibleMoves;
	PiecePtr currentPiece = m_board[currentPos.row][currentPos.col];

	if (currentPiece)
	{
		if (currentPiece->GetColor() == m_turn)
		{
			possibleMoves = currentPiece->GetPattern(currentPos, std::bind(&ChessGame::GetPiece, this, std::placeholders::_1));
		}
	}

	for (int i = 0; i < possibleMoves.size(); i++)
	{
		Position pos = possibleMoves[i];  // The pos variable is for iterating the possible moves //

		PiecePtr currentPieceCopy = m_board[currentPos.row][currentPos.col];
		PiecePtr finalPieceCopy = m_board[pos.row][pos.col];

		m_board[pos.row][pos.col] = m_board[currentPos.row][currentPos.col];
		m_board[currentPos.row][currentPos.col].reset();

		if (IsKingInCheckState() == true)
		{
			possibleMoves.erase(std::find(possibleMoves.begin(), possibleMoves.end(), pos));
			i--;
		}
		
		m_board[currentPos.row][currentPos.col] = currentPieceCopy;
		m_board[pos.row][pos.col] = finalPieceCopy;

	}
	return possibleMoves;
}

void ChessGame::MakeMove(Position initialPosition, Position finalPosition)
{
	PositionList possibleMoves = GetPossibleMoves(initialPosition);
	if (std::find(possibleMoves.begin(), possibleMoves.end(), finalPosition) == possibleMoves.end()) throw "Your move is not possible !";

	if (m_board[finalPosition.row][finalPosition.col])
	{
		if (m_turn == EColor::White) m_blackPiecesCaptured.push_back(m_board[finalPosition.row][finalPosition.col]);
		else m_whitePiecesCaptured.push_back(m_board[finalPosition.row][finalPosition.col]);
	}

	m_board[finalPosition.row][finalPosition.col] = m_board[initialPosition.row][initialPosition.col];
	m_board[initialPosition.row][initialPosition.col].reset();

	if (m_board[finalPosition.row][finalPosition.col]->GetType() == EType::King)
	{
		if (m_turn == EColor::White) m_whiteKingPosition = finalPosition;
		else m_blackKingPosition = finalPosition;
	}

	if (m_turn == EColor::White) m_turn = EColor::Black;
	else m_turn = EColor::White;

	if (IsKingInCheckState() == true)  
	{
		if (m_turn == EColor::White) m_checkStateWhiteKing = true;
		else m_checkStateBlackKing = true;
	}
}

IPiecePtr ChessGame::GetIPiece(char col, int ln) const
{
	if (col >= 'a')
	{
		return m_board[8 - ln][col - 'a'];
	}
	return m_board[8 - ln][col - 'A'];
}

bool ChessGame::IsInMatrix(Position piecePosition)
{
	if (piecePosition.row < 0 || piecePosition.row > 7 || 
		piecePosition.col < 0 || piecePosition.col > 7)
	{
		return false;
	}
	return true;
}
