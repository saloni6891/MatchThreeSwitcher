#include "SortUtil.h"

bool SortBySizeAsc(const vector<pair<int, int>> &a, const vector<pair<int, int>> &b)
{
	return (a.size() < b.size());
}

bool SortBySizeDesc(const vector<pair<int, int>> &a, const vector<pair<int, int>> &b)
{
	return (a.size() > b.size());
}

void SortMatchList(vector<vector<pair<int, int>>>& matchList)
{
	sort(matchList.begin(), matchList.end(), SortBySizeDesc);
}