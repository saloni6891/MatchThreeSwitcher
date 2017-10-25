#pragma once
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <set>
#include <unordered_set>
using namespace std;


std::vector<std::pair<int, int>> GetShapeMatch(int gridValue, int gridX, int gridY, int gridXMax, int gridYMax, int** grid);

std::set<std::vector<std::pair<int, int>>> GetAllShapeMatches(int** grid, int nrow, int ncol);

