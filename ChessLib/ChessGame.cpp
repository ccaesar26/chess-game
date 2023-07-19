#include "ChessGame.h"
#include "Piece.h"

#include <ctype.h>

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
	// Pawn Declaration 
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

static EColor GetColor(char c)
{
	return islower(c) ? EColor::White : EColor::Black;
}

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

// Public Methods //

//void ChessGame::PlayTurn(Position initialPos, Position finalPos)
//{
//	Position init;
//	 // To do
//	
//	PiecePtr p = m_board[0][0];
//	PositionPieceSet set = p->GetMovesPossible(init, std::bind(&ChessGame::GetPiece, this, std::placeholders::_1));
//}

bool ChessGame::IsGameOver() const
{
	//if (!m_checkState)
	//{
	//	return false;
	//}

	//PiecePtr checkPiece1;  // Memorize the Pieces that puts my king in check //
	//Position checkPiece1Pos;

	//PiecePtr checkPiece2;  // Memorize the Pieces that puts my king in check //
	//
	//for (int i = 0; i < 8; i++)
	//{
	//	for (int j = 0; j < 8; j++)
	//	{
	//		if (m_board[i][j])
	//		{
	//			if (m_board[i][j]->GetColor() != m_turn)
	//			{
	//				Position piecePosition(i, j);
	//				PositionList enemyPiecePositions = m_board[i][j]->GetPattern(piecePosition, std::bind(&ChessGame::GetPiece, this, std::placeholders::_1));
	//				for (auto pos : enemyPiecePositions)
	//				{
	//					if (pos == m_kingPositions[(int)m_turn])
	//					{
	//						if (!checkPiece1)
	//						{
	//							checkPiece1 = m_board[i][j];
	//							checkPiece1Pos.row = i;
	//							checkPiece1Pos.col = j;
	//						}
	//						else if (!checkPiece2) 
	//							checkPiece2 == m_board[i][j];
	//						else 
	//							break;
	//					}
	//				}
	//			}
	//		}
	//	}
	//}

	//// Verify the 3 cases // 

	//// Case 1 // 

	//PositionList kingPossibleMoves = GetPossibleMoves(m_kingPositions[(int)m_turn]);

	//if (kingPossibleMoves.empty() == false)
	//	return false;
	//else
	//{
	//	if (checkPiece1 && checkPiece2) 
	//		return true;
	//}

	//// Case 2 //

	//for (int i = 0; i < 8; i++)
	//{
	//	for (int j = 0; j < 8; j++)
	//	{
	//		if (m_board[i][j] && m_board[i][j]->GetColor() == m_turn)
	//		{
	//			Position piecePosition(i, j);
	//			PositionList ownPiecePositions = GetPossibleMoves(piecePosition);
	//			for (auto pos : ownPiecePositions)
	//			{
	//				if (pos == checkPiece1Pos) return false;
	//			}
	//		}
	//	}
	//}

	//// Case 3 // 

	//Position kingPosition = m_kingPositions[(int)m_turn];

	//PositionList toBlockPositions;

	//int movingRow;
	//int movingCol;

	//if (checkPiece1->GetType() == EType::King || checkPiece1->GetType() == EType::Pawn || checkPiece1->GetType() == EType::Horse) 
	//	return true;

	//if (kingPosition.row < checkPiece1Pos.row) 
	//	movingRow = -1;
	//else if (kingPosition.row > checkPiece1Pos.row) 
	//	movingRow = 1;
	//else 
	//	movingRow = 0;

	//if (kingPosition.col < checkPiece1Pos.col) 
	//	movingCol = -1;
	//else if (kingPosition.col > checkPiece1Pos.col) 
	//	movingCol = 1;
	//else 
	//	movingCol = 0;

	//int i_row = checkPiece1Pos.row + movingRow;
	//int i_col = checkPiece1Pos.col + movingCol;

	//while (i_row != kingPosition.row && i_col != kingPosition.col)
	//{
	//	toBlockPositions.push_back(Position(i_row, i_col));
	//	i_row += movingRow;
	//	i_col += movingCol;
	//}

	//if (toBlockPositions.empty() == true) 
	//	return true;
 //
	//for (int i = 0; i < 8; i++)
	//{
	//	for (int j = 0; j < 8; j++)
	//	{
	//		if (m_board[i][j] && m_board[i][j]->GetColor() == m_turn)
	//		{
	//			PositionList possibleMoves = GetPossibleMoves(Position(i, j));
	//			for (auto pos : toBlockPositions)
	//			{
	//				if (std::find(possibleMoves.begin(), possibleMoves.end(), pos) != possibleMoves.end()) 
	//					return false;
	//			}
	//		}
	//	}
	//}

	return true;
}

// Private Methods //

PiecePtr ChessGame::GetPiece(Position pos, const ArrayBoard& board) const
{
	return board[pos.row][pos.col];
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

IPieceList ChessGame::GetCapturedPieces(EColor color) const
{
	return color == EColor::White ? m_whitePiecesCaptured : m_blackPiecesCaptured;
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

void ChessGame::MakeMovement(char initialColumn, int initialRow, char finalColumn, int finalRow)
{
	MakeMove(ConvertToPosition(initialColumn, initialRow), ConvertToPosition(finalColumn, finalRow));
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

	// Old code //

	/*for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (m_board[i][j] && m_board[i][j]->GetColor() != m_turn)
			{
				Position piecePosition(i, j);
				PositionList enemyPiecePositions = m_board[i][j]->GetPattern(piecePosition, std::bind(&ChessGame::GetPiece, this, std::placeholders::_1));
				for (auto pos : enemyPiecePositions)
				{
					if (pos == m_kingPositions[(int)m_turn])
					{
						return true;
					}
				}
			}
		}
	}*/
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

//PositionList ChessGame::GetPossibleMoves(Position currentPos) const;

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
