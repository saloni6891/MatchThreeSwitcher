#pragma once
#include <cmath>
#include <vector>
#include <set>
#include <unordered_set>
#include "FindMatch.h"
using namespace std;

bool IsEligibleForL(int horMatchSize, int index)
{
	//For L match can only happen either on first or last element of match in a row
	return (index == 0) || (index + 1 == horMatchSize);
}

MatchList GetLMatch(int row, int col, int nrow, int ncol, int** grid)
{
	MatchList horizontalMatch;
	MatchList verticalMatch;
	std::set<Match> LMatchSet;

	horizontalMatch = GetMatch(row, col, ncol, grid, Direction::Horizontal);

	bool eligibleForL = false;
	if (horizontalMatch.size() >= 2)
	{
		//veritcal travesal from either of these horizantalmatch positions
		for (unsigned int i = 0; i < horizontalMatch.size(); ++i)
		{
			verticalMatch.clear();
			verticalMatch.push_back(std::make_pair(horizontalMatch[i].first, horizontalMatch[i].second));
			//need to find a way to exlude square
			eligibleForL = IsEligibleForL(horizontalMatch.size(), i);
			for (int dir = 0; dir <= 1; dir++) {
				for (int x0ffset = 1; x0ffset < nrow; x0ffset++) {
					int x;

					if (dir == 0) {//up
						x = horizontalMatch[i].first - x0ffset;
					}
					else {//down
						x = horizontalMatch[i].first + x0ffset;
					}

					if (x < 0 || x >= nrow) {
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
	}

	MatchList matchingList;
	//check for 4 is temp to exclude square
	if (!LMatchSet.empty() && LMatchSet.size() !=4 )
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
					j = j + match.back().second + 1;
				}
				else
				{
					++j;
				}
		}
	}

	return allLMatches;
}