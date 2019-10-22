#pragma once

#include "DUDOS.h"
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
	int sizePopulation = 6;
	int startVertex = 0;
	int sizeCrossOverWindow = 3;
	int countSwapInMutation = 2;
	int minimalFitnes = 9999;
	int minimalFitnesIteration = 9999;
	int iterationNum = 0;

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

	void reproduction();


	Individ* crossOver(Individ* firstParent, Individ* secondParent);

	int BinSearch(vector<int>  &arr,  int key);

	void mutation();

	void killWeakIndivid();

	void printPopulation();

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

	void mutationIndivid(Individ* individ);

	static bool vertexPairCompare(const pair<int, int> &first, const pair<int, int> &second) {
		return first.first < second.first;
	}



};

