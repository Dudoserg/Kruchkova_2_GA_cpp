#include "stdafx.h"
#include "GA.h"

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
	vector<vector<int>> pathFromTo;
	for (int t = 0; t < data.size(); t++) {
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

		pathFromTo.push_back(path);

	}
	#ifdef DEBUG
	cout << endl;
	#endif

	this->paths.push_back(pathFromTo);
}



vector<int> GA::createIndividual()
{
	int *currentPopulation = new int[n];
	for (int i = 0; i <n; i++) {
		currentPopulation[i] = i;
	}

	int firstRand = 0;
	int secondRand = 0;
	int tmp = 0;
	for (int i = 0; i < n * 10; i++) {
		firstRand = rand() % n + 0;
		secondRand = rand() % n + 0;

		tmp = currentPopulation[firstRand];
		currentPopulation[firstRand] = currentPopulation[secondRand];
		currentPopulation[secondRand] = tmp;
	}

	vector<int> result;
	for (int i = 0; i < n; i++)
		result.push_back(currentPopulation[i]);

	return result;
}


void GA::createFirstPopulation()
{
	for (int i = 0; i < sizePopulation; i++) {
		vector<int> popul = createIndividual();
		#ifdef  DEBUG
		cout << "individ # " << i + 1 << endl;
		for (int j = 0; j < popul.size(); j++)
			cout << popul[j] << " ";
		cout << endl;
		#endif //  DEBUG

		population.push_back(popul);
	}
}