#pragma once

#include "IChessGame.h"
#include "Piece.h"
#include "PGNFormat.h"

#include <array>
#include <unordered_map>
#include <string>

using ArrayBoard = std::array<std::array<PiecePtr, 8>, 8>;
using ChessMap = std::unordered_map<std::array<std::array<char, 8>, 8>, int, struct HashFunctor>;
using ChessVector = std::vector<std::array<std::array<char, 8>, 8>>;
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
	Reset,
	HistoryUpdate
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
	ChessGame(const CharBoard& inputConfig, EColor turn = EColor::White, CastleValues castle = { true, true, true, true });

	// Virtual Implementations //

	void ResetGame() override;
	void RestoreGame(const CharBoard& inputConfig, EColor turn = EColor::White, CastleValues castle = { true, true, true, true }) override;

	IPiecePtr		GetIPiecePtr(Position pos) const override;
	PositionList	GetPossibleMoves(Position currentPos) const override;
	IPieceList		GetCapturedPieces(EColor color) const override;
	EColor			GetCurrentPlayer() const override;
	MoveList		GetMoveHistory() const override;
	CharBoard		GetBoardAtIndex(int index) const override;
	// Setter for Castle Matrix // 

	void SetCastleValues(const CastleValues& Castle);

	// Virtual Implementations //

	void LoadGameFromPGNFormat(std::string& PGNString) override;
	std::string GetPGNFormat() const override;

	bool CheckCheckMate() const ;

	void MakeMove(Position initialpOS, Position finalPos) override;
	void MakeMoveFromString(std::string& move);

	void UpgradePawn(EType upgradeType) override;

	void RequestDraw() override;
	void AcceptDrawProposal() override;
	void DeclineDrawProposal() override;

	bool IsGameOver() const override;
	bool IsDraw() const override;
	bool IsWaitingForDrawResponse() const override;
	bool IsWonByWhitePlayer() const override;
	bool IsWonByBlackPlayer() const override;
	bool IsWaitingForUpgrade() const override;
	bool IsCheckState() const override;

	bool IsWhiteKingsideCastlingAvailable() const override;
	bool IsWhiteQueensideCastlingAvailable() const override;
	bool IsBlackKingsideCastlingAvailable() const override;
	bool IsBlackQueensideCastlingAvailable() const override;

	void AddListener(IChessGameListenerPtr listener) override;
	void RemoveListener(IChessGameListener* listener) override;

private:

	// Game's Logic //

	void InitializeChessGame();
	void InitializeChessGame(const CharBoard& inputConfig, EColor turn = EColor::White, CastleValues castle = {true, true, true, true});

	void ResetBoard();

	PiecePtr GetPiece(Position pos, const ArrayBoard& board) const;
	PieceList GetCheckPieces(Position& checkPos) const;
	Position GetMovingDirections(const Position& checkPiecePos) const;
	PositionList GetToBlockPositions(const Position& checkPiecePos) const;
	Position GetPiecePositionWithSameTypeThatCanMoveToFinalPosition(Position initialPos, Position finalPos, EType currentPieceType);
	
	void AddCastle(Position kingPosition, PositionList& kingPossibleMoves) const;
	void AddMove(Position finalPosition, std::string& move);	// Ads the move in history 

	void SaveConfiguration();

	bool CheckStaleMate() const;
	bool CheckThreeFoldRepetition();

	bool CheckPieceCanBeCaptured(const Position& checkPiecePos) const;
	bool CanBeCaptured(const ArrayBoard& board, Position toCapturePos) const;
	bool KingsWayCanBeBlocked(const PositionList& toBlockPositions) const;

	void SwitchTurn();

	// Observable //

	void Notify(ENotification notif, Position init, Position fin);
	void Notify(ENotification notif, Position pos);
	void Notify(ENotification notif);

	// Static Methods //

	static bool IsInMatrix(Position piecePosition);
	static BoardPosition ConvertToBoardPosition(Position pos);

	void ConvertMoveToPositions(std::string& move, Position& initialPos, Position& finalPos);

private:

	ArrayBoard m_board;
	EColor m_turn;

	PositionList m_kingPositions;

	IPieceList m_whitePiecesCaptured;
	IPieceList m_blackPiecesCaptured;

	EGameState m_state;

	CastleValues m_castle;    // Row 1 is for White and Row 2 is for Black ! Column 1 is for left castle and Column 2 is for right castle

	ChessMap m_boardConfigFrequency;
	ChessVector m_boardConfigurations;

	PGNFormat m_PGNFormat;

	// Observable //

	std::vector<IChessGameListenerWeakPtr> m_listeners;
};
