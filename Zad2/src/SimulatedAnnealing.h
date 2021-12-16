#pragma once
#include "AdjacencyMatrix.h"
#include "Timer.h"
#include <random>

//Klasa realizujaca algorytm Simulated Annealing

class SimulatedAnnealing
{
private:
	std::vector<int> currentSolution; //obecne rozwiazanie
	std::vector<int> neighbourSolution; //sasiednie rozwiazanie
	std::vector<std::vector<int>> graph{ 0 }; //macierz sasiedztwa
	Timer timer;
	void generateRandomStartingSolution(); //metoda odpowiedzialna za wygenerowanie losowego poczatkowego rozwiazania
	void generateNeighbourSolution(); //metoda generujaca sasiednie rozwiazanie
	int calculateCost(std::vector<int> solution); //metoda odpowiedzialna za obliczenie kosztu rozwiazania
public:
	void simulatedAnnealing(AdjacencyMatrix&, int stopCondition, int startingTemperature, double coolingRatio);
};

