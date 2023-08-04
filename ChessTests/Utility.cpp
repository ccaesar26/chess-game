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