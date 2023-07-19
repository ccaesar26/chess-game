#pragma once

#include "IChessGame.h"
#include "Piece.h"

#include <array>

using ArrayBoard = std::array<std::array<PiecePtr, 8>, 8>;
using CharBoard = std::array<std::array<char, 8>, 8>;

class ChessGame : public IChessGame
{

public:

	// Constructors //
	ChessGame();
	ChessGame(const CharBoard& inputConfig, EColor turn = EColor::White);

	

	bool IsGameOver() const override;

	EColor GetCurrentPlayer() const override;

	IPieceList GetCapturedPieces(EColor color) const override;

	std::vector<BoardPosition> GetMoves(char col, int row) const override;

	IPiecePtr GetIPiece(char col, int ln) const;

	PiecePtr GetPiece(Position pos, const ArrayBoard& board) const;
	

//private:

	bool IsInMatrix(Position piecePosition);

	bool CanBeCaptured(const ArrayBoard& board, Position toCapturePos) const;

	static Position ConvertToPosition(char col, int ln);

	static BoardPosition ConvertToBoardPosition(Position pos);

	void MakeMove(Position initialPosition, Position finalPosition);

	PositionList GetPossibleMoves(Position currentPos) const;

	void SwitchTurn();

	void MakeMovement(char initialColumn, int initialRow, char finalColumn, int finalRow) override;
private:

	ArrayBoard m_board;
	EColor m_turn;

	PositionList m_kingPositions;
	bool m_checkState;

	IPieceList m_whitePiecesCaptured;
	IPieceList m_blackPiecesCaptured;
};
