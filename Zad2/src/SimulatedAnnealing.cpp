#include "SimulatedAnnealing.h"

using std::cout;
using std::endl;

void SimulatedAnnealing::generateNeighbourSolution()
{
	neighbourSolution = currentSolution;
	int firstIndex = (rand() % (graph.size() - 1)) + 1;
	int secondIndex = (rand() % (graph.size() - 1)) + 1;
	while (secondIndex == firstIndex) {
	secondIndex = (rand() % (graph.size() - 1)) + 1;
	}
	neighbourSolution[secondIndex] = currentSolution[firstIndex];
	neighbourSolution[firstIndex] = currentSolution[secondIndex];
}

int SimulatedAnnealing::calculateCost(std::vector<int> solution)
{
	int sum = 0;
	for (int i = 0;i<graph.size()-1;++i) {
		sum += graph[solution.at(i)][solution.at(i + 1)];
	}
	sum += graph[solution.at(solution.size()-2)][0];
	return sum;
}

void SimulatedAnnealing::generateRandomStartingSolution()
{
	for (int i = 0; i < 100; ++i) {
		int firstIndex = (rand() % (graph.size()-1)) + 1;
		int secondIndex = (rand() % (graph.size()-1)) + 1;
		while (secondIndex == firstIndex) {
			secondIndex = (rand() % (graph.size()-1)) + 1;
		}
		//tworze nowe solution w neighbour solution
		neighbourSolution[secondIndex] = currentSolution[firstIndex];
		neighbourSolution[firstIndex] = currentSolution[secondIndex];
		//przyrownuje current solution do neighbour solution, losuje dalej
		currentSolution = neighbourSolution;
	}
}

void SimulatedAnnealing::simulatedAnnealing(AdjacencyMatrix& passedGraph, int stopCondition, int startingTemperature, double coolingRatio)
{
	//generator randomowych liczb (0...1)
	std::mt19937_64 rng;
	uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	std::seed_seq ss{ uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed >> 32) };
	rng.seed(ss);
	std::uniform_real_distribution<double> unif(0, 1);
	//vector z najlepszym rozwiazaniem
	std::vector<int> bestSolution;
	this->graph = passedGraph.graph;
	//pocz¹tkowa temperatura
	double currentTemperature = startingTemperature;
	int numberOfTries = graph.size();
	//pierwsze rozwi¹zanie 
	for (int i = 0; i < graph.size(); ++i) {
		currentSolution.push_back(i);
	}
	cout << "TEMPERATURA POCZATKOWA: " << startingTemperature << endl;
	cout << "WSPOLCZYNNIK REDUKCJI: " << coolingRatio << endl;
	srand(time(NULL));
	currentSolution.push_back(0);
	neighbourSolution.resize(currentSolution.size());
	neighbourSolution = currentSolution;
	bestSolution.resize(currentSolution.size());
	generateRandomStartingSolution();
	int currentCost = 0;
	int bestCost = INT_MAX;
	std::vector<int> bestNeighbourSolution;
	bestNeighbourSolution.resize(currentSolution.size());
	timer.start();
	while (timer.getSeconds() < stopCondition) {
		for (int i = 0; i < numberOfTries; ++i) {
			//obliczenie kosztu aktualnej sciezki
			currentCost = calculateCost(currentSolution);
			//wygenerowanie sasiedniego rozwiazania
			generateNeighbourSolution();
			//obliczenie kosztu sasiedniego rozwiazania
			int nextCost = calculateCost(neighbourSolution);
			//jesli koszt jest mniejszy akceptujemy rozwiazanie
			if (nextCost < currentCost) {
				currentSolution = neighbourSolution;
				currentCost = nextCost;
				//zapisujemy najlepsze znalezione w epoce rozwiazanie
				if (bestCost > currentCost) {
					bestCost = currentCost;
					bestSolution = currentSolution;
				}
			}
			//w innym przypadku akceptujemy je z odpowiednim prawdopodobienstwem zaleznym od temperatury
			else {
				double helper = exp(double((double(currentCost) - double(nextCost)) / currentTemperature));
				//cout.precision(17);
				double randomNumber = unif(rng);
				if (randomNumber < helper) {
					currentSolution = neighbourSolution;
					currentCost = nextCost;
				}
			}
		}
		//po epoce obnizamy temperature
		currentTemperature *= coolingRatio;
	}
	cout << "KONIEC ALGORYTMU" << endl;
	cout << "KOSZT SCIEZKI: " << bestCost << endl;
	cout << "Sciezka: " << endl;
	for (int vertice : bestSolution) {
		cout << vertice << " -> ";
	}
}
