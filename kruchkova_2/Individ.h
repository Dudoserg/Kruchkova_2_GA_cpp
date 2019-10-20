#pragma once

#define DEBUG

#include <iostream>
#include <vector>

using std::vector;
using std::pair;
using namespace std;

class Individ
{
public:
	Individ();
	~Individ();
	vector<int> path;
	int fitness;
	double percent;

	static bool testSort(const Individ* a, const Individ* b)
	{
		return a->percent > b->percent;
	}
private:
};

