#pragma once
#include "AdjacencyMatrix.h"
#include "Timer.h"
#include "SimulatedAnnealing.h"
#include "TabuSearch.h"
#include <iostream>
#include <string>
#include <limits>

//Klasa realizuj�ca komunikacj� z u�ytkownikiem i wywo�uj�ca wybrane przez niego metody

class Menu
{
private:
	AdjacencyMatrix* graph = nullptr;
	SimulatedAnnealing* sa = nullptr;
	TabuSearch* ts = nullptr;
	Timer timer;
	//kryterium stopu
	int stopCondition = 0;
	//poczatkowa temperatura SA
	int startingTemperature = 10000;
	//wspolczynnik wych�adzania SA
	double coolingRatio = 0.99;
	void waitingScreen();

public:
	Menu();

};

