#pragma once
#define DEBUG

#include <iostream>
#include <vector>

using std::vector;
using std::pair;
using namespace std;
class GA
{
public:

	GA();

	~GA();

	// fields
	const int INF = 1000000000;
	int sizePopulation = 5;

	vector<vector<pair<int, int>>> data;
	int n;
	vector<vector<vector<int>>> paths;

	vector<vector<int>> population;

	// methods
	void start();

	// начальна€ попул€ци€
	void createFirstPopulation();

private:
	// fields

	// methods
	void init();

	void readData();

	void calculatePathFromVertexToAll(int startVertex);

	void calculateAllPath();

	// создаем одну особь
	vector<int> createIndividual();

	



};

