#pragma once
#include "AdjacencyMatrix.h"
#include "Timer.h"
#include "GeneticAlgorithm.h"
#include <iostream>
#include <string>
#include <limits>

//Klasa realizuj¹ca komunikacjê z u¿ytkownikiem i wywo³uj¹ca wybrane przez niego metody

class Menu
{
private:
	AdjacencyMatrix* graph = nullptr;
	Timer timer;
	int stopCondition = 5; //kryterium stopu
	std::string crossoverMethod = "pmx"; //metoda krzyzowania
	std::string mutationMethod = "inverse"; //metoda mutacji
	double crossoverProbability = 0.8; //wspolczynnik krzyzowania
	double mutationProbability = 0.01; //wspolczynnik mutacji
	int populationSize = 100; //rozmiar populacji
	GeneticAlgorithm* ga = nullptr;
	void waitingScreen();
public:
	Menu();

};

