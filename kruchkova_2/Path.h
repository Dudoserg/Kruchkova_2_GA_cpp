#pragma once

#define DEBUG

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

