#include "MatchThree.h"
#include "SortUtil.h"

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
	if (horSize >= 2)
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
		for (int j = 0; j < ncol; ++j)
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
					if (grid[horMatch[horSize - 1].first][horMatch[horSize - 1].second] == grid[horMatch[horSize - 1].first + 1][horMatch[horSize - 1].second + 1])
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
		for (int j = 0; j < ncol; ++j)
		{
			MatchList match = GetZMatch(i, j, nrow, ncol, grid);
			if (match.size() >= 3)
			{
				allLMatches.insert(match);
			}
		}
	}

	return allLMatches;
}

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

vector<MatchList> SortAndUniquifyMatches(int** grid, int nrow, int ncol)
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
		if (!IsInMatchedElements(allShapes[i], matchedElements))
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