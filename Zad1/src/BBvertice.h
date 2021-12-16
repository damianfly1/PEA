#pragma once
#include <vector>

//Klasa kt�rej obiekty s� wierzcho�kami drzewa reprezentuj�cego przestrze� rozwi�za� problemu

class BBvertice
{
public:
	std::vector<std::vector<int>> matrix; //zredukowana macierz
	int cost; //cena redukcji
	int realVertice; //prawdziwy numer wierzcholka
	std::vector<int> avaiableVertices; //pozostale wierzcholki do odwiedzenia z obecnego wierzcholka
	std::vector<int> visitedVertices; //wierzcho�ki ju� odwiedzone
	int priority; //priorytet (wysoko�� wierzcho�ka w drzewie)
	BBvertice(); //konstruktor bez parametr�w
	//konstruktor z parametrami
	BBvertice(std::vector<std::vector<int>> matrix, int cost, int realVertice, std::vector<int> avaiableVertices, std::vector<int> visitedVertices, int priority);
	~BBvertice(); //destruktor
};

