/*
#pragma once
#include <cmath>
#include <vector>
#include <set>
#include <unordered_set>
#include "FindShapeMatch.h"
using namespace std;

MatchList GetZMatch(int row, int col, int nrow, int ncol, int** grid)
{
	MatchList horizontalMatch;
	MatchList verticalMatch;
	set<Match> ZSet;

	horizontalMatch = GetMatch(row, col, ncol, grid, Direction::Horizontal);

	int horSize = horizontalMatch.size();
	if (horSize == 2)
	{
		GetVerticalMatchForL(horizontalMatch[0].first, horizontalMatch[0].second, nrow, grid, 0, horSize, verticalMatch);
		if (!verticalMatch.empty())
		{
			verticalMatch.clear();
			GetVerticalMatchForL(horizontalMatch[horSize - 1].first, horizontalMatch[horSize - 1].second, nrow, grid, 1, horSize, verticalMatch);
			if (!verticalMatch.empty())
			{
				verticalMatch.clear();
				verticalMatch.push_back(make_pair(horizontalMatch[0].first - 1, horizontalMatch[0].second));
				verticalMatch.push_back(make_pair(horizontalMatch[horSize - 1].first + 1, horizontalMatch[horSize - 1].second));
			}
		}
		else
		{
				GetVerticalMatchForL(horizontalMatch[0].first, horizontalMatch[0].second, nrow, grid, 1, horSize, verticalMatch);
				if (!verticalMatch.empty())
				{
					verticalMatch.clear();
					GetVerticalMatchForL(horizontalMatch[horSize - 1].first, horizontalMatch[horSize - 1].second, nrow, grid, 0, horSize, verticalMatch);
					if (!verticalMatch.empty())
					{
						verticalMatch.clear();
						verticalMatch.push_back(make_pair(horizontalMatch[0].first + 1, horizontalMatch[0].second));
						verticalMatch.push_back(make_pair(horizontalMatch[horSize - 1].first - 1, horizontalMatch[horSize - 1].second));
					}
					else if ()
					{
						verticalMatch.clear();
						verticalMatch.push_back(make_pair(horizontalMatch[0].first + 1, horizontalMatch[0].second));
						verticalMatch.push_back(make_pair(horizontalMatch[horSize - 1].first + 1, horizontalMatch[0].second - 1));
					}
			}
		}
	}

	if (horizontalMatch.size() == verticalMatch.size()) {
		for (unsigned int i = 0; i < horizontalMatch.size(); i++) {
			ZSet.insert(horizontalMatch[i]);
		}
		for (unsigned int i = 0; i < verticalMatch.size(); i++) {
			ZSet.insert(verticalMatch[i]);
		}
	}

	MatchList matchingList;
	if (!ZSet.empty())
	{
		matchingList.insert(matchingList.begin(), ZSet.begin(), ZSet.end());
	}

	return matchingList;
}


set<MatchList> FindSShapeMatches(int** grid, int nrow, int ncol)
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
*/