#pragma once

#include "IChessGame.h"

enum class ETurn
{
	WhitePlayer,
	BlackPlayer
};

class ChessGame : public IChessGame
{

public:

	ChessGame();

	ChessGame(std::array<std::array<char, 8>, 8> inputConfig, 
		bool checkStateBlackKing = false, bool checkStateWhiteKing = false, ETurn turn = ETurn::WhitePlayer);

	bool IsGameOver() const override;

	void PlayTurn(BoardPosition initialPos, BoardPosition finalPos) override;

	Board GetBoard() const override;


	PieceSet GetWhitePiecesAlive() override;


	PieceSet GetBlackPiecesAlive() override;


	PieceSet GetWhitePiecesCaptured() override;


	PieceSet GetBlackPiecesCaptured() override;

private:

	bool IsInMatrix(Position piecePosition);

	bool IsKingInCheckState(EColor color);

	void MakeMove(Position initialPosition, Position finalPosition);

	PiecePtr GetPiece(Position pos) const;

private:

	Board m_board;
	ETurn m_turn;

	Position m_whiteKingPosition;
	bool m_checkStateWhiteKing;

	Position m_blackKingPosition;
	bool m_checkStateBlackKing;

	PieceSet m_whitePiecesAlive;
	PieceSet m_blackPiecesAlive;

	PieceSet m_whitePiecesCaptured;
	PieceSet m_blackPiecesCaptured;
};
