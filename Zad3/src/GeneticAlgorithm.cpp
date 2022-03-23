#include "GeneticAlgorithm.h"

using std::vector;
using std::pair;
using std::cout;

void GeneticAlgorithm::createFirstPopulation()
{
	vector<int> firstSolution;
	firstSolution.resize(graph.size() + 1);
	for (int i = 0; i < graph.size(); ++i) {
		firstSolution[i] = i;
	}
	firstSolution[firstSolution.size() - 1] = 0;
	population.push_back(make_pair(firstSolution, 0));
	std::random_device rd;
	std::mt19937 g(rd());
	for (int i = 1; i < populationSize; ++i) {
		std::shuffle(firstSolution.begin() + 1, firstSolution.end() - 1, g);
		population.push_back(make_pair(firstSolution, 0));
	}
}

void GeneticAlgorithm::calculateFitness()
{
	for (int i = 0; i < population.size(); ++i) {
		int sum = 0;
		vector<int> solution = population[i].first;
		for (int j = 0; j < solution.size() - 1; ++j) {
			sum += graph[solution.at(j)][solution.at(j + 1)];
		}
		population.at(i).second = sum; //przypisanie wartosci fitness
	}
}

void GeneticAlgorithm::inversionMutation(std::vector<int>& solution)
{
	int firstIndex = (rand() % (graph.size() - 1)) + 1;
	int secondIndex = (rand() % (graph.size() - 1)) + 1;
	while (secondIndex == firstIndex) {
		secondIndex = (rand() % (graph.size() - 1)) + 1;
	}
	//chcemy zeby zawsze firstindex byl przed secondindex
	if (firstIndex > secondIndex) {
		int helper = secondIndex;
		secondIndex = firstIndex;
		firstIndex = helper;
	}
	std::reverse(solution.begin() + firstIndex, solution.begin() + secondIndex);
}

void GeneticAlgorithm::pmx(std::vector<int>& firstParent, std::vector<int>& secondParent)
{
	int firstIndex = (rand() % (graph.size() - 1)) + 1;
	int secondIndex = (rand() % (graph.size() - 1)) + 1;
	while (secondIndex == firstIndex) {
		secondIndex = (rand() % (graph.size() - 1)) + 1;
	}
	//chcemy zeby zawsze firstindex byl przed secondindex
	if (firstIndex > secondIndex) {
		int helper = secondIndex;
		secondIndex = firstIndex;
		firstIndex = helper;
	}
	int savedFirstIndex = firstIndex;
	int savedSecondIndex = secondIndex;
	//mapujemy wierzcholki
	vector<int> firstMap;
	firstMap.resize(secondParent.size());
	vector<int> secondMap;
	secondMap.resize(firstParent.size());
	for (int i = 0; i < secondParent.size(); ++i) {
		firstMap[i] = secondParent[i];
	}
	for (int i = 0; i < firstParent.size(); ++i) {
		secondMap[i] = firstParent[i];
	}
	//potomek
	vector<int> child;
	child.resize(graph.size() + 1);
	child[0] = 0;
	child[child.size() - 1] = 0;
	//kopiujemy czesc rodzica do potomka
	copy(firstParent.begin() + firstIndex, firstParent.begin() + secondIndex + 1, child.begin() + firstIndex);
	//zczytujemy jakie wierzcholki juz dodalismy
	vector<int> alreadyAdded;
	for (int i = firstIndex; i <= secondIndex; ++i) {
		alreadyAdded.push_back(firstParent.at(i));
	}
	secondIndex++;
	while (alreadyAdded.size() != child.size() - 2) {
		if (secondIndex >= secondParent.size() - 1) {
			secondIndex = 1;
		}
		//jesli nie ma nalozenia
		if (std::find(begin(alreadyAdded), end(alreadyAdded), secondParent.at(secondIndex)) == end(alreadyAdded)) {
			child[secondIndex] = secondParent[secondIndex];
			alreadyAdded.push_back(secondParent[secondIndex]);
			secondIndex++;
		}
		//jesli jest nalozenie musimy znalezc liczbe do umieszczenia w tym miejscu
		else {
			//znajdujemy liczbe ktora trzeba wstawic
			int helper = secondIndex;
			while (true) {
				auto it = std::find(begin(secondMap), end(secondMap), secondParent.at(helper));
				int index = std::distance(secondMap.begin(), it);
				if (std::find(begin(alreadyAdded), end(alreadyAdded), secondParent.at(index)) == end(alreadyAdded)) {
					child[secondIndex] = secondParent.at(index);
					alreadyAdded.push_back(secondParent.at(index));
					secondIndex++;
					break;
				}
				else {
					helper = index;
				}
			}
		}
	}
	vector<int> firstChild = child;
	firstIndex = savedFirstIndex;
	secondIndex = savedSecondIndex;
	child.clear();
	child.resize(graph.size() + 1);
	child[0] = 0;
	child[child.size() - 1] = 0;
	//kopiujemt czesc rodzica do potomka
	copy(secondParent.begin() + firstIndex, secondParent.begin() + secondIndex + 1, child.begin() + firstIndex);
	//zczytujemy jakie wierzcholki juz dodalismy
	alreadyAdded.clear();
	for (int i = firstIndex; i <= secondIndex; ++i) {
		alreadyAdded.push_back(secondParent.at(i));
	}
	secondIndex++;
	while (alreadyAdded.size() != child.size() - 2) {
		if (secondIndex >= firstParent.size() - 1) {
			secondIndex = 1;
		}
		//jesli nie ma nalozenia
		if (std::find(begin(alreadyAdded), end(alreadyAdded), firstParent.at(secondIndex)) == end(alreadyAdded)) {
			child[secondIndex] = firstParent[secondIndex];
			alreadyAdded.push_back(firstParent[secondIndex]);
			secondIndex++;
		}
		//jesli jest nalozenie musimy znalezc liczbe do umieszczenia w tym miejscu
		else {
			//znajdujemy liczbe ktora trzeba wstawic
			int helper = secondIndex;
			while (true) {
				auto it = std::find(begin(firstMap), end(firstMap), firstParent.at(helper));
				int index = std::distance(firstMap.begin(), it);
				if (std::find(begin(alreadyAdded), end(alreadyAdded), firstParent.at(index)) == end(alreadyAdded)) {
					child[secondIndex] = firstParent.at(index);
					alreadyAdded.push_back(firstParent.at(index));
					secondIndex++;
					break;
				}
				else {
					helper = index;
				}
			}
		}
	}
	firstParent = firstChild;
	secondParent = child;
}

