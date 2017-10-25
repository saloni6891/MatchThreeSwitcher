#include "Match.h"

std::vector<std::pair<int, int>> GetHorizontalMatch(int gridValue, int gridX, int gridY, int gridXMax, int gridYMax, int** grid)
{
	std::vector<std::pair<int, int>> horizontalMatch;
	std::vector<std::pair<int, int>> matchList;

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
				horizontalMatch.push_back(std::make_pair(gridX, y));
			}
			else {
				break;
			}
		}
	}


	if (horizontalMatch.size() >= 3) {
		for (int i = 0; i < horizontalMatch.size(); i++) {
			matchList.push_back(horizontalMatch[i]);
		}
	}

	return matchList;
}

std::vector<std::pair<int, int>> GetVerticalMatch(int gridValue, int gridX, int gridY, int gridXMax, int gridYMax, int** grid)
{
	std::vector<std::pair<int, int>> verticalMatch;
	std::vector<std::pair<int, int>> matchList;

	verticalMatch.push_back(std::make_pair(gridX, gridY));

	for (int dir = 0; dir <= 1; dir++) {
		for (int x0ffset = 1; x0ffset < gridXMax; x0ffset++) {
			int x;

			if (dir == 0) {//up
				x = gridX - x0ffset;
			}
			else {//down
				x = gridX + x0ffset;
			}

			if (x < 0 || x >= gridXMax) {
				break;
			}

			if (grid[x][gridY] == grid[gridX][gridY]) {
				verticalMatch.push_back(std::make_pair(x, gridY));
			}
			else {
				break;
			}
		}
	}


	if (verticalMatch.size() >= 3) {
		for (int i = 0; i < verticalMatch.size(); i++) {
			matchList.push_back(verticalMatch[i]);
		}
	}

	return matchList;
}

std::vector<std::vector<std::pair<int, int>>> GetAllMatches(int** grid, int nrow, int ncol)
{
	std::vector<std::vector<std::pair<int, int>>> allMatches;

	for (int i = 0; i < nrow; ++i)
	{
		int j = 0;
		while (j < ncol)
		{
			std::vector<std::pair<int, int>> match = GetHorizontalMatch(grid[i][j], i, j, nrow, ncol, grid);
			if (!match.empty())
			{
				allMatches.push_back(match);
				j = j + match.back().second + 1;
			}
			else
			{
				++j;
			}

		}
	}

	for (int j = 0; j < 8; ++j)
	{
		int i = 0;
		while (i < 8)
		{
			std::vector<std::pair<int, int>> match = GetVerticalMatch(grid[i][j], i, j, nrow, ncol, grid);
			if (!match.empty())
			{
				allMatches.push_back(match);
				i = i + match.back().second + 1;
			}
			else
			{
				++i;
			}

		}
	}

	return allMatches;
}

bool sortbysize(const std::vector<std::pair<int, int>> &a, const std::vector<std::pair<int, int>> &b)
{
	return (a.size() < b.size());
}

std::vector<std::vector<std::pair<int, int>>> sortMatchList(std::vector<std::vector<std::pair<int, int>>>& matchList)
{
	sort(matchList.begin(), matchList.end(), sortbysize);
	return matchList;
}