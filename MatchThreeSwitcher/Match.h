#pragma once
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <unordered_set>
using namespace std;

std::vector<std::pair<int, int>> GetHorizontalMatch(int gridValue, int gridX, int gridY, int gridXMax, int gridYMax, int** grid);

std::vector<std::pair<int, int>> GetVerticalMatch(int gridValue, int gridX, int gridY, int gridXMax, int gridYMax, int** grid);

std::vector<std::vector<std::pair<int, int>>> GetAllMatches(int** grid, int nrow, int ncol);

bool sortbysize(const std::vector<std::pair<int, int>> &a, const std::vector<std::pair<int, int>> &b);

std::vector<std::vector<std::pair<int, int>>> sortMatchList(std::vector<std::vector<std::pair<int, int>>>& matchList);