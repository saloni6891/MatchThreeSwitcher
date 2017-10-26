#pragma once
#include "FindShapeMatch.h"
using namespace std;

MatchList GetSquareMatch(int row, int col, int nrow, int ncol, int** grid)
{
	MatchList horizontalMatch;
	MatchList verticalMatch;
	set<Match> SquareSet;

	horizontalMatch = GetMatch(row, col, ncol, grid, Direction::Horizontal);

	int horSize = horizontalMatch.size();
	if (horSize == 2)
	{
		GetVerMatch(horizontalMatch[0].first, horizontalMatch[0].second, nrow, grid, 0, horSize, verticalMatch);
		if (!verticalMatch.empty())
		{
			verticalMatch.clear();
			GetVerMatch(horizontalMatch[horSize - 1].first, horizontalMatch[horSize - 1].second, nrow, grid, 0, horSize, verticalMatch);
			if (!verticalMatch.empty())
			{
				verticalMatch.clear();
				verticalMatch.push_back(make_pair(horizontalMatch[0].first - 1, horizontalMatch[0].second));
				verticalMatch.push_back(make_pair(horizontalMatch[horSize - 1].first - 1, horizontalMatch[horSize - 1].second));
			}
		}
		else
		{
			GetVerMatch(horizontalMatch[0].first, horizontalMatch[0].second, nrow, grid, 1, horSize, verticalMatch);
			if (!verticalMatch.empty())
			{
				verticalMatch.clear();
				GetVerMatch(horizontalMatch[horSize - 1].first, horizontalMatch[horSize - 1].second, nrow, grid, 1, horSize, verticalMatch);
				if (!verticalMatch.empty())
				{
					verticalMatch.clear();
					verticalMatch.push_back(make_pair(horizontalMatch[0].first + 1, horizontalMatch[0].second));
					verticalMatch.push_back(make_pair(horizontalMatch[horSize - 1].first + 1, horizontalMatch[horSize - 1].second));
				}			
			}
		}
	}

	if (horizontalMatch.size() == verticalMatch.size()) {
		for (unsigned int i = 0; i < horizontalMatch.size(); i++) {
			SquareSet.insert(horizontalMatch[i]);
		}
		for (unsigned int i = 0; i < verticalMatch.size(); i++) {
			SquareSet.insert(verticalMatch[i]);
		}
	}

	MatchList matchingList;
	if (!SquareSet.empty())
	{
		matchingList.insert(matchingList.begin(), SquareSet.begin(), SquareSet.end());
	}

	return matchingList;
}


set<MatchList> FindSquareShapeMatches(int** grid, int nrow, int ncol)
{
	set<MatchList> allLMatches;
	for (int i = 0; i < nrow; ++i)
	{
		for(int j = 0; j < ncol; ++j)
		{
			MatchList match = GetSquareMatch(i, j, nrow, ncol, grid);
			if (match.size() >= 3)
			{
				allLMatches.insert(match);
			}
		}
	}

	return allLMatches;
}
