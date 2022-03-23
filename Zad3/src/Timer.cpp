#include "Timer.h"

void Timer::start()
{
	t1 = std::chrono::high_resolution_clock::now();
}

void Timer::stop()
{
	t2 = std::chrono::high_resolution_clock::now();
	time = (std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1)).count();
}

void Timer::printResult()
{
	std::cout << std::endl;
	std::cout << "Operacja zajela mi " << (std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1)).count() << " mikrosekund" << std::endl;
	std::cout << (std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1)).count() << " milisekund" << std::endl;
	std::cout << (std::chrono::duration_cast<std::chrono::seconds>(t2 - t1)).count() << "sekund" << std::endl;
	std::cout << std::endl;
}

void Timer::printToFile(std::ofstream& file)
{
	file << (std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1)).count() << '\n';
}

double Timer::getSeconds()
{
	return (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - t1)).count();
}
