#pragma once

#include "IChessGame.h"
#include "Piece.h"

#include <array>

using ArrayBoard = std::array<std::array<PiecePtr, 8>, 8>;
using CharBoard = std::array<std::array<char, 8>, 8>;

enum class EGameState
{
	MovingPiece,
	Draw,
	WonByWhitePlayer,
	WonByBlackPlayer,
	UpgradePawn,
	CheckState,
	WaitingForDrawResponse
};

class ChessGame : public IChessGame
{
public:

	// Constructors //

	ChessGame();
	ChessGame(const CharBoard& inputConfig, EColor turn = EColor::White);

	// Virtual Implementations //

	IPiecePtr GetIPiece(char col, int ln) const override;
	std::vector<BoardPosition> GetMoves(char col, char row) const override;
	IPieceList GetCapturedPieces(EColor color) const override;
	EColor GetCurrentPlayer() const override;

	bool IsGameOver() const override;

	void MakeMovement(char initialColumn, char initialRow, char finalColumn, char finalRow) override;

	void UpgradePawn(std::string upgradeType) override;

	void RequestDraw() override;

	void AcceptDrawProposal() override;

	void DeclineDrawProposal() override;

	bool IsDraw() const override;

	bool IsWonByWhitePlayer() const override;

	bool IsWonByBlackPlayer() const override;

	bool IsWaitingForUpgrade() const override;

	bool IsWaitingForDrawResponse() const override;

	bool IsCheckState() const override;

	Position ConvertToMemoryPosition(char col, char row) const override;
	BoardPosition ConvertToBoardPosition(Position pos) const override;

	// Game's Logic //

	PiecePtr GetPiece(Position pos, const ArrayBoard& board) const;

	void AddCastle(Position kingPosition, PositionList& kingPossibleMoves) const;

	PositionList GetPossibleMoves(Position currentPos) const;
	
private:

	PieceList GetCheckPieces(Position& checkPos) const;

	bool CheckPieceCanBeCaptured(const Position& checkPiecePos) const;

	Position GetMovingDirections(const Position& checkPiecePos) const;

	PositionList GetToBlockPositions(const Position& checkPiecePos) const;
	
	bool KingsWayCanBeBlocked(const PositionList& toBlockPositions) const;

	void SwitchTurn();

	bool CanBeCaptured(const ArrayBoard& board, Position toCapturePos) const;

	void MakeMove(Position initialPosition, Position finalPosition);

	// Static Methods //

	static bool IsInMatrix(Position piecePosition);

private:

	// Private Members //

	ArrayBoard m_board;
	EColor m_turn;

	PositionList m_kingPositions;

	IPieceList m_whitePiecesCaptured;
	IPieceList m_blackPiecesCaptured;

	EGameState m_state;

	std::array<std::array<bool, 2>, 2> m_Castle;    
	// Row 1 is for White and Row 2 is for Black ! Column 1 is for left castle and Column 2 is for right castle //
};
