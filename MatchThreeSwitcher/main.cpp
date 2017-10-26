#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include "SortingMatches.h"
using namespace std;

int main() {

	int arrTest[8][8] =
	{
		{1,3,2,4,2,5,4,5 },
		{4,1,2,1,5,1,4,3 },
		{1,4,3,6,4,4,4,3 },
		{2,4,3,6,4,5,1,4 },
		{1,5,4,1,6,6,3,3 },
		{3,4,2,2,6,6,1,4 },
		{6,2,2,3,4,5,4,6 },
		{6,6,4,5,3,4,1,6 }
	};
	
	int **arrPointer;
	arrPointer = new int*[8];
	for (int i = 0; i < 8; i++)
	{
		arrPointer[i] = arrTest[i];
	}

	vector<MatchList> matches;
	GetAllHorVerMatches(arrPointer, 8, 8, matches);
	SortMatchList(matches);
	auto finalSortMatch = SortAndRejectMatches(arrPointer, 8, 8);
	
	int temp;
	cout << "This is Match-Three Switcher";
	cin >> temp;

	for (int i = 0; i < 8; i++)
	{
		delete(arrPointer[i]);
	}
	delete(arrPointer);

	return 0;
	
}