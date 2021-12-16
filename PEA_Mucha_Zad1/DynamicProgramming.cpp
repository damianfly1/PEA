#include "DynamicProgramming.h"

using std::vector;
using std::cout;
using std::endl;

int DynamicProgramming::findMinCost(int visitedVertices, int currentVertice)
{
	//jesli odwiedzilismy wszystkie wierzcholki zwracamy koszt z aktualnego wierzcholka do startowego
	if (visitedVertices == end) {
		minDistanceMatrix[currentVertice][visitedVertices] = originalMatrix[currentVertice][0];
		return originalMatrix[currentVertice][0];
	}
	//jesli juz sprawdzalismy dany zbiór wierzcho³ków zwracamy wczesniej obliczony dystans (programowanie dynamiczne)
	if (minDistanceMatrix[currentVertice][visitedVertices] != INT_MAX) {
		return minDistanceMatrix[currentVertice][visitedVertices];
	}
	//petla tworz¹ca nastêpne kombinacje wierzcho³ków
	//1 iteracja: sprawdzamy 1 (001), 2(010), 3(100) itd
	for (int i = 0; i < originalMatrix.size()-1; i++) {
		//odwiedzamy nastepny wierzcholek, kolejny zbiór = obecny zbiór OR kolejny wierzcho³ek
		//np stan 011 OR 100 = 111 czyli beda odwiedzone wszystkie wierzcholki
		int nextSet = visitedVertices | (1 << i);
		//jeœli ju¿ odwiedziliœmy dany wierzcho³ek przechodzimy dalej
		if (nextSet == visitedVertices) continue;
		//rekurencyjne wywo³anie funkcji
		int cost = findMinCost(nextSet, i+1) + originalMatrix[currentVertice][i+1];
		//jeœli znaleŸlismy koszt ni¿szy od minium zmieniamy pozycje w macierzach minDistance
		if (cost < minDistanceMatrix[currentVertice][visitedVertices]) {
			minDistanceMatrix[currentVertice][visitedVertices] = cost;
		}
	}
	//zwracamy minimalny znaleziony dystans
	return minDistanceMatrix[currentVertice][visitedVertices];
}

DynamicProgramming::~DynamicProgramming()
{
	vector<vector<int>>().swap(minDistanceMatrix);
	vector<vector<int>>().swap(originalMatrix);
	vector<int>().swap(path);
}

void DynamicProgramming::findPath(int visitedVertices, int currentVertice)
{
	//zmienne pomocnicze
	int minimum = INT_MAX;
	int bestVertice = 0;
	int nextSet = -1;
	//jesli doszlismy do zbioru koncowego nie kontynuujemy
	if (visitedVertices == end) return;
	for (int i = 0; i < originalMatrix.size() - 1; i++) {
		//kolejny stan/zbiór (analogicznie jak w metodzie findMinCost) 
		nextSet = visitedVertices | (1 << i);
		if (nextSet == visitedVertices) continue;
		//minDistanceMatrix jest juz wypelniona odpowiednimi wartosciami
		int cost = minDistanceMatrix[i + 1][nextSet] + originalMatrix[currentVertice][i+1];
		if (cost < minimum) {
			minimum = cost;
			bestVertice = i + 1;
		}
	}
	nextSet = visitedVertices | (1 << (bestVertice-1));
	path.push_back(bestVertice);
	findPath(nextSet, bestVertice);
}

void DynamicProgramming::dynamicProgramming(AdjacencyMatrix graph)
{
	//skopiowanie macierzy z grafem do nowej zmiennej
	this->originalMatrix = graph.graph;
	//liczba wierzcholkow / wierszy w macierzy
	int numberOfVertices = graph.graphSize;
	//liczba kolumn w macierzy
	//nigdy nie bedzie wystepowal stan 0000 wiec mozemy rozpatrywac tylko 2^(n-1) stanow
	//przykladowo dla 4 wierzcholkow stany 000 001 ... 111
	int numberOfSubsets = pow(2, (numberOfVertices-1));
	vector<int> row(numberOfSubsets, INT_MAX);
	//inicjalizacja minDistanceMatrix 
	minDistanceMatrix = vector<vector<int>>(numberOfVertices, row);
	//inicjalizacja path
	path = vector<int>();
	//oprocz wierzcholka startowego zaden nie odwiedzony wiec stan startowy = 0
	int start = 0;
	//Np dla 4: 1000 - 1 = 111
	end = (1 << (numberOfVertices-1)) - 1;
	//wywolanie rekurencyjnych funkcji
	findMinCost(start, 0);
	findPath(start, 0);
	cout << "WYNIKI HELD-KARP" << endl;
	cout << "NAJKROTSZA DROGA: " << minDistanceMatrix[0][0] << endl;
	cout << "SCIEZKA: 0 -> ";
	for (int vertice : path) {
		cout << vertice << " -> ";
	}
	cout << "0";
}
