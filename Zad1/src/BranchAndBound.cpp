#include "BranchAndBound.h"

using std::vector;
using std::cout;
using std::endl;


bool BranchAndBound::generateNextVertice(BBvertice start, int end)
{
	vector<vector< int>> newMatrix = start.matrix; //matryca któr¹ bedziemy redukowaæ
	int size = newMatrix.size();
	bool isALeaf = false;
	//nie chcemy wracac do wierzcholka startowego i juz odwiedzonych
	for (int vertice : start.visitedVertices) {
		newMatrix[end][vertice] = -1;
	}
	//zerujemy wiersz wierzcholka startowego i kolumne koncowego
	for (int i = 0; i < size; i++) {
		newMatrix[start.realVertice][i] = -1;
		newMatrix[i][end] = -1;
	}
	int currentPos = -1; //obecna pozycja, zaczynamy od -1 bo na poczatku petli zwiekszamy o 1
	int minimum; // minimalny koszt po redukcji wiersza lub kolumny
	int cost = start.cost; //pocz¹tkowy koszt 
	//sprawdzamy czy macierz jest zredukowana, jesli nie to redukujemy
	//WIERSZE
	while (currentPos != (size- 1)) {
		currentPos++;
		minimum = INT_MAX;
		for (int j = 0; j < size; ++j) {
			//jesli wiersz jest zredukowany przechodzimy do nastepnego
			if ((newMatrix[currentPos][j] == 0)) break;
			//znajdujemy minimum w wierszu
			if ((newMatrix[currentPos][j] < minimum) && (newMatrix[currentPos][j] != -1)) minimum = newMatrix[currentPos][j];
			//jesli doszlismy do konca wiersza
			if (j == (size - 1) && (minimum != INT_MAX)) {
				//koszt = koszt+minimum z danego wiersza
				cost += minimum;
				//redukujemy wiersz
				if (cost >= upperBound) return false;
				for (int k = 0; k < size; k++) {
					if (k == currentPos || (newMatrix[currentPos][k] == (-1))) continue;
					newMatrix[currentPos][k] -= minimum;
				}
			}
		}
	}
	currentPos = -1;
	//KOLUMNY
	//analogicznie jak w przypadku wierszy, jedynie odwrócone indeksy
	while (currentPos != (size - 1)) {
		currentPos++;
		minimum = INT_MAX;
		for (int j = 0; j < size; ++j) {
			if ((newMatrix[j][currentPos] == 0)) break;
			if ((newMatrix[j][currentPos] < minimum) && (newMatrix[j][currentPos] != -1)) minimum = newMatrix[j][currentPos];
			if (j == (size - 1) && (minimum != INT_MAX)) {
				cost += minimum;
				if (cost >= upperBound) return false;
				for (int k = 0; k < size; k++) {
					if ((k == currentPos) || (newMatrix[k][currentPos] == (-1))) continue;
					newMatrix[k][currentPos] -= minimum;
				}
			}
		}
	}
	//trzeba zwiekszyc koszt o koszt przejœcia ze starego wierzcho³ka do obecnego
	cost += start.matrix[start.realVertice][end];
	//jeœli koszt przekracza górn¹ granicê nie chcemy go zapamiêtywaæ
	if (cost >= upperBound) return false;
	//vector z wierzcho³kami mo¿liwymi do odwiedzenia
	vector< int> newAvaiableVertices;
	//jeœli jest to ostatni mo¿liwy wierzcho³ek znaleŸliœmy liœæ
	if (start.avaiableVertices.size() == 1) isALeaf = true;
	//w innym wypadku kopiujemy wierzcho³ki z porzedniego wierzcho³ka - obecny wierzcho³ek
	else {
		for (int i = 0; i < start.avaiableVertices.size(); ++i) {
			if(start.avaiableVertices.at(i) != end) newAvaiableVertices.push_back(start.avaiableVertices.at(i));
		}
	}
	//do odwiedzonych wierzcho³ków dodajemy obecny
	vector< int> visitedVertices = start.visitedVertices;
	visitedVertices.push_back(end);
	//tworzymy nowy BBVertice
	BBvertice temp = BBvertice(newMatrix, cost, end, newAvaiableVertices, visitedVertices, visitedVertices.size());
	//jeœli nie znaleŸliœmy liœcia dodajemy wierzcho³ek do kolejki
	if (!isALeaf) bbVertices.push(temp);
	//w innym wypadku ustawiamy leafVertice na obecny wierzcho³ek
	else leafVertice = temp;
	//zwracamy informacjê o tym czy znaleŸliœmy liœæ
	return isALeaf;
}

