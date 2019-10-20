#include "stdafx.h"
#include "GA.h"
#include "Individ.h"
#include "Path.h"
#include <time.h>
#include <sstream>
#include <algorithm>


GA::GA()
{
}


GA::~GA()
{
}

void GA::start()
{
	init();
}

//
void GA::init()
{
	readData();
	calculateAllPath();
}

// —читываем данные в g
void GA::readData()
{
	vector<pair<int, int>> zero;
	zero.push_back(pair<int, int>(1, 1));

	vector<pair<int, int>> one;
	one.push_back(pair<int, int>(0, 1));
	one.push_back(pair<int, int>(2, 1));
	one.push_back(pair<int, int>(3, 1));
	one.push_back(pair<int, int>(4, 1));

	vector<pair<int, int>> two;
	two.push_back(pair<int, int>(1, 1));

	vector<pair<int, int>> three;
	three.push_back(pair<int, int>(1, 1));

	vector<pair<int, int>> four;
	four.push_back(pair<int, int>(1, 1));
	four.push_back(pair<int, int>(5, 1));
	four.push_back(pair<int, int>(6, 1));

	vector<pair<int, int>> five;
	five.push_back(pair<int, int>(4, 1));

	vector<pair<int, int>> six;
	six.push_back(pair<int, int>(4, 1));

	data.push_back(zero);
	data.push_back(one);
	data.push_back(two);
	data.push_back(three);
	data.push_back(four);
	data.push_back(five);
	data.push_back(six);

	//g[0] = zero;
	//g[1] = one;
	//g[2] = two;
	//g[3] = three;
	//g[4] = four;
	//g[5] = five;
	//g[6] = six;

	n = data.size();
}

void GA::calculateAllPath()
{
	for (int i = 0; i < data.size(); i++)
		calculatePathFromVertexToAll(i);
}


// генерируем особь
Individ * GA::createIndividual()
{
	//int *currentPopulation = new int[n + 1];

	vector<int> currentPopulation(n+1);

	for (int i = 0; i < n; i++) {
		currentPopulation[i] = i;
	}
	// на первое место нужно поставить стартовую вершину, и потом ее не трогать, при перемешивании
	
	for (int i = 0; i < n; i++) {
		if (currentPopulation[i] == startVertex) {
			int tmp = currentPopulation[0];
			currentPopulation[0] = currentPopulation[i];
			currentPopulation[i] = tmp;
		}
	}

	// ¬ конце должны вернутьс€ в стартовую вершину, и потом ее не трогать, при перемешивании
	currentPopulation[n] = startVertex;

	int firstRand = 0;
	int secondRand = 0;
	int tmp = 0;
	for (int i = 0; i < n * 10; i++) {
		firstRand = rand() % (n-1) + 1;
		secondRand = rand() % (n-1) + 1;

		tmp = currentPopulation[firstRand];
		currentPopulation[firstRand] = currentPopulation[secondRand];
		currentPopulation[secondRand] = tmp;
	}

	vector<int> result;
	for (int i = 0; i < n + 1; i++)
		result.push_back(currentPopulation[i]);

	Individ* individ = new Individ();
	individ->path = result;

	return individ;
}


