#pragma once

#include "IChessGame.h"

using ArrayBoard = std::array<std::array<PiecePtr, 8>, 8>;

class ChessGame : public IChessGame
{

public:

	ChessGame();

	ChessGame(std::array<std::array<char, 8>, 8> inputConfig, 
		bool checkStateBlackKing = false, bool checkStateWhiteKing = false, EColor turn = EColor::White);

	bool IsGameOver() const override;

	void PlayTurn(Position initialPos, Position finalPos) override;

	

	IPieceList GetWhitePiecesCaptured() override;

	IPieceList GetBlackPiecesCaptured() override;

	IPiecePtr GetPiece(Position pos) const override;

private:

	bool IsInMatrix(Position piecePosition);

	bool IsKingInCheckState(EColor color);

	void MakeMove(Position initialPosition, Position finalPosition);

private:

	Board m_board;
	EColor m_turn;

	Position m_whiteKingPosition;
	bool m_checkStateWhiteKing;

	Position m_blackKingPosition;
	bool m_checkStateBlackKing;

	IPieceList m_whitePiecesAlive;
	IPieceList m_blackPiecesAlive;

	IPieceList m_whitePiecesCaptured;
	IPieceList m_blackPiecesCaptured;
};
