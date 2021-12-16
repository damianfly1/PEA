#pragma once
#include <vector>

//Klasa której obiekty s¹ wierzcho³kami drzewa reprezentuj¹cego przestrzeñ rozwi¹zañ problemu

class BBvertice
{
public:
	std::vector<std::vector<int>> matrix; //zredukowana macierz
	int cost; //cena redukcji
	int realVertice; //prawdziwy numer wierzcholka
	std::vector<int> avaiableVertices; //pozostale wierzcholki do odwiedzenia z obecnego wierzcholka
	std::vector<int> visitedVertices; //wierzcho³ki ju¿ odwiedzone
	int priority; //priorytet (wysokoœæ wierzcho³ka w drzewie)
	BBvertice(); //konstruktor bez parametrów
	//konstruktor z parametrami
	BBvertice(std::vector<std::vector<int>> matrix, int cost, int realVertice, std::vector<int> avaiableVertices, std::vector<int> visitedVertices, int priority);
	~BBvertice(); //destruktor
};

