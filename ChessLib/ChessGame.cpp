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
	: m_turn(ETurn::WhitePlayer)
	, m_blackKingPosition(0, 4)
	, m_whiteKingPosition(7,4)
	, m_checkStateWhiteKing(false)
	, m_checkStateBlackKing(false)
{
	// Pawn Declaration 
	for (int j = 0; j < 8; j++)
	{
		m_board[1][j] = std::make_shared<Pawn>(EColor::Black, Position(1, j));
		m_blackPiecesAlive.insert(m_board[1][j]);

		m_board[6][j] = std::make_shared<Pawn>(EColor::White, Position(6, j));
		m_whitePiecesAlive.insert(m_board[6][j]);
	}

	// Rook Declaration
	m_board[0][0] = std::make_shared<Rook>(EColor::Black, Position(0, 0));
	m_blackPiecesAlive.insert(m_board[0][0]);

	m_board[0][7] = std::make_shared<Rook>(EColor::Black, Position(0, 7));
	m_blackPiecesAlive.insert(m_board[0][7]);

	m_board[7][0] = std::make_shared<Rook>(EColor::White, Position(7, 0));
	m_whitePiecesAlive.insert(m_board[7][0]);

	m_board[7][7] = std::make_shared<Rook>(EColor::White, Position(7, 7));
	m_whitePiecesAlive.insert(m_board[7][7]);

	// Horse Declaration
	m_board[0][1] = std::make_shared<Horse>(EColor::Black, Position(0, 1));
	m_blackPiecesAlive.insert(m_board[0][1]);

	m_board[0][6] = std::make_shared<Horse>(EColor::Black, Position(0, 6));
	m_blackPiecesAlive.insert(m_board[0][6]);

	m_board[7][1] = std::make_shared<Horse>(EColor::White, Position(7, 1));
	m_whitePiecesAlive.insert(m_board[7][1]);

	m_board[7][6] = std::make_shared<Horse>(EColor::White, Position(7, 6));
	m_whitePiecesAlive.insert(m_board[7][6]);

	// Bishop Declaration
	m_board[0][2] = std::make_shared<Bishop>(EColor::Black, Position(0, 2));
	m_blackPiecesAlive.insert(m_board[0][2]);

	m_board[0][5] = std::make_shared<Bishop>(EColor::Black, Position(0, 5));
	m_blackPiecesAlive.insert(m_board[0][5]);

	m_board[7][2] = std::make_shared<Bishop>(EColor::White, Position(7, 2));
	m_whitePiecesAlive.insert(m_board[7][2]);

	m_board[7][5] = std::make_shared<Bishop>(EColor::White, Position(7, 5));
	m_whitePiecesAlive.insert(m_board[7][5]);

	// Queen Declaration
	m_board[0][3] = std::make_shared<Queen>(EColor::Black, Position(0, 3));
	m_blackPiecesAlive.insert(m_board[0][3]);

	m_board[7][3] = std::make_shared<Queen>(EColor::White, Position(7, 3));
	m_whitePiecesAlive.insert(m_board[7][3]);

	// King Declaration
	m_board[0][4] = std::make_shared<King>(EColor::Black, Position(0, 4));
	m_blackPiecesAlive.insert(m_board[0][4]);
	

	m_board[7][4] = std::make_shared<King>(EColor::White, Position(7, 4));
	m_whitePiecesAlive.insert(m_board[7][4]);
}