// »щем путь от вершины ƒо всех остальных
void GA::calculatePathFromVertexToAll(int startVertex)
{
	int s = startVertex;
	vector<int> d(n, INF), p(n);
	d[s] = 0;
	vector<char> u(n);
	for (int i = 0; i < n; ++i) {
		int v = -1;
		for (int j = 0; j<n; ++j)
			if (!u[j] && (v == -1 || d[j] < d[v]))
				v = j;
		if (d[v] == INF)
			break;
		u[v] = true;

		for (size_t j = 0; j<data[v].size(); ++j) {
			int to = data[v][j].first,
				len = data[v][j].second;
			if (d[v] + len < d[to]) {
				d[to] = d[v] + len;
				p[to] = v;
			}
		}
	}

	// сохран€ем путь
	vector<Path*> pathFromTo;

	for (int t = 0; t < data.size(); t++) {

		Path* currPath = new Path();
		currPath->from = startVertex;
		currPath->to = t;



		vector<int> path;
		for (int v = t; v != s; v = p[v])
			path.push_back(v);
		path.push_back(s);
		reverse(path.begin(), path.end());

#ifdef DEBUG
		cout << "path from " << s << " to " << t << ": ";

		for (int i = 0; i < path.size(); i++) {
			cout << path[i] << " ";
		}
		cout << endl;
#endif

		//pathFromTo.push_back(path);

		// устанавливаем маршрут в текущий путь
		currPath->path = path;

		// ¬ычисл€ем длину пути
		currPath->weight = calculateWeightPath(currPath);

		// —охран€ем путь в глобальный массив
		pathFromTo.push_back(currPath);
	}
#ifdef DEBUG
	cout << endl;
#endif

	this->paths.push_back(pathFromTo);
}

// –асчет длины пути
int GA::calculateWeightPath(Path * currPath)
{
	int sum = 0;
	for (int i = 0; i < currPath->path.size() - 1; i++) {
		int first = currPath->path[i];
		int second = currPath->path[i + 1];

		int weight = -1;

		for (int j = 0; j < data[first].size(); j++) {
			if (data[first][j].first == second) {
				weight = data[first][j].second;
				break;
			}
		}

		if (weight != -1)
			sum += weight;
		else
			cout << "====================error=========================" << endl;
	}
	return sum;
}


void GA::createFirstPopulation()
{
	for (int i = 0; i < sizePopulation; i++) {
		Individ* individ = createIndividual();
		#ifdef  DEBUG
		cout << "individ # " << i + 1 << endl;
		for (int j = 0; j < individ->path.size(); j++)
			cout << individ->path[j] << " ";
		cout << endl;
		#endif //  DEBUG

		population.push_back(individ);
	}
}


void GA::fitness()
{
	for (int i = 0; i < sizePopulation; i++) {
		int x = fitnessForIndivid(population[i]);
		population[i]->fitness = x;
	}
	cout << "";
}


int GA::fitnessForIndivid(Individ * individ)
{
	int sum = 0;
	for (int i = 0; i < individ->path.size() - 1; i++) {
		int first = individ->path[i];
		int second = individ->path[i + 1];

		int weight = -1;

		weight = paths[first][second]->weight;
		
		if (weight != -1)
			sum += weight;
		else
			cout << "=========error==========" << endl;
	}

	return sum;
}


void GA::calculatePercent() {
	double ss = 0.0;

	for (int i = 0; i < sizePopulation; i++) {
		double tmp = 1.0 / population[i]->fitness;
		ss += tmp;
	}

	for (int i = 0; i < sizePopulation; i++) {
		double tmp = 1.0 / population[i]->fitness;
		tmp = tmp / ss;
		population[i]->percent = tmp;
	}
	cout << "";
}


void GA::reproduction() {
	
	//vector<double> randarr;
	//for (int i = 0; i < 10000; i++) {
	//	double random = (rand() % 100001) / 100000.0;
	//	randarr.push_back(random);
	//}
	//std::sort(randarr.begin(), randarr.end());
	//reverse(randarr.begin(), randarr.end());
	//cout << endl;
	//for (int i = 0; i < randarr.size(); i++)
	//	cout << randarr[i] << endl;

	double random = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	double sum = 0.0;

	int indexFirstParent = 0;

	for (int i = 0; i < population.size(); i++) {
		sum += population[i]->percent;
		if (random < sum) {
			indexFirstParent = i;
			break;
		}		
	}
	
	int indexSecondParent = -1;
	do {
		random = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		sum = 0.0;
		
		for (int i = 0; i < population.size(); i++) {
			sum += population[i]->percent;
			if (random < sum) {
				indexSecondParent = i;
				break;
			}
		}
	} while (indexSecondParent == indexFirstParent);

	cout << indexFirstParent << " " << indexSecondParent << endl;
	
}