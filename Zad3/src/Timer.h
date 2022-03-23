#pragma once
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>

//Klasa zawieraj¹ca metody realizuj¹ce pomiar czasu

class Timer
{
private:
	std::chrono::high_resolution_clock::time_point t1, t2; //punkt startowy i koncowy pomiaru

public:
	long long time;
	void start(); //uruchom zegar
	void stop(); //zatrzymaj zegar
	void printResult(); //wyswietl zmierzony czas
	void printToFile(std::ofstream&);
	double getSeconds();
};

