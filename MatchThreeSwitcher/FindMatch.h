#pragma once
#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

using Match = std::pair<int, int>;
using MatchList = std::vector<Match>;
enum Direction
{
	Horizontal,
	Vertical
};

MatchList GetMatch(int row, int col, int num, int** grid, Direction dir)
{
	MatchList matches;

	matches.push_back(make_pair(row, col));

	for (int i = 0; i <= 1; i++) {
		for (int offset = 1; offset < num; offset++) {
			if (dir == Direction::Vertical)
			{
				int z = i ? row + offset : row - offset;

				if (z < 0 || z >= num) {
					break;
				}

				if (grid[z][col] == grid[row][col]) {
					if (i)
					{
						matches.push_back(make_pair(z, col));
					}
					else
					{
						matches.insert(matches.begin(), make_pair(z, col));
					}
				}
				else {
					break;
				}
			}
			else
			{ 
				int z = i ? col + offset : col - offset;

				if (z < 0 || z >= num) {
					break;
				}

				if (grid[row][z] == grid[row][col]) {
					if (i)
					{
						matches.push_back(make_pair(row, z));
					}
					else
					{
						matches.insert(matches.begin(), make_pair(row, z));
					}
					
				}
				else {
					break;
				}
			}

		}
	}

	return matches;
}

void GetMatchesInOneDirection(int** grid, int nrow, int ncol, vector<MatchList>& matches, Direction dir)
{
	for (int i = 0; i < nrow; ++i)
	{
		int j = 0;
		while (j < ncol)
		{
			MatchList match;
			if (dir == Direction::Vertical)
			{
				match = GetMatch(j, i, ncol, grid, Direction::Vertical);
			}
			else
			{
				 match = GetMatch(i, j, ncol, grid, Direction::Horizontal);
			}
			
			if (match.size() >=3)
			{
				matches.push_back(match);
				j = j + match.back().second + 1;
			}
			else
			{
				++j;
			}

		}
	}

}

vector<MatchList> GetAllHorVerMatches(int** grid, int nrow, int ncol)
{
	vector<MatchList> allMatches;

	GetMatchesInOneDirection(grid, nrow, ncol, allMatches, Direction::Horizontal);
	GetMatchesInOneDirection(grid, ncol, nrow, allMatches, Direction::Vertical);

	return allMatches;
}

bool SortBySize(const MatchList &a, const MatchList &b)
{
	return (a.size() < b.size());
}

vector<MatchList> SortMatchList(std::vector<MatchList>& matchList)
{
	sort(matchList.begin(), matchList.end(), SortBySize);
	return matchList;
}
