#pragma once

#include "AdjacencyMatrix.h"
#include "Timer.h"
#include <random>

//Klasa realizuj¹ca algorytm Tabu Search

class TabuSearch
{
private:
	std::vector<int> currentSolution; //obecne rozwiazanie
	std::vector<int> neighbourSolution; //sasiednie rozwiazanie
	std::vector<std::vector<int>> graph{ 0 }; //macierz sasiedztwa
	std::vector<std::vector<int>> tabuList{ 0 }; //lista Tabu
	Timer timer; 
	std::pair<int, int> lastMove; //ostatni ruch
	std::pair<int, int> bestNeighbourMove; //zmienna pomocnicza
	void generateRandomStartingSolution(); //metoda odpowiedzialna za wygenerowanie losowego poczatkowego rozwiazania
	bool checkTabuList(); //metoda sprawdzajaca czy ruch jest na liscie tabu
	void generateNeighbourSolution(); //metoda generujaca sasiednie rozwiazanie
	void lowerCadence(); //obnizanie kadencji
	int calculateCost(std::vector<int> solution); //metoda odpowiedzialna za obliczenie kosztu rozwiazania
public:
	void tabuSearch(AdjacencyMatrix&, int); //g³ówna metoda algorytmu
};

