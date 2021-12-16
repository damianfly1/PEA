#pragma once
#include "AdjacencyMatrix.h"
#include "Timer.h"
#include "BruteForce.h"
#include <iostream>
#include <string>
#include "BranchAndBound.h"
#include "DynamicProgramming.h"
#include <limits>

//Klasa realizuj¹ca komunikacjê z u¿ytkownikiem i wywo³uj¹ca wybrane przez niego metody

class Menu
{
private:
	AdjacencyMatrix* graph = nullptr;
	Timer timer;
	BruteForce *bf = nullptr;
	BranchAndBound *bb = nullptr;
	DynamicProgramming *dp = nullptr;

	void waitingScreen();
	
public: 
	Menu();

};

