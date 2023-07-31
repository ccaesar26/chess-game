#pragma once

#include "IChessGame.h"
#include "Piece.h"

#include <array>
#include <unordered_map>
#include <string>

using ArrayBoard = std::array<std::array<PiecePtr, 8>, 8>;
using CharBoard = std::array<std::array<char, 8>, 8>;
using CastleValues = std::array<std::array<bool, 2>, 2>;
using BoardPosition = std::pair<char, char>;

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

enum class ENotification
{
	MoveMade,
	PawnUpgrade,
	GameOver,
	DrawProposal,
	Check,
	Reset
};

struct HashFunctor {
	std::size_t operator()(const std::array<std::array<char, 8>, 8>& data) const
	{
		std::size_t seed = 0;
		for (const auto& row : data) 
		{
			for (char element : row) 
			{
				// Combine the hash of each element in the data structure
				seed ^= std::hash<char>{}(element)+0x9e3779b9 + (seed << 6) + (seed >> 2);
			}
		}
		return seed;
	}
};

class ChessGame : public IChessGame
{
public:

	// Constructors //

	ChessGame();
	ChessGame(const CharBoard& inputConfig, EColor turn = EColor::White);

	void ResetGame() override;

	// Setter for Castle Matrix // 

	void SetCastleValues(const CastleValues& Castle);

	// Virtual Implementations //

	IPiecePtr GetIPiecePtr(Position pos) const override;
	PositionList GetPossibleMoves(Position currentPos) const override;

	IPieceList GetCapturedPieces(EColor color) const override;
	EColor GetCurrentPlayer() const override;
	MoveList GetMoveHistory() const override;

	bool CheckStaleMate() const;
	bool CheckCheckMate() const ;
	bool CheckThreeFoldRepetition();

	void MakeMove(Position initialpOS, Position finalPos) override;

	void UpgradePawn(EType upgradeType) override;

	void RequestDraw() override;
	void AcceptDrawProposal() override;
	void DeclineDrawProposal() override;

	bool IsDraw() const override;
	bool IsGameOver() const override;
	bool IsCheckState() const override;

	bool IsWonByWhitePlayer() const override;
	bool IsWonByBlackPlayer() const override;

	bool IsWaitingForUpgrade() const override;
	bool IsWaitingForDrawResponse() const override;

	// Observable //

	void AddListener(IChessGameListenerPtr listener);
	void RemoveListener(IChessGameListener* listener);
	void Notify(ENotification notif, Position init, Position fin); // different implementations
	void Notify(ENotification notif, Position pos);
	void Notify(ENotification notif); // different implementations

	// Game's Logic //

	PiecePtr GetPiece(Position pos, const ArrayBoard& board) const;

	void AddCastle(Position kingPosition, PositionList& kingPossibleMoves) const;

private:
	void InitializeChessGame();
	void ResetBoard();

	PieceList GetCheckPieces(Position& checkPos) const;

	bool CheckPieceCanBeCaptured(const Position& checkPiecePos) const;

	Position GetMovingDirections(const Position& checkPiecePos) const;

	PositionList GetToBlockPositions(const Position& checkPiecePos) const;
	
	bool KingsWayCanBeBlocked(const PositionList& toBlockPositions) const;

	void SwitchTurn();

	bool CanBeCaptured(const ArrayBoard& board, Position toCapturePos) const;

	Position GetPiecePositionWithSameTypeThatCanMoveToFinalPosition(Position initialPos, Position finalPos, EType currentPieceType);

	// Static Methods //

	static bool IsInMatrix(Position piecePosition);

	static BoardPosition ConvertToBoardPosition(Position pos);

private:

	// Private Members //

	ArrayBoard m_board;
	EColor m_turn;

	PositionList m_kingPositions;

	IPieceList m_whitePiecesCaptured;
	IPieceList m_blackPiecesCaptured;

	EGameState m_state;

	// Row 1 is for White and Row 2 is for Black ! Column 1 is for left castle and Column 2 is for right castle
	CastleValues m_Castle;    

	std::unordered_map<std::array<std::array<char, 8>, 8>, int, HashFunctor> m_boardConfigurationsRepetitons;

	// Observable //

	std::vector<IChessGameListenerWeakPtr> m_listeners;

	// PGN //

	MoveList m_MoveHistory;
};
