#include "Menu.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

void Menu::waitingScreen()
{
	cout << endl << "Wprowadz dowolna liczbe zeby kontynuowac" << endl;
	int input;
	cin >> input;
}

Menu::Menu()
{
	bool running = true;
	while (running) {
		system("cls");
		cout << "ZADANIE PROJEKTOWE NR 1" << endl;
		cout << "1. Wczytaj z pliku" << endl;
		cout << "2. Wyswietl macierz sasiedztwa" << endl;
		cout << "3. Symulowane wyzarzanie" << endl;
		cout << "4. TabuSearch" << endl;
		cout << "5. Ustaw kryterium stopu" << endl;
		cout << "6. Ustaw parametry algorytmu SA" << endl;
		cout << "7. Testy" << endl;
		cout << "8. Wyjdz" << endl;

		cout << "Wprowadz swoj wybor: ";
		int choice;
		cin >> choice;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			system("cls");
			cout << endl << "Wprowadz liczbe calkowita!";
			waitingScreen();
			continue;
		}
		else
			try {
			switch (choice) {
			case 1:
			{
				if (graph) delete graph;
				cout << "Podaj nazwe pliku (z rozszerzeniem)" << endl;
				string filename;
				cin >> filename;
				try {
					graph = new AdjacencyMatrix();
					graph->createFromFile(filename);
				}
				catch (string e) {
					delete graph;
					graph = nullptr;
					cout << endl << "Wczytanie nie powiodlo sie. Informacja: ";
					cout << endl << e;
					waitingScreen();
					continue;
				}
				cout << "Graf gotowy!";
				waitingScreen();
				break;
			}
			case 2:
				if (graph) {
					system("cls");
					graph->printGraph();
					waitingScreen();
				}
				else throw string("Najpierw wczytaj graf");
				break;
			case 3:
				if (graph) {
					sa = new SimulatedAnnealing();
					system("cls");
					timer.start();
					sa->simulatedAnnealing(*graph, stopCondition, startingTemperature, coolingRatio);
					timer.stop();
					timer.printResult();
					delete sa;
					waitingScreen();
				}
				else throw string("Najpiew wczytaj graf");
				break;
			case 4:
				if (graph) {
					ts = new TabuSearch();
					system("cls");
					timer.start();
					ts->tabuSearch(*graph, stopCondition);
					timer.stop();
					timer.printResult();
					delete ts;
					waitingScreen();
				}
				else throw string("Najpiew wczytaj graf");
				break;
			case 5:
				if (graph) {
					cin >> this->stopCondition;
				}
				else throw string("Najpiew wczytaj graf");
				break;
			case 6:
				if (graph) {
					system("cls");
					cout << "Podaj temperature poczatkowa: " << endl;
					cin >> this->startingTemperature;
					cout << endl << "Podaj wspolczynnik redukcji: " << endl;
					cin >> this->coolingRatio;
				}
				else throw string("Najpiew wczytaj graf");
				break;
			case 7:
			{
				/*if (graph) {
				system("cls");
				std::ofstream file;
				cout << "Przeprowadzanie testow...";
				//wykonujemy 5 pomiarów i zapisujemy do pliku œredni¹
				int result;
				for (int i = 0; i < 5; ++i) {
					if (i == 0) stopCondition = 20;
					if (i == 1) stopCondition = 30;
					if (i == 2) stopCondition = 40;
					if (i == 3) stopCondition = 50;
					if (i == 4) stopCondition = 60;
					for (int j = 0; j < 5; j++) {
						sa = new SimulatedAnnealing();
						startingTemperature = 1000;
						coolingRatio = 0.99;
						result = sa->simulatedAnnealing(*graph, stopCondition, startingTemperature, coolingRatio);
						delete sa;
						file.open("SA" + std::to_string(stopCondition) + "_" + std::to_string(startingTemperature) + "_" + std::to_string(coolingRatio) + ".txt", std::ios_base::app);
						file << result << '\n';
						file.close();
						sa = new SimulatedAnnealing();
						startingTemperature = 1000;
						coolingRatio = 0.97;
						result = sa->simulatedAnnealing(*graph, stopCondition, startingTemperature, coolingRatio);
						delete sa;
						file.open("SA" + std::to_string(stopCondition) + "_" + std::to_string(startingTemperature) + "_" + std::to_string(coolingRatio) + ".txt", std::ios_base::app);
						file << result << '\n';
						file.close();
						sa = new SimulatedAnnealing();
						startingTemperature = 100000;
						coolingRatio = 0.99;
						result = sa->simulatedAnnealing(*graph, stopCondition, startingTemperature, coolingRatio);
						delete sa;
						file.open("SA" + std::to_string(stopCondition) + "_" + std::to_string(startingTemperature) + "_" + std::to_string(coolingRatio) + ".txt", std::ios_base::app);
						file << result << '\n';
						file.close();
						sa = new SimulatedAnnealing();
						startingTemperature = 100000;
						coolingRatio = 0.97;
						result = sa->simulatedAnnealing(*graph, stopCondition, startingTemperature, coolingRatio);
						delete sa;
						file.open("SA" + std::to_string(stopCondition) + "_" + std::to_string(startingTemperature) + "_" + std::to_string(coolingRatio) + ".txt", std::ios_base::app);
						file << result << '\n';
						file.close();
						sa = new SimulatedAnnealing();
						startingTemperature = 10000000;
						coolingRatio = 0.99;
						result = sa->simulatedAnnealing(*graph, stopCondition, startingTemperature, coolingRatio);
						delete sa;
						file.open("SA" + std::to_string(stopCondition) + "_" + std::to_string(startingTemperature) + "_" + std::to_string(coolingRatio) + ".txt", std::ios_base::app);
						file << result << '\n';
						file.close();
						sa = new SimulatedAnnealing();
						startingTemperature = 10000000;
						coolingRatio = 0.97;
						result = sa->simulatedAnnealing(*graph, stopCondition, startingTemperature, coolingRatio);
						delete sa;
						file.open("SA" + std::to_string(stopCondition) + "_" + std::to_string(startingTemperature) + "_" + std::to_string(coolingRatio) + ".txt", std::ios_base::app);
						file << result << '\n';
						file.close();
						ts = new TabuSearch();
						result = ts->tabuSearch(*graph, stopCondition);
						delete ts;
						file.open("TS" + std::to_string(stopCondition) + ".txt", std::ios_base::app);
						file << result << '\n';
						file.close();
					}
				}
				}
				else throw string("Najpiew wczytaj graf");*/
				break;

			}

			case 8: {
				running = false;
				break;
			}
			default:
				throw string("Niedostepna funkcja");
			}
		}
		catch (string e) {
			system("cls");
			cout << endl << e;
			waitingScreen();
		}
	}

}
