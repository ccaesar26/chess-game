#pragma once

#include "IChessGame.h"
#include "Piece.h"

#include <array>
#include <unordered_map>

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

enum class ENotification
{
	MoveMade,
	PawnUpgrade,
	GameOver,
	DrawProposal,
	CheckState
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
	void RestartChessGame() override;

	// Setter for Castle Matrix // 

	void SetCastleValues(const std::array<std::array<bool, 2>, 2>& Castle);

	// Virtual Implementations //

	IPiecePtr GetIPiecePtr(int row, int col) const override;
	std::vector<std::pair<int, int>> GetMoves(int row, int col) const override;
	IPieceList GetCapturedPieces(EColor color) const override;
	EColor GetCurrentPlayer() const override;

	bool IsStaleMate() const;

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

	// Observable //

	void AddListener(IChessGameListenerPtr listener);
	void RemoveListener(IChessGameListenerPtr listener);
	void Notify(ENotification notif, int ir = 0, int ic = 0, int fr = 0, int fc = 0); // different implementations

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

	void SaveCurrentConfig();

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

	// Row 1 is for White and Row 2 is for Black ! Column 1 is for left castle and Column 2 is for right castle
	std::array<std::array<bool, 2>, 2> m_Castle;    

	std::unordered_map<std::array<std::array<char, 8>, 8>, int, HashFunctor> m_boardConfigurationsRepetitons;

	// Observable //

	std::vector<std::weak_ptr<IChessGameListener>> m_listeners;
};
