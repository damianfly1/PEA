#pragma once
#include "AdjacencyMatrix.h"

//Klasa realizuj¹ca algorytm dynamic programming (held-karp)

class DynamicProgramming
{
private:
	//metoda wywo³ywana rekurencyjnie, przekazywane parametry to aktualny wierzcholek i stan 
	int findMinCost(int, int); 
	int end; //stan koñcowy algorytmu (wszystkie bity ustawione na 1)
	//macierz przechowuj¹ca aktualne minimalne odleg³oœci o rozmiarze liczba wierzcho³ków x liczba mo¿liwych stanów
	std::vector<std::vector<int>> minDistanceMatrix; 
	//macierz z oryginalnego grafu
	std::vector<std::vector<int>> originalMatrix;
	void findPath(int set, int prevVertice); //metoda wywo³ywana rekrenyjnie
	std::vector<int> path; //metoda znajdujaca sciezke
public:
	void dynamicProgramming(AdjacencyMatrix graph); //g³owna metoda 
	~DynamicProgramming(); //destruktor
};

