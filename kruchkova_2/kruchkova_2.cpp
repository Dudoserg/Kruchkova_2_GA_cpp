// kruchkova_2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "DUDOS.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <time.h>
#include <set>  // заголовочный файл множеств и мультимножеств
#include <iterator>
#include <ctime>


#include "GA.h"
const int INF = 1000000000;

using namespace std;

void func();

int main()
{
	//int n;
	//n = 7;
	//
	//vector < vector < pair<int, int> > > g(n);
	//
	//vector<pair<int, int>> zero; 
	//zero.push_back(pair<int, int>(1, 1));

	//vector<pair<int, int>> one;
	//one.push_back(pair<int, int>(0, 1));
	//one.push_back(pair<int, int>(2, 1));
	//one.push_back(pair<int, int>(3, 1));
	//one.push_back(pair<int, int>(4, 1));

	//vector<pair<int, int>> two;
	//two.push_back(pair<int, int>(1, 1));

	//vector<pair<int, int>> three;
	//three.push_back(pair<int, int>(1, 1));

	//vector<pair<int, int>> four;
	//four.push_back(pair<int, int>(1, 1));
	//four.push_back(pair<int, int>(5, 1));
	//four.push_back(pair<int, int>(6, 1));

	//vector<pair<int, int>> five;
	//five.push_back(pair<int, int>(4, 1));

	//vector<pair<int, int>> six;
	//six.push_back(pair<int, int>(4, 1));

	//g[0] = zero;
	//g[1] = one;
	//g[2] = two;
	//g[3] = three;
	//g[4] = four;
	//g[5] = five;
	//g[6] = six;

	//int s = 0; // стартовая вершина

	//vector<int> d(n, INF), p(n);
	//d[s] = 0;
	//vector<char> u(n);
	//for (int i = 0; i < n; ++i) {
	//	int v = -1;
	//	for (int j = 0; j<n; ++j)
	//		if (!u[j] && (v == -1 || d[j] < d[v]))
	//			v = j;
	//	if (d[v] == INF)
	//		break;
	//	u[v] = true;

	//	for (size_t j = 0; j<g[v].size(); ++j) {
	//		int to = g[v][j].first,
	//			len = g[v][j].second;
	//		if (d[v] + len < d[to]) {
	//			d[to] = d[v] + len;
	//			p[to] = v;
	//		}
	//	}
	//}

	//for (int t = 0; t < g.size(); t++) {
	//	cout << "path from " << s << " to " << t << ": ";
	//	vector<int> path;
	//	for (int v = t; v != s; v = p[v])
	//		path.push_back(v);
	//	path.push_back(s);
	//	reverse(path.begin(), path.end());

	//	for (int i = 0; i < path.size(); i++) {
	//		cout << path[i] << " ";
	//	}
	//	cout << endl;
	//}

	unsigned int start_time = clock(); // начальное время
	 // здесь должен быть фрагмент кода, время выполнения которого нужно измерить

	srand(time(NULL));

	
	GA* ga = new GA();
	ga->start();
	ga->createFirstPopulation();


	for (int i = 0; i < 500; i++) {
		// считаем фитнес и процент выживаемости
		ga->fitness();
		ga->calculatePercent();

		// удаляем слабые особи, чтобы их осталось столько, сколько было
		ga->killWeakIndivid();

		// пересчитываем фитнес и процент выживаемости
		ga->fitness();
		ga->calculatePercent();

		//std::sort(ga->population.begin(), ga->population.end(), Individ::testSort);

		// размножение
		ga->reproduction();

		ga->fitness();
		ga->calculatePercent();

		//cout << "=====================  " << i << " =====================";
		//ga->printPopulation();

		if( i != 2000 - 1)
			ga->mutation();
	}
	
	ga->fitness();

	ga->calculatePercent();

	std::sort(ga->population.begin(), ga->population.end(), Individ::testSort);
	
	unsigned int end_time = clock(); // конечное время
	unsigned int search_time = end_time - start_time; // искомое время

	cout << endl << endl << "=======================================================" << endl << "result" << ga->population[0]->fitness << endl;
	cout << "minimalFitnes = " << ga->minimalFitnes << endl;
	cout << "minimalFitnesIteration = " << ga->minimalFitnesIteration << endl;
	cout << endl << "=======================================================" << endl;
	cout << endl << "time = "  ; printf("%.3f\n", search_time / 1000.0);

	

    return 0;
}


