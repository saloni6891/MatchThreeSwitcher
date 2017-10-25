#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
//#include "Match.h
#include "FindShapeMatch.h"
#include "ShapeMatch.h"
using namespace std;

int main() {

	int arr[6][8] =
	{
		{ 6,1,4,3,2,2,4,2 },
		{ 6,6,5,3,6,6,2,2 },
		{ 3,6,1,5,6,6,4,2 },
		{ 5,2,5,5,5,4,2,2 },
		{ 4,4,2,3,5,5,4,2 },
		{ 4,6,5,2,5,6,2,2 }
	};

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
	auto newMatch = GetAllHorVerMatches(arrPointer, 8, 8);
	auto sortedMatch = SortMatchList(newMatch);
	auto smallLMatch = FindLShapeMatches(arrPointer, 8, 8);
	
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