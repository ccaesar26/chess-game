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

	IPiecePtr GetIPiecePtr(int row, int col) const override;
	std::vector<std::pair<int, int>> GetMoves(int row, int col) const override;
	IPieceList GetCapturedPieces(EColor color) const override;
	EColor GetCurrentPlayer() const override;

	bool IsGameOver() const override;

	void MakeMovement(int initialRow, int initialColumn, int finalRow, int finalColumn) override;

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
};
