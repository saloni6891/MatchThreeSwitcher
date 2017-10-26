#pragma once
#include <cmath>
#include <vector>
#include <set>
#include <unordered_set>
#include "FindShapeMatch.h"
#include "FindZMatch.h"
#include "FindSquare.h"
using namespace std;

void SortAndRejectMatches(int** grid, int nrow, int ncol)
{
	
	auto LMatch = FindLShapeMatches(grid, nrow, ncol);
	auto SquareMatch = FindSquareShapeMatches(grid, nrow, ncol);
	auto ZMatch = FindZShapeMatches(grid, nrow, ncol);
}