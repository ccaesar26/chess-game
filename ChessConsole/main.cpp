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
			if (g->GetIPiece(i, j))
			{ 
				std::cout << ' ';
				if (g->GetIPiece(i, j)->GetColor() == EColor::Black)
				{
					switch (g->GetIPiece(i, j)->GetType())
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
					switch (g->GetIPiece(i, j)->GetType())
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

int main()
{
	std::shared_ptr<class IChessGame> g = IChessGame::CreateBoard();
	
	while (!g->IsGameOver())
	{
		printBoard(g);
		std::cout << std::endl;
		std::cout << "Input desired movement (X0 X0) : " << std::endl;
		try
		{
			char ic, fc;
			int ir, fr;
			std::cin >> ic >> ir >> fc >> fr;
			g->MakeMovement(ic, ir, fc, fr);
		}
		catch (...)
		{
			std::cout << std::endl << " ! Move not valid. Try again !" << std::endl;
		}
	}
	printBoard(g);

	//
	/*std::vector<int> v;
	for (int i = 0; i <= 10; i++)
	{
		v.push_back(i);
	}

	
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i] % 2 == 0 || v[i] % 3 == 0)
		{
			v.erase(std::find(v.begin(), v.end(), v[i]));
			i--;
		}	
	}

	for (auto i : v)
	{
		std::cout << i << ' ';
	}*/
	return 0;
}