void BranchAndBound::createFirstMatrix(std::vector<std::vector<int>> &graph)
{
	//przechodzimy po kolei wszystkie wiersze i zamieniamy 0 na -1
	for (int i = 0; i < graph.size(); i++)
	{
		for (int j = 0; j < graph[i].size(); j++)
		{
			if (i == j) graph[i][j] = -1;
		}
	}
	int size = graph.size();
	int currentPos = -1;
	int minimum;
	int cost = 0;
	//sprawdzamy czy macierz jest zredukowana, jesli nie to redukujemy
	//WIERSZE
	while (currentPos != (size - 1)) {
		currentPos++;
		minimum = INT_MAX;
		for (int j = 0; j < size; ++j) {
			//jesli wiersz jest zredukowany przechodzimy do nastepnego
			if ((graph[currentPos][j] == 0)) break;
			if ((graph[currentPos][j] < minimum) && (graph[currentPos][j] != -1)) minimum = graph[currentPos][j];
			//jesli doszlismy do konca wiersza
			if (j == (size - 1) && (minimum != INT_MAX)) {
				cost += minimum;
				for (int k = 0; k < size; k++) {
					if (k == currentPos || (graph[currentPos][k] == (-1))) continue;
					graph[currentPos][k] -= minimum;
				}
			}
		}
	}
	currentPos = -1;
	//KOLUMNY
	while (currentPos != (size - 1)) {
		currentPos++;
		minimum = INT_MAX;
		for (int j = 0; j < size; ++j) {
			if ((graph[j][currentPos] == 0)) break;
			if ((graph[j][currentPos] < minimum) && (graph[j][currentPos] != -1)) minimum = graph[j][currentPos];
			if (j == (size - 1) && (minimum != INT_MAX)) {
				cost += minimum;
				for (int k = 0; k < size; k++) {
					if ((k == currentPos) || (graph[k][currentPos] == (-1))) continue;
					graph[k][currentPos] -= minimum;
				}
			}
		}
	}
	//tworzymy pierwszy BBVertice
	vector<int> avaiableVertices;
	for (int i = 1; i < size; i++) {
		avaiableVertices.push_back(i);
	}
	vector< int> visitedVertices;
	visitedVertices.push_back(0);
	bbVertices.push(BBvertice(graph, cost, 0, avaiableVertices, visitedVertices, visitedVertices.size()));
}

void BranchAndBound::branchAndBround(AdjacencyMatrix graph)
{
	upperBound = INT_MAX; //pocz¹tkowa górna granica
	createFirstMatrix(graph.graph);
	bool finished = false; 
	bool flag = false; 
	//g³ówna pêtla: dopóki nie znajdziemy najlepszej górnej granicy rozpatrujemy pozosta³e wierzcho³ki
	while (!finished) {
		//jeœli kolejka jest pusta koñczymy algorytm
		if (bbVertices.empty()) {
			finished = true;
			break;
		}
		//w innym wypadku bierzemy pierwszy wierzcho³ek w kolejce
		else currentVertice = (bbVertices.top());
		//jeœli wierzcho³ek jest wiekszy od upper bound usuwamy go i przechodzimy do nastepnego
		if (currentVertice.cost >= upperBound) {
			bbVertices.pop();
			continue;
		}else bbVertices.pop();
		//sprawdzamy wszystkie wierzcho³ki mo¿liwe do odwiedzenia
		for (int verticeToVisit : currentVertice.avaiableVertices) {
			 flag = generateNextVertice(currentVertice, verticeToVisit);
			 //jeœli doszliœmy do liœcia sprawdzamy obecny upperBound
			 if (flag) {
				 if((leafVertice.cost) < upperBound)
				 upperBound = (leafVertice.cost);
			 }
		}
	}
	cout << "WYNIKI BRANCH & BOUND" << endl;
	cout << "NAJKROTSZA DROGA: " << upperBound << endl;
	cout << "SCIEZKA: ";
	for (int visitedVertice : leafVertice.visitedVertices) {
		cout << visitedVertice << " -> ";
	}
	cout << "0";

}
