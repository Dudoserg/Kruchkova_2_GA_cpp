#pragma once
#define DEBUG

#include <iostream>
#include <vector>
#include "Individ.h"
#include "Path.h"

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
	int startVertex = 0;

	vector<vector<pair<int, int>>> data;
	int n;
	
	vector<vector<Path*>> paths;

	vector<Individ*> population;

	// methods
	void start();

	// начальна€ попул€ци€
	void createFirstPopulation();

	void fitness();

	void calculatePercent();

private:
	// fields

	// methods
	void init();

	void readData();

	void calculatePathFromVertexToAll(int startVertex);

	void calculateAllPath();

	int calculateWeightPath(Path* currPath);

	// создаем одну особь
	Individ* createIndividual();

	int fitnessForIndivid(Individ* individ);



};

