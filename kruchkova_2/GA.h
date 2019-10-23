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

	// Количество потоков в вычислении  FITNESS
	const int THREAD_FITNESS_COUNT = 4;


	// Количество потоков в вычислении REPRODUCTION
	const int THREAD_REPRODUCTION_COUNT = 4;

	static const int INF = 1000000000;
	// размер окна в кроссовере
	static const int sizeCrossOverWindow = 3;
	// количество мутаций 
	static const int countSwapInMutation = 2;


	vector<Individ*> newPopulation;

	int sizePopulation = 6;
	int startVertex = 0;

	int minimalFitnes = 9999;
	int minimalFitnesIteration = 9999;
	int iterationNum = 0;

	vector<vector<pair<int, int>>> data;
	int n;
	
	vector<vector<Path*>> paths;

	vector<Individ*> population;

	// methods
	void start();

	// начальная популяция
	void createFirstPopulation();

	void fitness();

	//void startFitness(int startIndex, int secondIndex);

	int fitnessForIndivid(Individ* individ);

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

	

	void mutationIndivid(Individ* individ);

	static bool vertexPairCompare(const pair<int, int> &first, const pair<int, int> &second) {
		return first.first < second.first;
	}



};

