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

	// Virtual Implementations //

	IPiecePtr GetIPiece(char col, int ln) const override;
	std::vector<BoardPosition> GetMoves(char col, int row) const override;
	IPieceList GetCapturedPieces(EColor color) const override;
	EColor GetCurrentPlayer() const override;

	bool IsGameOver() const override;

	void MakeMovement(char initialColumn, int initialRow, char finalColumn, int finalRow) override;

	// Game's Logic //

	PiecePtr GetPiece(Position pos, const ArrayBoard& board) const;
	
private:

	PieceList GetCheckPieces(Position& checkPos) const;

	bool CheckPieceCanBeCaptured(const Position& checkPiecePos) const;

	Position GetMovingDirections(const Position& checkPiecePos) const;

	PositionList GetToBlockPositions(const Position& checkPiecePos) const;
	
	bool KingsWayCanBeBlocked(const PositionList& toBlockPositions) const;

	void SwitchTurn();

	bool CanBeCaptured(const ArrayBoard& board, Position toCapturePos) const;

	PositionList GetPossibleMoves(Position currentPos) const;

	void MakeMove(Position initialPosition, Position finalPosition);

	// Static Methods //

	static bool IsInMatrix(Position piecePosition);

	static Position ConvertToPosition(char col, int ln);
	static BoardPosition ConvertToBoardPosition(Position pos);

private:

	// Private Members //

	ArrayBoard m_board;
	EColor m_turn;

	PositionList m_kingPositions;
	bool m_checkState;

	IPieceList m_whitePiecesCaptured;
	IPieceList m_blackPiecesCaptured;
};
