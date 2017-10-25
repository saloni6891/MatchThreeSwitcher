#include "ShapeMatch.h"

std::vector<std::pair<int, int>> GetShapeMatch(int gridValue, int gridX, int gridY, int gridXMax, int gridYMax, int** grid)
{
	std::vector<std::pair<int, int>> horizontalMatch;
	std::vector<std::pair<int, int>> verticalMatch;
	std::set<std::pair<int, int>> LMatchSet;
	std::set<std::pair<int, int>> squareMatchSet;
	std::set<std::pair<int, int>> zMatchSet;

	horizontalMatch.push_back(std::make_pair(gridX, gridY));

	for (int dir = 0; dir <= 1; dir++) {
		for (int y0ffset = 1; y0ffset < gridYMax; y0ffset++) {
			int y;

			if (dir == 0) {//left
				y = gridY - y0ffset;
			}
			else {//right
				y = gridY + y0ffset;
			}

			if (y < 0 || y >= gridYMax) {
				break;
			}

			if (grid[gridX][y] == grid[gridX][gridY]) {
				if (dir == 0)
				{
					horizontalMatch.insert(horizontalMatch.begin(), std::make_pair(gridX, y));
				}
				else
				{
					horizontalMatch.push_back(std::make_pair(gridX, y));
				}
			}
			else {
				break;
			}
		}
	}

	bool eligibleForL = false;
	if (horizontalMatch.size() >= 2)
	{
		//veritcal travesal from either of these horizantalmatch positions
		for (unsigned int i = 0; i < horizontalMatch.size(); ++i)
		{
			verticalMatch.clear();
			verticalMatch.push_back(std::make_pair(horizontalMatch[i].first, horizontalMatch[i].second));
			eligibleForL = (i == 0) || (i + 1 == horizontalMatch.size());
			for (int dir = 0; dir <= 1; dir++) {
				for (int x0ffset = 1; x0ffset < gridYMax; x0ffset++) {
					int x;

					if (dir == 0) {//up
						x = horizontalMatch[i].first - x0ffset;
					}
					else {//down
						x = horizontalMatch[i].first + x0ffset;
					}

					if (x < 0 || x >= gridXMax) {
						break;
					}

					if (grid[x][horizontalMatch[i].second] == grid[horizontalMatch[i].first][horizontalMatch[i].second]) {
						verticalMatch.push_back(std::make_pair(x, horizontalMatch[i].second));
					}
					else {
						break;
					}
				}

				if (horizontalMatch.size() == verticalMatch.size() && eligibleForL) {
					for (unsigned int i = 0; i < horizontalMatch.size(); i++) {
						LMatchSet.insert(horizontalMatch[i]);
					}
					for (unsigned int i = 1; i < verticalMatch.size(); i++) {
						LMatchSet.insert(verticalMatch[i]);
					}
					break;
				}
				else if (dir == 0)
				{
					verticalMatch.clear();
					verticalMatch.push_back(std::make_pair(horizontalMatch[i].first, horizontalMatch[i].second));
				}
			}
		}


		//now looking for square or z
		//veritcal travesal from either of these horizantalmatch positions
		//we should iterate to the second last element of horizontal match to find square
		if (LMatchSet.size() > 3 && horizontalMatch.size() > 2)
		{
			horizontalMatch.clear();
		}

		for (int i = 0; horizontalMatch.size() > 0 && i < horizontalMatch.size() - 1; ++i)
		{
			squareMatchSet.clear();
			squareMatchSet.insert(std::make_pair(horizontalMatch[i].first, horizontalMatch[i].second));
			zMatchSet.clear();
			zMatchSet.insert(std::make_pair(horizontalMatch[i].first, horizontalMatch[i].second));

			for (int dir = 0; dir <= 1; dir++) {
				for (int x0ffset = 1; x0ffset < gridYMax; x0ffset++) {
					int x;

					if (dir == 0) {//up
						x = horizontalMatch[i].first - x0ffset;
					}
					else {//down
						x = horizontalMatch[i].first + x0ffset;
					}

					if (x < 0 || x >= gridXMax) {
						break;
					}
					bool eligibleForZ = (horizontalMatch[i].first !=0 && horizontalMatch[i].first != gridXMax - 1);
					if (grid[x][horizontalMatch[i].second] == grid[horizontalMatch[i].first][horizontalMatch[i].second])
					{
						if (grid[x][horizontalMatch[i + 1].second] == grid[horizontalMatch[i + 1].first][horizontalMatch[i + 1].second])
						{
							squareMatchSet.insert(std::make_pair(x, horizontalMatch[i].second));
							squareMatchSet.insert(std::make_pair(x, horizontalMatch[i + 1].second));
							squareMatchSet.insert(std::make_pair(horizontalMatch[i + 1].first, horizontalMatch[i + 1].second));
						}
						else if ( eligibleForZ &&
							grid[dir ? horizontalMatch[i + 1].first - x0ffset : horizontalMatch[i + 1].first + x0ffset][horizontalMatch[i + 1].second] 
							== grid[horizontalMatch[i].first][horizontalMatch[i].second])
						{
							//horizontal Z 
							zMatchSet.insert(std::make_pair(x, horizontalMatch[i].second));
							zMatchSet.insert(std::make_pair(horizontalMatch[i + 1].first, horizontalMatch[i + 1].second));
							zMatchSet.insert(std::make_pair(dir ? horizontalMatch[i + 1].first - x0ffset : horizontalMatch[i + 1].first + x0ffset, horizontalMatch[i + 1].second));
						}
						else if (grid[x][horizontalMatch[i].second - 1] == grid[horizontalMatch[i].first][horizontalMatch[i].second])
						{
							//vertical Z matching at i == 0
							zMatchSet.insert(std::make_pair(x, horizontalMatch[i].second));
							zMatchSet.insert(std::make_pair(x, horizontalMatch[i].second - 1));
							zMatchSet.insert(std::make_pair(horizontalMatch[i + 1].first, horizontalMatch[i + 1].second));

						}
					}
					else if (grid[x][horizontalMatch[i+1].second] == grid[horizontalMatch[i+1].first][horizontalMatch[i+1].second] 
						&& grid[x][horizontalMatch[i+1].second + 1] == grid[horizontalMatch[i+1].first][horizontalMatch[i+1].second])
					{
						//vertical Z matching at i == 1
						zMatchSet.insert(std::make_pair(horizontalMatch[i + 1].first, horizontalMatch[i + 1].second));
						zMatchSet.insert(std::make_pair(x, horizontalMatch[i + 1].second));
						zMatchSet.insert(std::make_pair(x, horizontalMatch[i + 1].second + 1));
					}
					else {
						break;
					}
				}

				if (squareMatchSet.size() != 4)
				{
					squareMatchSet.clear();
					if (dir == 0)
					{
						squareMatchSet.insert(std::make_pair(horizontalMatch[i].first, horizontalMatch[i].second));
					}
				}
				else
				{
					LMatchSet.clear();
				}

				if (zMatchSet.size() != 4)
				{
					zMatchSet.clear();
					if (dir == 0)
					{
						zMatchSet.insert(std::make_pair(horizontalMatch[i].first, horizontalMatch[i].second));
					}
				}
				else
				{
					LMatchSet.clear();
				}
			}
		}
	}

	std::vector<std::pair<int, int>> matchingList;
	if (!LMatchSet.empty())
	{
		matchingList.insert(matchingList.begin(), LMatchSet.begin(), LMatchSet.end());
	}

	if (!squareMatchSet.empty())
	{
		matchingList.insert(matchingList.begin(), squareMatchSet.begin(), squareMatchSet.end());
	}
	if (!zMatchSet.empty())
	{
		matchingList.insert(matchingList.begin(), zMatchSet.begin(), zMatchSet.end());
	}

	return matchingList;
}

