#pragma once
#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

using Match = pair<int, int>;
using MatchList = vector<Match>;
using MatchSet = set<Match>;
enum Direction
{
	Horizontal,
	Vertical
};

MatchList GetMatch(int row, int col, int maxOffset, int** grid, Direction dir);

void GetDirMatches(int** grid, int nrow, int ncol, vector<MatchList>& matches, Direction dir);

void GetAllHorVerMatches(int** grid, int nrow, int ncol, vector<MatchList>& matchList);

MatchList GetVerMatch(int row, int col, int maxOffset, int** grid, int dir, int horSize, MatchList& matches);

MatchList GetLMatch(int row, int col, int nrow, int ncol, int** grid);

set<MatchList> FindLShapeMatches(int** grid, int nrow, int ncol);

MatchList GetSquareMatch(int row, int col, int nrow, int ncol, int** grid);

set<MatchList> FindSquareShapeMatches(int** grid, int nrow, int ncol);

MatchList GetZMatch(int row, int col, int nrow, int ncol, int** grid);

set<MatchList> FindZShapeMatches(int** grid, int nrow, int ncol);

bool IsInMatchedElements(MatchList& sortedMatches, set<Match>& matchedElements);

vector<MatchList> SortAndUniquifyMatches(int** grid, int nrow, int ncol);

