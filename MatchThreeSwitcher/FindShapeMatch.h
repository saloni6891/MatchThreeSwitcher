#pragma once
#include <cmath>
#include <vector>
#include <set>
#include <unordered_set>
#include "FindMatch.h"
using namespace std;

MatchList GetVerMatch(int row, int col, int maxOffset, int** grid, int dir, int horSize, MatchList& matches)
{
	matches.push_back(make_pair(row, col));

	for (int offset = 1; offset < maxOffset; offset++)
	{
		int z = dir ? row + offset : row - offset;
		if (z < 0 || z >= maxOffset) { break; }

		if (grid[z][col] == grid[row][col]) 
		{
			if (dir)
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
	MatchList horMatch;
	MatchList verMatch;
	MatchSet LMatchSet;

	horMatch = GetMatch(row, col, ncol, grid, Direction::Horizontal);

	int horSize = horMatch.size();
	if(horSize >= 2)
	{
		GetVerMatch(horMatch[0].first, horMatch[0].second, nrow, grid, 0, horSize, verMatch);
		if (verMatch.empty())
		{
			GetVerMatch(horMatch[0].first, horMatch[0].second, nrow, grid, 1, horSize, verMatch);
			if (verMatch.empty())
			{
				GetVerMatch(horMatch[horSize - 1].first, horMatch[horSize - 1].second, nrow, grid, 0, horSize, verMatch);
				if (verMatch.empty())
				{
					GetVerMatch(horMatch[horSize - 1].first, horMatch[horSize - 1].second, nrow, grid, 1, horSize, verMatch);
				}
			}
		}
	}

	if (horMatch.size() == verMatch.size()) {
		for (unsigned int i = 0; i < horMatch.size(); i++) {
			LMatchSet.insert(horMatch[i]);
		}
		for (unsigned int i = 0; i < verMatch.size(); i++) {
			LMatchSet.insert(verMatch[i]);
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
		for (int j = 0; j < ncol; j++)
		{
			MatchList match = GetLMatch(i, j, nrow, ncol, grid);
			if (match.size() >= 3)
			{
				allLMatches.insert(match);
			}
		}
	}
	return allLMatches;
}