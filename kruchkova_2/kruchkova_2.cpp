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

#include<omp.h>
#include<windows.h>

#include "GA.h"
#include "Mylog.h"

const int INF = 1000000000;

using namespace std;

void startGA();

void testThread();

void funcForThread(int &x, int rnd);

int main()
{

	srand(time(NULL));

	startGA();
	int s;

	#pragma omp parallel for private(s) num_threads(2)
	for (int i = 0; i < 10; i++) {
		s = omp_get_thread_num();
		Sleep(1000 * i);
		#pragma omp critical
		std::cout << " i = " << i  << "  s = " << s << endl;		
	}


    return 0;
}




void startGA() {

	unsigned int start_time = clock(); // начальное время
									   // здесь должен быть фрагмент кода, время выполнения которого нужно измерить

	////////////////////////////////////////////////////////////////////////////////////
	//// Создание островов = количеству потоков
	//for (int i = 0; i < GA::THREAD_COUNT_ISLAND; i++) {
	//	GA* tmp = new GA();
	//	tmp->start();
	//	tmp->createFirstPopulation();
	//}
	// первый остров
	GA* ga_first = new GA();
	ga_first->start();
	ga_first->createFirstPopulation();

	// второй остров
	GA* ga_second = new GA();
	ga_second->start();
	ga_second->createFirstPopulation();

	ga_second->population.clear();
	for (int i = 0; i < ga_first->population.size(); i++)
		ga_second->population.push_back(ga_first->population[i]->copy());

	///////////////////////////////////////////////////////////////////////////////////
	
	int bestResult_first_prev = INT_MAX;
	int bestResult_first = INT_MAX;
	int bestResult_second_prev = INT_MAX;
	int bestResult_second = INT_MAX;

	int countUnsuccessfulIslandAssociations = 0;


	vector<GA *> ga_array;
	ga_array.push_back(ga_first);
	ga_array.push_back(ga_second);


	while (true) {

		// массив потоков
		vector<thread> thread_array(ga_first->THREAD_COUNT_ISLAND);

	
		
		///// создаем и запускаем потоки
		for (int i = 0; i < ga_first->THREAD_COUNT_ISLAND; i++) {
			// используем лябду функцию
			thread_array[i] = thread(
				[&](GA * ga)
			{

				int countIteration = 10;
				for (int i = 0; i < countIteration; i++) {
					// считаем фитнес и процент выживаемости
					MyLog::log("1 start", MyLog::Status::DEBUG);
					ga->fitness();
					MyLog::log("2 start", MyLog::Status::DEBUG);
				
					ga->calculatePercent();


					// удаляем слабые особи, чтобы их осталось столько, сколько было
					MyLog::log("3 start", MyLog::Status::DEBUG);
					ga->killWeakIndivid();


#if DEBUG_ON

					std::cout << endl << "it #" << i;
					std::cout << "_ind #1___";
					for (int i = 0; i < ga->population[0]->path.size(); i++)
						std::cout << ga->population[0]->path[i] << " ";
					std::cout << "___fit = " << ga->population[0]->fitness;

					std::cout << "_ind #2___";
					for (int i = 0; i < ga->population[1]->path.size(); i++)
						std::cout << ga->population[1]->path[i] << " ";
					std::cout << "___fit = " << ga->population[1]->fitness;

#endif // DEBUG_ON

					// пересчитываем фитнес и процент выживаемости
					MyLog::log("4 start", MyLog::Status::DEBUG);
					ga->fitness();
					MyLog::log("5 start", MyLog::Status::DEBUG);
					ga->calculatePercent();

					//std::sort(ga->population.begin(), ga->population.end(), Individ::testSort);

					// размножение
					MyLog::log("6 start", MyLog::Status::DEBUG);
					ga->reproduction();

					MyLog::log("7 start", MyLog::Status::DEBUG);
					ga->fitness();
					MyLog::log("8 start", MyLog::Status::DEBUG);
					ga->calculatePercent();

					//std::cout << "=====================  " << i << " =====================";
					//ga->printPopulation();

					MyLog::log("9 start", MyLog::Status::DEBUG);
					ga->mutation();
					MyLog::log("10 start", MyLog::Status::DEBUG);

					cout << "i == " << i << endl;
					
				}

				ga->fitness();
				ga->calculatePercent();

				ga->killWeakIndivid();

				ga->fitness();
				ga->calculatePercent();

				std::sort(ga->population.begin(), ga->population.end(), Individ::testSort);



			}, ga_array[i]);
		}


		///// ждем остановки потоков
		for (int i = 0; i < ga_first->THREAD_COUNT_ISLAND; i++) {
			if (thread_array[i].joinable()) {
				thread_array[i].join();
			}
		}

		// Переносим все особи на первый остров 
		for (int i = 0; i < ga_second->population.size(); i++) {
			ga_first->population.push_back(ga_second->population[i]);
		}
		// вычисляем фитнес для всех особей
		ga_first->fitness();
		ga_first->calculatePercent();

		// размножение особей
		ga_first->reproduction();

		// пересчитываем фитнес
		ga_first->fitness();
		ga_first->calculatePercent();

		// мутируем нужные особи
		ga_first->mutation();

		// удаляем лишние особи
		ga_first->killWeakIndivid();

		// копируем особи с первого острова на второй остров
		ga_second->population.clear();
		for (int i = 0; i < ga_first->population.size(); i++) {
			ga_second->population.push_back(ga_first->population[i]);
		}

		ga_first->fitness();
		ga_first->calculatePercent();

		ga_second->fitness();
		ga_second->calculatePercent();

		bestResult_first_prev = bestResult_first;
		bestResult_first = ga_first->population[0]->fitness;

		bestResult_second_prev = bestResult_second;
		bestResult_second = ga_second->population[0]->fitness;



		// Если Ни на одном острове не стало лучше чем на прошлом шаге, 
		if ( !((bestResult_first < bestResult_first_prev) || (bestResult_second < bestResult_second_prev)) ) {
			// количество безуспешных объединений островов
			countUnsuccessfulIslandAssociations++;
			// Если это количество == 3, то 
			if (countUnsuccessfulIslandAssociations == 2)
				break;
		}
		else {
			cout << "";
		}	

		///////////////////////////////////////////////////////////////////////////////////
	}
	


	std::cout << endl << endl << "=======================================================" << endl;
	std::cout << "result = " << ga_first->population[0]->fitness << endl;
	std::cout << "minimalFitnes = " << ga_first->minimalFitnes << endl;
	std::cout << "minimalFitnesIteration = " << ga_first->minimalFitnesIteration << endl;
	std::cout << endl << "=======================================================" << endl;

	unsigned int end_time = clock(); // конечное время
	unsigned int search_time = end_time - start_time; // искомое время
	std::cout << endl << "time = "; std::printf("%.3f\n", search_time / 1000.0);

	std::cout << endl;
	for (int i = 0; i < ga_first->population[0]->path.size(); i++)
		std::cout << ga_first->population[0]->path[i] << " ";
	std::cout << endl;
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
		std::cout << rnd << " ";
		thread_array[i] = thread(funcForThread, ref(result[i]), rnd);
	}
	std::cout << endl;
	for (int i = 0; i < length; i++) {
		if (thread_array[i].joinable()) {
			id = thread_array[i].get_id();
			thread_array[i].join();
			std::cout << "Thread with id " << id << " finished. With result " << result[i] << "\n";
		}
	}
	std::cout << endl<< "end";
}

void funcForThread(int &x, int rnd)
{
	x = rnd * rnd;
	this_thread::sleep_for(chrono::seconds(rnd));

}
