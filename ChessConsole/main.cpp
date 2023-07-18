#include "IChessGame.h"
#include <vector>
#include <iostream>

int main()
{
	std::shared_ptr<class IChessGame> g = IChessGame::CreateBoard();
	std::array<std::array<std::shared_ptr<IPiece>, 8>, 8> arr;
	for (int j = 8; j > 0; j--)
	{
		for (int i = 'A'; i <= 'H'; i++)
		{
			if (g->GetIPiece(i, j))
			{
				std::cout << int(g->GetIPiece(i, j)->GetType()) << ' ';
			}
			else
			{
				std::cout << "_ ";
			}
		}
		std::cout << std::endl;
	}

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
	}
	return 0;*/
}