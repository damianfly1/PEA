#include "BruteForce.h"

using std::vector;
using std::next_permutation;

void BruteForce::bruteForce(AdjacencyMatrix matrix)
{
	vector<vector<int>> graph = matrix.graph;
	int size = graph.size();
	//vector z pozostalymi wierzcholkami
	vector<int> otherVertices;
	otherVertices.reserve(size - 1);
	//najlepsza droga obecnie
	int bestDistance = INT_MAX;
	//droga do najlepszego wierzcholka
	vector<int> bestPath;
	bestPath.reserve(size+1);
	bestPath.push_back(0);
	//obecna droga
	int currentDistance;
	//poprzedni wierzcholek
	int previousVertice;
	//wypelnienie vectora pozostalymi wierzcholkami
	for (int i = 1; i <size; i++) {
		otherVertices.push_back(i);
	}
	//sprawdzamy wszystkie permutacje
	while (next_permutation(otherVertices.begin(), otherVertices.end())) {
		//dlugosc nowej sciezki
		currentDistance = 0;
		//poprzedni wierzcholek
		previousVertice = 0;
		//petla obliczajaca wartosc currentDistance
		for (int i = 0; i < size - 1;i++) {
			currentDistance += graph[previousVertice][otherVertices.at(i)];
			previousVertice = otherVertices.at(i);
		}
		currentDistance += graph[previousVertice][0];
		//jesli currentDistance mniejsza od bestDistance zamieniamy bestPath 
		if (currentDistance < bestDistance) {
			bestDistance = currentDistance;
			bestPath.erase(bestPath.begin()+1,bestPath.end());
			bestPath.insert(bestPath.end(), otherVertices.begin(), otherVertices.end());
		}
	}
	bestPath.push_back(0);
	std::cout << "WYNIKI BRUTE FORCE" << std::endl;
	std::cout << "NAJKROTSZA DROGA: " << bestDistance;
	std::cout << std::endl << "SCIEZKA: ";
	for (int vertice : bestPath) {
		std::cout << vertice << " -> ";
	}
}
