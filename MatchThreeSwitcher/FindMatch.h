#pragma once
#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

using Match = pair<int, int>;
using MatchList = vector<Match>;
using MatchSet = set<Match>;
enum Direction
{
	Horizontal,
	Vertical
};

MatchList GetMatch(int row, int col, int maxOffset, int** grid, Direction dir)
{
	MatchList matches;

	matches.push_back(make_pair(row, col));

	for (int i = 0; i <= 1; i++) 
	{
		for (int offset = 1; offset < maxOffset; offset++) 
		{
			if (dir == Direction::Vertical)
			{
				int z = i ? row + offset : row - offset;

				if (z < 0 || z >= maxOffset) { break;}

				if (grid[z][col] == grid[row][col]) 
				{
					if (i)
					{
						matches.push_back(make_pair(z, col));
					}
					else
					{
						matches.insert(matches.begin(), make_pair(z, col));
					}
				}
				else 
				{
					break;
				}
			}
			else
			{ 
				int z = i ? col + offset : col - offset;

				if (z < 0 || z >= maxOffset) { break; }

				if (grid[row][z] == grid[row][col]) 
				{
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

void GetDirMatches(int** grid, int nrow, int ncol, vector<MatchList>& matches, Direction dir)
{
	int max1 = dir == Direction::Horizontal ? nrow : ncol;
	int max2 = dir == Direction::Horizontal ? ncol : nrow;
	for (int i = 0; i < max1; ++i)
	{
		int j = 0;
		while (j < max2)
		{
			MatchList match;
			if (dir == Direction::Vertical)
			{
				match = GetMatch(j, i, max2, grid, Direction::Vertical);
			}
			else
			{
				 match = GetMatch(i, j, max2, grid, Direction::Horizontal);
			}
			
			if (match.size() >=3)
			{
				matches.push_back(match);
				j = (dir == Direction::Horizontal ? match.back().second : match.back().first ) + 1;
			}
			else
			{
				++j;
			}

		}
	}

}

void GetAllHorVerMatches(int** grid, int nrow, int ncol, vector<MatchList>& matchList)
{
	GetDirMatches(grid, nrow, ncol, matchList, Direction::Horizontal);
	GetDirMatches(grid, nrow, ncol, matchList, Direction::Vertical);
}

bool SortBySizeAsc(const MatchList &a, const MatchList &b)
{
	return (a.size() < b.size());
}

bool SortBySizeDesc(const MatchList &a, const MatchList &b)
{
	return (a.size() > b.size());
}

void SortMatchList(vector<MatchList>& matchList)
{
	sort(matchList.begin(), matchList.end(), SortBySizeDesc);
}
