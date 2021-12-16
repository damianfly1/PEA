#pragma once
#include "AdjacencyMatrix.h"
#include <algorithm>
#include "BBvertice.h"
#include "BBCompareCost.h"
#include <queue>;

//Klasa realizuj�ca algorytm Branch&Bound

class BranchAndBound
{
private:
	//metoda tworz�ca kolejny wierzcho�ek w drzewie reprezentuj�cym przestrze� rozwi�za�
	bool generateNextVertice(BBvertice start, int end); 
	//metoda odpowiedzialna za zredukowanie i przygotowanie otrzymanej macierzy s�siedztwa na pocz�tku algorytmu
	void createFirstMatrix(std::vector<std::vector<int>> &graph);
	//kolejka priorytetowa przechowuj�ca wierzcho�ki
	std::priority_queue<BBvertice, std::vector<BBvertice>, CompareCost> bbVertices;
	BBvertice currentVertice; //obecnie rozpatrywany wierzcho�ek
	BBvertice leafVertice; //li�� 
	int upperBound; //aktualna g�rna granica rozwi�zania
public:
	void branchAndBround(AdjacencyMatrix graph); //g��wna metoda
};

