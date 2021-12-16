#pragma once
#include "AdjacencyMatrix.h"

//Klasa realizuj�ca algorytm dynamic programming (held-karp)

class DynamicProgramming
{
private:
	//metoda wywo�ywana rekurencyjnie, przekazywane parametry to aktualny wierzcholek i stan 
	int findMinCost(int, int); 
	int end; //stan ko�cowy algorytmu (wszystkie bity ustawione na 1)
	//macierz przechowuj�ca aktualne minimalne odleg�o�ci o rozmiarze liczba wierzcho�k�w x liczba mo�liwych stan�w
	std::vector<std::vector<int>> minDistanceMatrix; 
	//macierz z oryginalnego grafu
	std::vector<std::vector<int>> originalMatrix;
	void findPath(int set, int prevVertice); //metoda wywo�ywana rekrenyjnie
	std::vector<int> path; //metoda znajdujaca sciezke
public:
	void dynamicProgramming(AdjacencyMatrix graph); //g�owna metoda 
	~DynamicProgramming(); //destruktor
};