std::set<std::vector<std::pair<int, int>>> GetAllShapeMatches(int** grid, int nrow, int ncol)
{
	std::set<std::vector<std::pair<int, int>>> allMatches;
	std::set<std::pair<int, int>> matchedElements;
	for (int i = 0; i < nrow; ++i)
	{
		int j = 0;
		while (j < ncol)
		{
			if (matchedElements.find(std::make_pair(i, j)) == matchedElements.end())
			{
				std::vector<std::pair<int, int>> match = GetShapeMatch(grid[i][j], i, j, nrow, ncol, grid);
				if (!match.empty())
				{
					//matchedElements.insert(match);
					bool addMatch = true;
					for (auto& element : match)
					{

						if (matchedElements.find(element) != matchedElements.end())
						{
							//aleast one of the nodes of the match exist in some other match
							//compare current match with existing match and keep the biggest one
							//iterate over all the elements of allMatches

							for (auto& prevMatch : allMatches)
							{
								for (auto& node : prevMatch)
								{
									if (node.first == element.first && node.second == element.second)
									{
										if (match.size() > prevMatch.size())
										{
											for (auto& node1 : prevMatch)
											{
												matchedElements.erase(node1);
											}
											allMatches.erase(prevMatch);
										}
										else
										{
											addMatch = false;
										}
										break;
									}
								}
							}
						}
					}
					if (addMatch)
					{
						for (auto& element : match)
						{
							matchedElements.insert(element);
						}

						allMatches.insert(match);
					}
					//j = j + match.back().second + 1;
					++j;
				}
				else
				{
					++j;
				}
			}
			else
			{
				++j;
			}
		}
	}

	return allMatches;
}