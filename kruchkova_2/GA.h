#pragma once
#define DEBUG

#include <iostream>
#include <vector>

using std::vector;
using std::pair;
using namespace std;
class Deickstra
{
public:

	Deickstra();

	~Deickstra();

	// fields
	const int INF = 1000000000;
	vector<vector<pair<int, int>>> data;
	int n;
	vector<vector<vector<int>>> paths;

	// methods
	void start();

private:
	// fields

	// methods
	void init();

	void readData();

	void calculatePathFromVertexToAll(int startVertex);

	void calculateAllPath();

};

