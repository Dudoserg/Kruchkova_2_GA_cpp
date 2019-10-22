#pragma once


#include "DUDOS.h"
#include <iostream>
#include <vector>
using namespace std;


class Path
{
public:
	Path();
	~Path();
	int from;
	int to;
	vector<int> path;
	int weight;
};

