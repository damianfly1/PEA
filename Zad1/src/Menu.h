#pragma once
#include "AdjacencyMatrix.h"
#include "Timer.h"
#include "BruteForce.h"
#include <iostream>
#include <string>
#include "BranchAndBound.h"
#include "DynamicProgramming.h"
#include <limits>

//Klasa realizuj�ca komunikacj� z u�ytkownikiem i wywo�uj�ca wybrane przez niego metody

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