ChessGame::ChessGame(std::array<std::array<char, 8>, 8> inputConfig,
	bool checkStateBlackKing, bool checkStateWhiteKing, ETurn turn)
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
			// empty tile: * or _ or anything else
			switch (inputConfig[i][j])
			{
			case 'p':
				m_board[i][j] = std::make_shared<Pawn>(EColor::White, Position(i, j));
				m_whitePiecesAlive.insert(m_board[i][j]);
				break;
			case 'P':
				m_board[i][j] = std::make_shared<Pawn>(EColor::Black, Position(i, j));
				m_blackPiecesAlive.insert(m_board[i][j]);
				break;
			case 'r':
				m_board[i][j] = std::make_shared<Rook>(EColor::White, Position(i, j));
				m_whitePiecesAlive.insert(m_board[i][j]);
				break;
			case 'R':
				m_board[i][j] = std::make_shared<Rook>(EColor::Black, Position(i, j));
				m_blackPiecesAlive.insert(m_board[i][j]);
				break;
			case 'h':
				m_board[i][j] = std::make_shared<Horse>(EColor::White, Position(i, j));
				m_whitePiecesAlive.insert(m_board[i][j]);
				break;
			case 'H':
				m_board[i][j] = std::make_shared<Horse>(EColor::Black, Position(i, j));
				m_blackPiecesAlive.insert(m_board[i][j]);
				break;
			case 'b':
				m_board[i][j] = std::make_shared<Bishop>(EColor::White, Position(i, j));
				m_whitePiecesAlive.insert(m_board[i][j]);
				break;
			case 'B':
				m_board[i][j] = std::make_shared<Bishop>(EColor::Black, Position(i, j));
				m_blackPiecesAlive.insert(m_board[i][j]);
				break;
			case 'q':
				m_board[i][j] = std::make_shared<Queen>(EColor::White, Position(i, j));
				m_whitePiecesAlive.insert(m_board[i][j]);
				break;
			case 'Q':
				m_board[i][j] = std::make_shared<Queen>(EColor::Black, Position(i, j));
				m_blackPiecesAlive.insert(m_board[i][j]);
				break;
			case 'k':
				m_board[i][j] = std::make_shared<King>(EColor::White, Position(i, j));
				m_whitePiecesAlive.insert(m_board[i][j]);
				m_whiteKingPosition = Position(i, j);
				break;
			case 'K':
				m_board[i][j] = std::make_shared<King>(EColor::Black, Position(i, j));
				m_blackPiecesAlive.insert(m_board[i][j]);
				m_blackKingPosition = Position(i, j);
				break;
			default:
				break;
			}
		}
	}
}

// Public Methods //

void ChessGame::PlayTurn(BoardPosition initialPos, BoardPosition finalPos)
{
	//Position init;
	// // To do

	//PiecePtr p = m_board[0][0];
	//PositionPieceSet set = p->GetMovesPossible(init, std::bind(&ChessGame::GetPiece, this, std::placeholders::_1));
}

Board ChessGame::GetBoard() const
{
	return m_board;
}

PieceSet ChessGame::GetWhitePiecesAlive()
{
	return m_whitePiecesAlive;
}

PieceSet ChessGame::GetBlackPiecesAlive()
{
	return m_blackPiecesAlive;
}

PieceSet ChessGame::GetWhitePiecesCaptured()
{
	return m_whitePiecesCaptured;
}

PieceSet ChessGame::GetBlackPiecesCaptured()
{
	return m_blackPiecesCaptured;
}

bool ChessGame::IsGameOver() const
{
	// To do
	return false;
}


// Private Methods //

void ChessGame::MakeMove(Position initialPosition, Position finalPosition)
{
	// To do
}

PiecePtr ChessGame::GetPiece(Position pos) const
{
	return m_board[pos.row][pos.col];
}

bool ChessGame::IsKingInCheckState(EColor color)
{
	/*Position kingPosition;
	if (color == EColor::White)
	{
		kingPosition = m_whiteKingPosition;
		for (auto iterator : m_blackPiecesAlive)
		{
			if (iterator->PieceMoveIsPossible(iterator->GetPosition(), kingPosition, m_board) == true)
			{
				m_checkStateWhiteKing = true;
				return true;
			}
		}
	}
	else
	{
		kingPosition = m_blackKingPosition;
		for (auto iterator : m_whitePiecesAlive)
		{
			if (iterator->PieceMoveIsPossible(iterator->GetPosition(), kingPosition, m_board) == true)
			{
				m_checkStateBlackKing = true;
				return true;
			}
		}
	}*/
	return false;
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


//bool ChessGame::IsMovePossible(Position initialPosition, Position finalPosition)
//{
//	if (initialPosition == finalPosition)
//	{
//		return false;
//	}
//
//	if (!IsInMatrix(finalPosition))
//	{
//		return false;
//	}
//
//	PiecePtr currentPiece = m_board[initialPosition.row][initialPosition.col];
//	PiecePtr toCapturePiece = m_board[finalPosition.row][finalPosition.col];
//	if (toCapturePiece)
//	{
//		if (currentPiece->GetColor() == toCapturePiece->GetColor())
//		{
//			return false;
//		}
//	}
//
//	if (currentPiece->PieceMoveIsPossible(initialPosition, finalPosition, m_board) == false)
//	{
//		return false;
//	}
//	
//	if (IsKingInCheckState(currentPiece->GetColor()))
//	{
//		return false;
//	}
//	return true;
//}