#pragma once
#include <cmath>
#include <vector>
#include <set>
#include <unordered_set>
#include "FindMatch.h"
using namespace std;

MatchList GetVerticalMatchForL(int row, int col, int num, int** grid, int way, int horSize, MatchList& matches)
{
	matches.push_back(make_pair(row, col));

	for (int offset = 1; offset < num; offset++)
	{
		int z = way ? row + offset : row - offset;
		if (z < 0 || z >= num) {
			break;
		}

		if (grid[z][col] == grid[row][col]) {
			if (way)
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

	if (matches.size() != horSize)
	{
		matches.clear();
	}
	return matches;
}

MatchList GetLMatch(int row, int col, int nrow, int ncol, int** grid)
{
	MatchList horizontalMatch;
	MatchList verticalMatch;
	set<Match> LMatchSet;

	horizontalMatch = GetMatch(row, col, ncol, grid, Direction::Horizontal);

	int horSize = horizontalMatch.size();
	if(horSize >= 2)
	{
		GetVerticalMatchForL(horizontalMatch[0].first, horizontalMatch[0].second, nrow, grid, 0, horSize, verticalMatch);
		if (verticalMatch.empty())
		{
			GetVerticalMatchForL(horizontalMatch[0].first, horizontalMatch[0].second, nrow, grid, 1, horSize, verticalMatch);
			if (verticalMatch.empty())
			{
				GetVerticalMatchForL(horizontalMatch[horSize - 1].first, horizontalMatch[horSize - 1].second, nrow, grid, 0, horSize, verticalMatch);
				if (verticalMatch.empty())
				{
					GetVerticalMatchForL(horizontalMatch[horSize - 1].first, horizontalMatch[horSize - 1].second, nrow, grid, 1, horSize, verticalMatch);
				}
			}
		}
	}

	if (horizontalMatch.size() == verticalMatch.size()) {
		for (unsigned int i = 0; i < horizontalMatch.size(); i++) {
			LMatchSet.insert(horizontalMatch[i]);
		}
		for (unsigned int i = 0; i < verticalMatch.size(); i++) {
			LMatchSet.insert(verticalMatch[i]);
		}
	}

	MatchList matchingList;
	if (!LMatchSet.empty())
	{
		matchingList.insert(matchingList.begin(), LMatchSet.begin(), LMatchSet.end());
	}

	return matchingList;
}


set<MatchList> FindLShapeMatches(int** grid, int nrow, int ncol)
{
	set<MatchList> allLMatches;
	for (int i = 0; i < nrow; ++i)
	{
		int j = 0;
		while (j < ncol)
		{
				MatchList match = GetLMatch(i, j, nrow, ncol, grid);
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