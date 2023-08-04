#pragma once
#include "ChessGame.h"

using CharBoard = std::array<std::array<char, 8>, 8>;

bool ComparePositionLists(const PositionList& piecePossibleMoves, const PositionList& pieceExpectedMoves);

bool CompareCharBoardWithNormalBoard(const CharBoard& charBoard, const ChessGame& chessGame);