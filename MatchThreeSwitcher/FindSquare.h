#pragma once
#include "FindShapeMatch.h"
using namespace std;

MatchList GetSquareMatch(int row, int col, int nrow, int ncol, int** grid)
{
	MatchList horMatch;
	MatchList verMatch;
	set<Match> SquareSet;

	horMatch = GetMatch(row, col, ncol, grid, Direction::Horizontal);

	int horSize = horMatch.size();
	if (horSize == 2)
	{
		GetVerMatch(horMatch[0].first, horMatch[0].second, nrow, grid, 0, horSize, verMatch);
		if (!verMatch.empty())
		{
			verMatch.clear();
			GetVerMatch(horMatch[horSize - 1].first, horMatch[horSize - 1].second, nrow, grid, 0, horSize, verMatch);
			if (!verMatch.empty())
			{
				verMatch.clear();
				verMatch.push_back(make_pair(horMatch[0].first - 1, horMatch[0].second));
				verMatch.push_back(make_pair(horMatch[horSize - 1].first - 1, horMatch[horSize - 1].second));
			}
		}
		else
		{
			GetVerMatch(horMatch[0].first, horMatch[0].second, nrow, grid, 1, horSize, verMatch);
			if (!verMatch.empty())
			{
				verMatch.clear();
				GetVerMatch(horMatch[horSize - 1].first, horMatch[horSize - 1].second, nrow, grid, 1, horSize, verMatch);
				if (!verMatch.empty())
				{
					verMatch.clear();
					verMatch.push_back(make_pair(horMatch[0].first + 1, horMatch[0].second));
					verMatch.push_back(make_pair(horMatch[horSize - 1].first + 1, horMatch[horSize - 1].second));
				}			
			}
		}
	}

	if (horMatch.size() == verMatch.size()) {
		for (unsigned int i = 0; i < horMatch.size(); i++) {
			SquareSet.insert(horMatch[i]);
		}
		for (unsigned int i = 0; i < verMatch.size(); i++) {
			SquareSet.insert(verMatch[i]);
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
