#include "TabuSearch.h"

using std::cout;
using std::endl;

bool TabuSearch::checkTabuList()
{
	//sprawdzamy czy ruch znajduje sie na liscie tabu
	if ((tabuList[lastMove.first][lastMove.second] != 0) || (tabuList[lastMove.second][lastMove.first] != 0)) return true;
	//jesli ruch jest dozwolony zwracamy false
	return false;
}

void TabuSearch::generateNeighbourSolution()
{
	neighbourSolution = currentSolution;
	int firstIndex = (rand() % (graph.size() - 1)) + 1;
	int secondIndex = (rand() % (graph.size() - 1)) + 1;
	while (secondIndex == firstIndex) {
		secondIndex = (rand() % (graph.size() - 1)) + 1;
	}
	//zapisujemy ruch do zmiennej
	lastMove = std::make_pair(currentSolution[firstIndex], currentSolution[secondIndex]);
	neighbourSolution[secondIndex] = currentSolution[firstIndex];
	neighbourSolution[firstIndex] = currentSolution[secondIndex];
}

void TabuSearch::lowerCadence()
{
	//obnizanie kadencji
	for (int i = 0; i < tabuList.size(); ++i) {
		for (int j = 0; j < tabuList.size(); ++j) {
			if (tabuList[i][j] != 0) tabuList[i][j]--;
		}
	}
}

int TabuSearch::calculateCost(std::vector<int> solution)
{
	int sum = 0;
	for (int i = 0; i < graph.size() - 1; ++i) {
		sum += graph[solution.at(i)][solution.at(i + 1)];
	}
	sum += graph[solution.at(solution.size() - 2)][0];
	return sum;
}

void TabuSearch::generateRandomStartingSolution()
{
	for (int i = 0; i < 100; ++i) {
		int firstIndex = (rand() % (graph.size() - 1)) + 1;
		int secondIndex = (rand() % (graph.size() - 1)) + 1;
		while (secondIndex == firstIndex) {
			secondIndex = (rand() % (graph.size() - 1)) + 1;
		}
		//tworze nowe solution w neighbour solution
		neighbourSolution[secondIndex] = currentSolution[firstIndex];
		neighbourSolution[firstIndex] = currentSolution[secondIndex];
		//przyrownuje current solution do neighbour solution, losuje dalej
		currentSolution = neighbourSolution;
	}
}

void TabuSearch::tabuSearch(AdjacencyMatrix& passedGraph, int stopCondition)
{
	std::vector<int> bestSolution;
	std::vector<int> bestNeighbourSolution;
	this->graph = passedGraph.graph;
	int currentCost = 0;
	int bestCost = INT_MAX;
	int bestNeighbourCost = INT_MAX;
	//ilosc wierzcholkow
	int problemSize = passedGraph.graphSize;
	//minimalna iloœæ przeszukiwanych s¹siadów
	int minM = problemSize / 2;
	//maksymalna iloœæ przeszukiwanych s¹siadów
	int maxM = minM + (minM / 2);
	for (int i = 0; i < graph.size(); ++i) {
		currentSolution.push_back(i);
	}
	tabuList.resize(graph.size(), std::vector<int>(graph.size()));
	for (int i = 0; i < tabuList.size(); ++i) {
		for (int j = 0; j < tabuList.size(); ++j) {
			tabuList[i][j] = 0;
		}
	}
	srand(time(NULL));
	currentSolution.push_back(0);
	neighbourSolution.resize(currentSolution.size());
	bestSolution.resize(currentSolution.size());
	neighbourSolution = currentSolution;
	generateRandomStartingSolution();
	timer.start();
	while (timer.getSeconds() < stopCondition) {
		bestNeighbourCost = INT_MAX;
		//obecny koszt
		currentCost = calculateCost(currentSolution);
		int plus = 0;
		//przegladamy sasiadow nie wiecej niz maxM i nie mniej niz minM razy
		for (int i = 0; i < maxM; ++i) {
			//tworzymy rozwiazanie sasiednie
			generateNeighbourSolution();
			//obliczamy koszt nowego rozwiazania
			int neighbourCost = calculateCost(neighbourSolution);
			//jesli spelnia kryterium aspitacji
			if ((neighbourCost < currentCost)){
				//sprawdzamy czy jest to najlepsze dotychczasowe rozwiazanie
				if (neighbourCost < bestNeighbourCost) {
					bestNeighbourMove = lastMove;
					bestNeighbourCost = neighbourCost;
					bestNeighbourSolution = neighbourSolution;
				}
				//sprawdz czy juz bylo osiagniete minM
				if (i >= minM) {
					//jesli nie to idziemy dalej - o taka ilosc zeby na pewno minM i iles powyzej < maxM
					i = rand() % maxM + minM; //losowanie od minM do maxM
				}
				//jesli tak to konczysz szukanie tego sasiada
				else break;
			}
			//jesli nie spelnia kryterium
			else {
				//sprawdzamy czy jest na liscie tabu
				bool isOnTabuList = checkTabuList();
				//jesli jest restartujemy aktualny loop
				if (isOnTabuList) continue;
				//inaczej sprawdzamy czy jest to najlepsze sasiednie rozwiazanie 
				if (neighbourCost < bestNeighbourCost) {
					bestNeighbourMove = lastMove;
					bestNeighbourCost = neighbourCost;
					bestNeighbourSolution = neighbourSolution;
				}
			}
		}
		//dodajemy najlepszy ruch wykonywany do listy tabu 
		tabuList[lastMove.first][lastMove.second] = minM;
		//zmieniamy aktualne rozwiazanie
		currentSolution = bestNeighbourSolution;
		currentCost = bestNeighbourCost;
		//sprawdzamy czy znalezlismy najlepsze do tej pory rozwiazanie
		if (currentCost < bestCost) {
			bestSolution = currentSolution;
			bestCost = currentCost;
		}
		//obnizamy kadencje
		lowerCadence();
	}
	cout << "KONIEC ALGORYTMU" << endl;
	cout << "KOSZT SCIEZKI: " << bestCost << endl;
	cout << "Sciezka: " << endl;
	for (int vertice : bestSolution) {
		cout << vertice << " -> ";
	}
}
