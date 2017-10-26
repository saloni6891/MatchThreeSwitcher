#pragma once
#include <vector>
#include <algorithm>
using namespace std;

bool SortBySizeAsc(const vector<pair<int, int>> &a, const vector<pair<int, int>> &b);

bool SortBySizeDesc(const vector<pair<int, int>> &a, const vector<pair<int, int>> &b);

void SortMatchList(vector<vector<pair<int, int>>>& matchList);

