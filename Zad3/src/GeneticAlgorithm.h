#pragma once

#include "AdjacencyMatrix.h"
#include "Timer.h"
#include <algorithm>
#include<random>

//Klasa realizuj¹ca algorytm genetyczny

class GeneticAlgorithm
{
private:
	Timer timer;
	std::vector<std::pair<std::vector<int>,int>> population; //populacja (wektor par - rozwiazania i wartosci funkcji fitness)
	std::vector<std::pair<std::vector<int>, int>> nextPopulation; //nastepna populacja
	std::vector<std::vector<int>> graph{0}; //macierz sasiedztwa
	int populationSize; //rozmiar populacji
	void createFirstPopulation(); //metoda odpowiedzialna za stworzenie losowej pierwszej populacji
	void calculateFitness(); //metoda wyliczajaca wartosc funkcji fitness dla populacji
	void inversionMutation(std::vector<int>&); //metoda realizujaca mutacje inverse
	void pmx(std::vector<int>&, std::vector<int>&); //metoda realizujaca krzyzowanie PMX
	void ox(std::vector<int>&, std::vector<int>&); //metoda realizujaca krzyzowanie OX 
public:
	void geneticAlgorithm(AdjacencyMatrix& , int populationSize, double crossoverProbability, double mutationProbability, 
		int stopCondition, std::string crossoverMethod, std::string mutationMethod);
};

