#include "IChessGame.h"
#include <vector>
#include <iostream>

void printBoard(std::shared_ptr<class IChessGame> g)
{
	std::cout << "     A   B   C   D   E   F   G   H " << std::endl;
	std::cout << "   |-------------------------------|" << std::endl;
	for (int j = 8; j > 0; j--)
	{
		std::cout << " " << j << " |";
		for (int i = 'A'; i <= 'H'; i++)
		{
			if (g->GetIPiecePtr(j, i))
			{ 
				std::cout << ' ';
				if (g->GetIPiecePtr(j, i)->GetColor() == EColor::Black)
				{
					switch (g->GetIPiecePtr(j, i)->GetType())
					{
					case EType::Rook:
						std::cout << 'R';
						break;
					case EType::Horse:
						std::cout << 'H';
						break;
					case EType::Bishop:
						std::cout << 'B';
						break;
					case EType::Queen:
						std::cout << 'Q';
						break;
					case EType::King:
						std::cout << 'K';
						break;
					case EType::Pawn:
						std::cout << 'P';
						break;
					default:
						break;
					}
				}
				else
				{
					switch (g->GetIPiecePtr(j, i)->GetType())
					{
					case EType::Rook:
						std::cout << 'r';
						break;
					case EType::Horse:
						std::cout << 'h';
						break;
					case EType::Bishop:
						std::cout << 'b';
						break;
					case EType::Queen:
						std::cout << 'q';
						break;
					case EType::King:
						std::cout << 'k';
						break;
					case EType::Pawn:
						std::cout << 'p';
						break;
					default:
						break;
					}
				}
			}
			else
			{
				std::cout << "  ";
			}
			std::cout << " |";
		}
		std::cout << std::endl;
		std::cout << "   |-------------------------------|" << std::endl;
	}
}

void printTurn(EColor turn)
{
	std::cout << std::endl;
	std::cout << "Current turn: ";
	switch (turn)
	{
	case EColor::White:
		std::cout << "White's turn";
		break;
	case EColor::Black:
		std::cout << "Black's turn";
		break;
	default:
		break;
	}
	std::cout << std::endl;
}

bool inputIsDraw(char ic, char ir, char fc, char fr)
{
	if ((ic == 'D' || ic == 'd') && (ir == 'R' || ir == 'r') && (fc == 'A' || fc == 'a') && (fr == 'W' || fr == 'w'))
	{
		return true;
	}
	return false;
}

int main()
{
	/*std::shared_ptr<class IChessGame> g = IChessGame::CreateBoard();
	
	char ic, ir, fc, fr;
	std::string upg;
	
	printBoard(g);
	while (!g->IsGameOver())
	{
		printTurn(g->GetCurrentPlayer());
		std::cout << "-> To request DRAW, type 'DRAW' below" << std::endl;
		std::cout << "Input desired movement (X0 X0) : " << std::endl;
		
		try
		{
			std::cin >> ic >> ir >> fc >> fr;

			if (inputIsDraw(ic, ir, fc, fr))
			{
				g->RequestDraw();
			}

			if (g->IsWaitingForDrawResponse())
			{
				std::cout << "The opponent requested a draw. Do you accept? (y/n) ...";
				std::cin >> ic;
				switch (ic)
				{
				case 'y':
					g->AcceptDrawProposal();
					continue;
				case 'n':
					g->DeclineDrawProposal();
					std::cout << std::endl << "Input desired movement (X0 X0) : " << std::endl;
					std::cin >> ic >> ir >> fc >> fr;
					break;
				default:
					throw "no valid input";
					break;
				}
			}
			
			g->MakeMovement(ic, ir, fc, fr);

			if (g->IsWaitingForUpgrade())
			{
				std::cout << "-> What upgrade do you want for your Pawn? " << std::endl;
				std::cout << "-> Available upgrade: queen, rook, horse, bishop " << std::endl;
				std::cout << "-> Enter your choice... ";
				std::cin >> upg;
				g->UpgradePawn(upg);
			}
		}
		catch (...)
		{
			std::cout << std::endl << "* err *" << std::endl << std::endl;
		}
		printBoard(g);
	}

	std::cout << std::endl;
	if (g->IsDraw())
	{
		std::cout << "Game ended in DRAW " << std::endl;
	}
	else if (g->IsWonByBlackPlayer())
	{
		std::cout << "Game won by Black Player" << std::endl;
	}
	else if (g->IsWonByWhitePlayer())
	{
		std::cout << "Game won by White Player" << std::endl;
	}*/
	return 0;
}