void GeneticAlgorithm::ox(std::vector<int>& firstParent, std::vector<int>& secondParent)
{
	int firstIndex = (rand() % (graph.size() - 1)) + 1;
	int secondIndex = (rand() % (graph.size() - 1)) + 1;
	while (secondIndex == firstIndex) {
		secondIndex = (rand() % (graph.size() - 1)) + 1;
	}
	//chcemy zeby zawsze firstindex byl przed secondindex
	if (firstIndex > secondIndex) {
		int helper = secondIndex;
		secondIndex = firstIndex;
		firstIndex = helper;
	}
	int savedFirstIndex = firstIndex;
	int savedSecondIndex = secondIndex;
	//potomek
	vector<int> child;
	child.resize(graph.size() + 1);
	child[0] = 0;
	child[child.size() - 1] = 0;
	//kopiujemt czesc rodzica do potomka
	copy(firstParent.begin() + firstIndex, firstParent.begin() + secondIndex + 1, child.begin() + firstIndex);
	//zczytujemy jakie wierzcholki juz dodalismy
	vector<int> alreadyAdded;
	for (int i = firstIndex; i <= secondIndex; ++i) {
		alreadyAdded.push_back(firstParent.at(i));
	}
	secondIndex++;
	int childIndex = secondIndex;
	while (alreadyAdded.size() != child.size() - 2) {
		if (secondIndex >= secondParent.size() - 1) {
			secondIndex = 1;
		}
		if (childIndex >= child.size() - 1) {
			childIndex = 1;
		}
		if (std::find(begin(alreadyAdded), end(alreadyAdded), secondParent.at(secondIndex)) == end(alreadyAdded)) {
			child[childIndex] = secondParent[secondIndex];
			alreadyAdded.push_back(secondParent[secondIndex]);
			childIndex++;
		}
		secondIndex++;
	}
	vector<int> firstChild = child;
	firstIndex = savedFirstIndex;
	secondIndex = savedSecondIndex;
	child.clear();
	child.resize(graph.size() + 1);
	child[0] = 0;
	child[child.size() - 1] = 0;
	//kopiujemt czesc rodzica do potomka
	copy(secondParent.begin() + firstIndex, secondParent.begin() + secondIndex + 1, child.begin() + firstIndex);
	//zczytujemy jakie wierzcholki juz dodalismy
	alreadyAdded.clear();
	for (int i = firstIndex; i <= secondIndex; ++i) {
		alreadyAdded.push_back(secondParent.at(i));
	}
	secondIndex++;
	childIndex = secondIndex;
	while (alreadyAdded.size() != child.size() - 2) {
		if (secondIndex >= firstParent.size() - 1) {
			secondIndex = 1;
		}
		if (childIndex >= child.size() - 1) {
			childIndex = 1;
		}
		if (std::find(begin(alreadyAdded), end(alreadyAdded), firstParent.at(secondIndex)) == end(alreadyAdded)) {
			child[childIndex] = firstParent[secondIndex];
			alreadyAdded.push_back(firstParent[secondIndex]);
			childIndex++;
		}
		secondIndex++;
	}
	firstParent = firstChild;
	secondParent = child;
}

