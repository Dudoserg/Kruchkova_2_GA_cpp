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

#include<cstdlib> 
#include<thread>

#include "GA.h"
const int INF = 1000000000;

using namespace std;

void startGA();

void testThread();

void funcForThread(int &x, int rnd);

int main()
{

	srand(time(NULL));
	//unsigned int start_time = clock(); // начальное время

	//testThread();

	//unsigned int end_time = clock(); // конечное время
	//unsigned int search_time = end_time - start_time; // искомое время

	//cout << endl << "time = "; printf("%.3f\n", search_time / 1000.0);

	startGA();


    return 0;
}




void startGA() {

	unsigned int start_time = clock(); // начальное время
									   // здесь должен быть фрагмент кода, время выполнения которого нужно измерить

	GA* ga = new GA();
	ga->start();
	ga->createFirstPopulation();

	int countIteration = 50;
	for (int i = 0; i < countIteration; i++) {
		// считаем фитнес и процент выживаемости
		ga->fitness();
		ga->calculatePercent();
		cout << 1 << endl;

		// удаляем слабые особи, чтобы их осталось столько, сколько было
		ga->killWeakIndivid();
		cout << 2 << endl;

		#if DEBUG_ON

		cout << endl << "it #" << i ;
		cout << "_ind #1___" ;
		for (int i = 0; i < ga->population[0]->path.size(); i++)
			cout << ga->population[0]->path[i] << " ";
		cout << "___fit = " << ga->population[0]->fitness;

		cout << "_ind #2___";
		for (int i = 0; i < ga->population[1]->path.size(); i++)
			cout << ga->population[1]->path[i] << " ";
		cout << "___fit = " <<  ga->population[1]->fitness;

		#endif // DEBUG_ON

		// пересчитываем фитнес и процент выживаемости
		ga->fitness();
		ga->calculatePercent();
		cout << 3 << endl;
		//std::sort(ga->population.begin(), ga->population.end(), Individ::testSort);
		
		// размножение
		ga->reproduction();
		cout << 4 << endl;
		ga->fitness();
		ga->calculatePercent();
		cout << 5 << endl;
		//cout << "=====================  " << i << " =====================";
		//ga->printPopulation();

		ga->mutation();
		cout << 5 << endl;
	
	}

	ga->fitness();
	ga->calculatePercent();

	ga->killWeakIndivid();

	ga->fitness();
	ga->calculatePercent();

	std::sort(ga->population.begin(), ga->population.end(), Individ::testSort);


	cout << endl << endl << "=======================================================" << endl;
	cout << "result = " << ga->population[0]->fitness << endl;
	cout << "minimalFitnes = " << ga->minimalFitnes << endl;
	cout << "minimalFitnesIteration = " << ga->minimalFitnesIteration << endl;
	cout << endl << "=======================================================" << endl;

	unsigned int end_time = clock(); // конечное время
	unsigned int search_time = end_time - start_time; // искомое время
	cout << endl << "time = "; printf("%.3f\n", search_time / 1000.0);

	cout << endl;
	for (int i = 0; i < ga->population[0]->path.size(); i++)
		cout << ga->population[0]->path[i] << " ";
	cout << endl;
}


void testThread()
{
	const int length = 5;

	thread::id id;

	thread thread_array[length];
	//vector<int> result(length);
	int result[length];
	for (int i = 0; i < length; i++) {
		int rnd = rand() % 10 + 1;
		cout << rnd << " ";
		thread_array[i] = thread(funcForThread, ref(result[i]), rnd);
	}
	cout << endl;
	for (int i = 0; i < length; i++) {
		if (thread_array[i].joinable()) {
			id = thread_array[i].get_id();
			thread_array[i].join();
			cout << "Thread with id " << id << " finished. With result " << result[i] << "\n";
		}
	}
	cout << endl<< "end";
}

void funcForThread(int &x, int rnd)
{
	x = rnd * rnd;
	this_thread::sleep_for(chrono::seconds(rnd));

}
