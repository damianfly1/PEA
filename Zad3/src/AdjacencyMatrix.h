#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

//Klasa której obiekt przechowuje graf w postaci macierzy s¹siedztwa

class AdjacencyMatrix
{
private:
	bool file_read_line(std::ifstream& file, std::vector<int>&, int size); //metoda pomocnicza przy wczytywaniu grafu z pliku

public:
	std::vector<std::vector<int>> graph; //macierz s¹siedztwa
	int graphSize; //rozmiar macierzy
	void printGraph(); //metoda wyœwietlaj¹ca macierz s¹siedztwa
	void createFromFile(std::string); //metoda wczytuj¹ca macierz z pliku
	void generateRandom(int size); //metoda tworz¹ca losow¹ macierz o podanym rozmiarze
	~AdjacencyMatrix();
};

