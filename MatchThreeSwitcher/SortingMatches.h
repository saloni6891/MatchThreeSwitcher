#pragma once
#include <cmath>
#include <vector>
#include <set>
#include <unordered_set>
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
		}
	}
	return isInMatchedElements;
}

vector<MatchList> SortAndRejectMatches(int** grid, int nrow, int ncol)
{
	
	auto LMatch = FindLShapeMatches(grid, nrow, ncol);
	auto SquareMatch = FindSquareShapeMatches(grid, nrow, ncol);
	auto ZMatch = FindZShapeMatches(grid, nrow, ncol);

	vector<MatchList> allMatches;
	allMatches.insert(allMatches.end(), LMatch.begin(), LMatch.end());
	allMatches.insert(allMatches.end(), SquareMatch.begin(), SquareMatch.end());
	allMatches.insert(allMatches.end(), ZMatch.begin(), ZMatch.end());

	auto sortedMatches = SortMatchList(allMatches);
	set<Match> matchedElements;
	vector<MatchList> allSortedMatches;

	for (int i = 0; i < sortedMatches.size(); i++)
	{
		//check is all the elements of sortedMatches[i] is in matched elements set
		if(!IsInMatchedElements(sortedMatches[i], matchedElements))
		{
			//if it is not
			//add all elements of sortedMatches[i] to matchedElements
			//push_back sortedMatches[i] to allSortedMatches
			MatchList matchToAdd = sortedMatches[i];
			for (int j = 0; j < matchToAdd.size(); j++)
			{
				matchedElements.insert(matchToAdd[j]);
			}
			allSortedMatches.push_back(sortedMatches[i]);
		}
		else
		{
			continue;
		}
	}
	

	return allSortedMatches;
}


