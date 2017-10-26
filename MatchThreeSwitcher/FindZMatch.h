#pragma once
#include <cmath>
#include <vector>
#include <set>
#include <unordered_set>
#include "FindShapeMatch.h"
using namespace std;

MatchList GetZMatch(int row, int col, int nrow, int ncol, int** grid)
{
	MatchList horMatch;
	MatchList verMatch;
	set<Match> ZSet;

	horMatch = GetMatch(row, col, ncol, grid, Direction::Horizontal);

	int horSize = horMatch.size();
	if (horSize == 2)
	{
		GetVerMatch(horMatch[0].first, horMatch[0].second, nrow, grid, 0, horSize, verMatch);
		if (!verMatch.empty())
		{
			verMatch.clear();
			GetVerMatch(horMatch[horSize - 1].first, horMatch[horSize - 1].second, nrow, grid, 1, horSize, verMatch);
			if (!verMatch.empty())
			{
				verMatch.clear();
				verMatch.push_back(make_pair(horMatch[0].first - 1, horMatch[0].second));
				verMatch.push_back(make_pair(horMatch[horSize - 1].first + 1, horMatch[horSize - 1].second));
			}
		}
		else
		{
				GetVerMatch(horMatch[0].first, horMatch[0].second, nrow, grid, 1, horSize, verMatch);
				if (!verMatch.empty())
				{
					verMatch.clear();
					GetVerMatch(horMatch[horSize - 1].first, horMatch[horSize - 1].second, nrow, grid, 0, horSize, verMatch);
					if (!verMatch.empty())
					{
						verMatch.clear();
						verMatch.push_back(make_pair(horMatch[0].first + 1, horMatch[0].second));
						verMatch.push_back(make_pair(horMatch[horSize - 1].first - 1, horMatch[horSize - 1].second));
					}
					else if (grid[horMatch[0].first][horMatch[0].second] == grid[horMatch[0].first + 1][horMatch[0].second - 1])
					{
						verMatch.clear();
						verMatch.push_back(make_pair(horMatch[0].first + 1, horMatch[0].second));
						verMatch.push_back(make_pair(horMatch[horSize - 1].first + 1, horMatch[0].second - 1));
					}
				}
				else
				{
					GetVerMatch(horMatch[horSize - 1].first, horMatch[horSize - 1].second, nrow, grid, 1, horSize, verMatch);
					if (!verMatch.empty())
					{
						verMatch.clear();
						if (grid[horMatch[horSize-1].first][horMatch[horSize-1].second] == grid[horMatch[horSize - 1].first + 1][horMatch[horSize - 1].second + 1])
						{
							verMatch.push_back(make_pair(horMatch[horSize - 1].first + 1, horMatch[horSize - 1].second));
							verMatch.push_back(make_pair(horMatch[horSize - 1].first + 1, horMatch[horSize - 1].second + 1));
						}
					}
				}
		}
	}

	if (horMatch.size() == verMatch.size()) {
		for (unsigned int i = 0; i < horMatch.size(); i++) {
			ZSet.insert(horMatch[i]);
		}
		for (unsigned int i = 0; i < verMatch.size(); i++) {
			ZSet.insert(verMatch[i]);
		}
	}

	MatchList matchingList;
	if (!ZSet.empty())
	{
		matchingList.insert(matchingList.begin(), ZSet.begin(), ZSet.end());
	}

	return matchingList;
}


set<MatchList> FindZShapeMatches(int** grid, int nrow, int ncol)
{
	set<MatchList> allLMatches;
	for (int i = 0; i < nrow; ++i)
	{
		int j = 0;
		while (j < ncol)
		{
			MatchList match = GetZMatch(i, j, nrow, ncol, grid);
			if (match.size() >= 3)
			{
				allLMatches.insert(match);
				++j;
			}
			else
			{
				++j;
			}
		}
	}

	return allLMatches;
}