#include <iostream>
#include <Windows.h>
#include "NEAStar.hpp"
#include "Point.hpp"

using namespace std;

int main()
{
	NEAStar star;
	Map map;
	star.Init(Point(2,0),Point(2,4),&map);

	int dwtick = GetTickCount();
	star.run();
	cout << "Run()= " << GetTickCount()-dwtick << endl;

	star.PrintMap();

	return 0;
}
