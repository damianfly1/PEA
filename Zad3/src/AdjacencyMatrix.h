#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

//Klasa kt�rej obiekt przechowuje graf w postaci macierzy s�siedztwa

class AdjacencyMatrix
{
private:
	bool file_read_line(std::ifstream& file, std::vector<int>&, int size); //metoda pomocnicza przy wczytywaniu grafu z pliku

public:
	std::vector<std::vector<int>> graph; //macierz s�siedztwa
	int graphSize; //rozmiar macierzy
	void printGraph(); //metoda wy�wietlaj�ca macierz s�siedztwa
	void createFromFile(std::string); //metoda wczytuj�ca macierz z pliku
	void generateRandom(int size); //metoda tworz�ca losow� macierz o podanym rozmiarze
	~AdjacencyMatrix();
};

