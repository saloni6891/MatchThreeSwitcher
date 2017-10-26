#pragma once
#include "FindShapeMatch.h"
#include "FindZMatch.h"
#include "FindSquare.h"
using namespace std;

bool IsInMatchedElements(MatchList& sortedMatches, set<Match>& matchedElements)
{
	bool isInMatchedElements = false;
	for (int i = 0; i < sortedMatches.size(); i++)
	{
		if (matchedElements.find(sortedMatches[i]) != matchedElements.end())
		{
			isInMatchedElements = true;
			break;
		}
	}
	return isInMatchedElements;
}

vector<MatchList> SortAndRejectMatches(int** grid, int nrow, int ncol)
{
	auto LMatch = FindLShapeMatches(grid, nrow, ncol);
	auto SquareMatch = FindSquareShapeMatches(grid, nrow, ncol);
	auto ZMatch = FindZShapeMatches(grid, nrow, ncol);

	vector<MatchList> allShapes;
	allShapes.insert(allShapes.end(), LMatch.begin(), LMatch.end());
	allShapes.insert(allShapes.end(), SquareMatch.begin(), SquareMatch.end());
	allShapes.insert(allShapes.end(), ZMatch.begin(), ZMatch.end());

	SortMatchList(allShapes);
	set<Match> matchedElements;
	vector<MatchList> allSortedMatches;
	
	for (int i = 0; i < allShapes.size(); i++)
	{
		if(!IsInMatchedElements(allShapes[i], matchedElements))
		{
			MatchList matchToAdd = allShapes[i];
			for (int j = 0; j < matchToAdd.size(); j++)
			{
				matchedElements.insert(matchToAdd[j]);
			}
			allSortedMatches.push_back(allShapes[i]);
		}
		else
		{
			continue;
		}
	}

	return allSortedMatches;
}


