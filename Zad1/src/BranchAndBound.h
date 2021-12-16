#pragma once
#include "AdjacencyMatrix.h"
#include <algorithm>
#include "BBvertice.h"
#include "BBCompareCost.h"
#include <queue>;

//Klasa realizuj¹ca algorytm Branch&Bound

class BranchAndBound
{
private:
	//metoda tworz¹ca kolejny wierzcho³ek w drzewie reprezentuj¹cym przestrzeñ rozwi¹zañ
	bool generateNextVertice(BBvertice start, int end); 
	//metoda odpowiedzialna za zredukowanie i przygotowanie otrzymanej macierzy s¹siedztwa na pocz¹tku algorytmu
	void createFirstMatrix(std::vector<std::vector<int>> &graph);
	//kolejka priorytetowa przechowuj¹ca wierzcho³ki
	std::priority_queue<BBvertice, std::vector<BBvertice>, CompareCost> bbVertices;
	BBvertice currentVertice; //obecnie rozpatrywany wierzcho³ek
	BBvertice leafVertice; //liœæ 
	int upperBound; //aktualna górna granica rozwi¹zania
public:
	void branchAndBround(AdjacencyMatrix graph); //g³ówna metoda
};