static bool comparator(const std::pair<vector<int>, int>& a, const std::pair<vector<int>, int>& b)
{
	return (a.second < b.second);
}

void GeneticAlgorithm::geneticAlgorithm(AdjacencyMatrix& passedGraph, int populationSize, double crossoverProbability, double mutationProbability,
	int stopCondition, std::string crossoverMethod, std::string mutationMethod)
{
	this->populationSize = populationSize;
	this->graph = passedGraph.graph;
	srand(time(NULL));
	std::random_device rd;
	std::mt19937 mt(rd());
	// tworzymy pierwsza populacje
	createFirstPopulation();
	timer.start();
	int second = 0;
	//int minimum = INT_MAX;
	while (timer.getSeconds() < stopCondition) {
		//czyscimy nastepna populacje
		nextPopulation.clear();
		//liczymy fitness 
		calculateFitness();
		//bierzemy najlepsze rozwiazanie dalej (elitism)
		nextPopulation.push_back(*std::min_element(population.begin(), population.end(), [](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; }));
		//metoda ruletki
		//obliczamy sume fitness
		int fitnessSum = 0;
		for (int i = 0; i < population.size(); ++i) {
			fitnessSum += population[i].second;
		}
		//wype³niamy tablice probability
		vector<double> probability;
		probability.resize(population.size());
		for (int i = 0; i < population.size(); ++i) {
			probability[i] = population[i].second / static_cast<double>(fitnessSum);
		}
		while (nextPopulation.size() < populationSize) {
			//wybieramy losowo 2 osobników
			vector<int> pickedSolutionsIndex;
			for (int i = 0; i < 2; ++i) {
				double helper = 0;
				std::uniform_real_distribution<double> dist(0.0, 1.0);
				int random = dist(mt);
				for (int j = 0; j < population.size(); j++) {
					helper += (1 - probability[i]) / (population.size() - 1);
					if (random < helper) {
						if (i == 1 && pickedSolutionsIndex[0] == j) continue;
						pickedSolutionsIndex.push_back(j);
						break;
					}
				}
			}
			vector<int> firstParent = population.at(pickedSolutionsIndex.at(0)).first;
			vector<int> secondParent = population.at(pickedSolutionsIndex.at(1)).first;
			//sprawdzamy czy dochodzi do krzyzowania
			std::uniform_real_distribution<double> dist(0.0, 1.0);
			if (crossoverMethod.compare("brak") != 0) {
				if (dist(mt) < crossoverProbability) {
					if (crossoverMethod.compare("pmx") == 0) pmx(firstParent, secondParent);
					else if (crossoverMethod.compare("ox") == 0) ox(firstParent, secondParent);
				}
			}
			//sprawdzamy czy dochodzi do mutacji
			if ((mutationMethod.compare("brak") != 0)) {
				if (dist(mt) < mutationProbability) {
					if (mutationMethod.compare("inverse") == 0) {
						inversionMutation(firstParent);
						inversionMutation(secondParent);
					}
				}
			}
			//dodajemy pare
			nextPopulation.push_back(make_pair(firstParent, 0));
			nextPopulation.push_back(make_pair(secondParent, 0));
		}
		//zastepujemy populacje
		population = nextPopulation;
	}
	calculateFitness();
	pair<vector<int>, int> solution = *std::min_element(population.begin(), population.end(), [](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; });
	cout << "KONIEC ALGORYTMU \n";
	cout << "KOSZT SCIEZKI: " << solution.second << "\n";
	cout << "Sciezka: " << "\n";
	for (int vertice : solution.first) {
		cout << vertice << " -> ";
	}
}
