#include "IChessGame.h"
#include <vector>
#include <iostream>

int main()
{
	//std::shared_ptr<class IChessGame> Table = IChessGame::CreateBoard();
	std::vector<int> v;
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
	return 0;
}