#include "Menu.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

void Menu::waitingScreen()
{
	cout << "\n" << "Wprowadz dowolna liczbe zeby kontynuowac" << "\n";
	int input;
	cin >> input;
}

Menu::Menu()
{
	bool running = true;
	while (running) {
		system("cls");
		cout << "ZADANIE PROJEKTOWE NR 3" << "\n";
		cout << "1. Wczytaj z pliku" << "\n";
		cout << "2. Wyswietl macierz sasiedztwa" << "\n";
		cout << "3. Algorytm genetyczny" << "\n";
		cout << "4. Ustaw kryterium stopu (AKTUALNE: " << stopCondition << ")\n";
		cout << "5. Ustaw wielkosc populacji poczatkowej (AKTUALNA: " << populationSize << ")\n";
		cout << "6. Ustaw wspolczynnik krzyzowania (AKTUALNY: " << crossoverProbability << ")\n";
		cout << "7. Ustaw wspolczynnik mutacji (AKTUALNY: " << mutationProbability << ")\n";
		cout << "8. Wybierz metode krzyzowania (AKTUALNA: " << crossoverMethod << ")\n";
		cout << "9. Wybierz metode mutacji (AKTUALNA: " << mutationMethod << ")\n";
		cout << "10. Wyjdz" << "\n";

		cout << "Wprowadz swoj wybor: ";
		int choice;
		cin >> choice;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			system("cls");
			cout << "\n" << "Wprowadz liczbe calkowita!";
			waitingScreen();
			continue;
		}
		else
			try {
			switch (choice) {
			case 1:
			{
				if (graph) delete graph;
				cout << "Podaj nazwe pliku (z rozszerzeniem)" << "\n";
				string filename;
				cin >> filename;
				try {
					graph = new AdjacencyMatrix();
					graph->createFromFile(filename);
				}
				catch (string e) {
					delete graph;
					graph = nullptr;
					cout << "\n" << "Wczytanie nie powiodlo sie. Informacja: ";
					cout << "\n" << e;
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
					ga = new GeneticAlgorithm();
					system("cls");
					cout << "POPULACJA: " << populationSize << "\n";
					cout << "KRZYZOWANIE: " << crossoverMethod << "\n";
					cout << "MUTACJA: " << mutationMethod << "\n";
					cout << "WSPOLCZYNNIK KRZYZOWANIA: " <<crossoverProbability << "\n";
					cout << "WSPOLCZYNNIK MUTACJI: " << mutationProbability << "\n";
					timer.start();
					ga->geneticAlgorithm(*graph, populationSize, crossoverProbability, mutationProbability, stopCondition,
						crossoverMethod, mutationMethod);
					timer.stop();
					timer.printResult();
					delete ga;
					waitingScreen();
				}
				else throw string("Najpiew wczytaj graf");
				break;
			case 4:
				system("cls");
				cout << "Podaj kryterium stopu: " << "\n";
				cin >> this->stopCondition;
				break;
			case 5:
				system("cls");
				cout << "Podaj wielkosc populacji poczatkowej: " << "\n";
				cin >> this->populationSize;
				break;
			case 6:
				system("cls");
				cout << "Podaj wspolczynnik krzyzowania: " << "\n";
				cin >> this->crossoverProbability;
				break;
			case 7:
			{
				system("cls");
				cout << "Podaj wspolczynnik mutacji: " << "\n";
				cin >> this->mutationProbability;
				break;
			}
			case 8:
			{
				system("cls");
				cout << "Wpisz 1 jesli chcesz wylaczyc krzyzowanie\n";
				cout << "Wpisz 2 jesli chcesz wlaczyc operator OX\n";
				cout << "Wpisz 3 jesli chcesz wlaczyc operator PMX\n";
				int input;
				cin >> input;
				if (input == 1) crossoverMethod = "brak";
				else if (input == 2) crossoverMethod = "ox";
				else if (input == 3) crossoverMethod = "pmx";
				break;
			}
			case 9:
			{
				system("cls");
				cout << "Wpisz 1 jesli chcesz wylaczyc mutacje\n";
				cout << "Wpisz 2 jesli chcesz wlaczyc mutacje przez inwersje\n";
				int input;
				cin >> input;
				if (input == 1) mutationMethod = "brak";
				else if (input == 2) mutationMethod = "inverse";
				break;
			}
			case 10: {
				running = false;
				break;
			}
			default:
				throw string("Niedostepna funkcja");
			}
		}
		catch (string e) {
			system("cls");
			cout << "\n" << e;
			waitingScreen();
		}
	}

}

