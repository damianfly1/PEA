#pragma once
#include "AdjacencyMatrix.h"

//Klasa realizująca algorytm dynamic programming (held-karp)

class DynamicProgramming
{
private:
	//metoda wywoływana rekurencyjnie, przekazywane parametry to aktualny wierzcholek i stan 
	int findMinCost(int, int); 
	int end; //stan końcowy algorytmu (wszystkie bity ustawione na 1)
	//macierz przechowująca aktualne minimalne odległości o rozmiarze liczba wierzchołków x liczba możliwych stanów
	std::vector<std::vector<int>> minDistanceMatrix; 
	//macierz z oryginalnego grafu
	std::vector<std::vector<int>> originalMatrix;
	void findPath(int set, int prevVertice); //metoda wywoływana rekrenyjnie
	std::vector<int> path; //metoda znajdujaca sciezke
public:
	void dynamicProgramming(AdjacencyMatrix graph); //głowna metoda 
	~DynamicProgramming(); //destruktor
};

