#include "Utility.h"

bool ComparePositionLists(const PositionList& piecePossibleMoves, const PositionList& pieceExpectedMoves)
{
	if (piecePossibleMoves.size() != pieceExpectedMoves.size()) 
		return false;
	for (int i = 0; i < pieceExpectedMoves.size(); i++)
	{
		if (piecePossibleMoves[i] != pieceExpectedMoves[i]) 
			return false;
	}
	return true;
}

bool CompareCharBoardWithNormalBoard(const CharBoard& charBoard, const ChessGame& chessGame)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Position pos(i, j);
			if(!chessGame.GetPieceFromBoard(pos) && charBoard[i][j] != ' ')
			if (chessGame.GetPieceFromBoard(pos)->ToLetter() != charBoard[i][j])
				return false;
		}
	}	
	return true;
}
