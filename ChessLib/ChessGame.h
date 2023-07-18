#pragma once

#include "IChessGame.h"
#include "Piece.h"
#include "Board.h"



class ChessGame : public IChessGame
{

public:

	// Constructors //

	ChessGame();

	ChessGame(std::array<std::array<char, 8>, 8> inputConfig, 
		bool checkStateBlackKing = false, bool checkStateWhiteKing = false, EColor turn = EColor::White);

	// Virtual Implementations //
	
	PositionList GetPossibleMoves(Position currentPos) override;

	void MakeMove(Position initialPosition, Position finalPosition) override;

	bool IsGameOver() override;

	// Getters //

	IPieceList GetWhitePiecesCaptured() override;

	IPieceList GetBlackPiecesCaptured() override;

	IPiecePtr GetIPiece(char col, int ln) const;

	PiecePtr GetPiece(Position pos) const ;

	IBoardPtr GetBoard() const override;
	
private:

	bool IsInMatrix(Position piecePosition);

	bool IsKingInCheckState();

private:

	ArrayBoard m_board;
	EColor m_turn;

	Position m_whiteKingPosition;
	bool m_checkStateWhiteKing;

	Position m_blackKingPosition;
	bool m_checkStateBlackKing;

	IPieceList m_whitePiecesCaptured;
	IPieceList m_blackPiecesCaptured;
};
