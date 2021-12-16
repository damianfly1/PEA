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
		cout << "3. Brute Force" << endl;
		cout << "4. Branch & Bound" << endl;
		cout << "5. Dynamic Programming" << endl;
		cout << "6. Szybki test" << endl;
		cout << "7. Testy" << endl;
		cout << "8. Wyjdz" << endl;

		cout << "Wprowadz swoj wybor: ";
		int choice;
		cin >> choice;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
					bf = new BruteForce();
					system("cls");
					timer.start();
					bf->bruteForce(*graph);
					timer.stop();
					timer.printResult();
					delete bf;
					waitingScreen();
				}
				else throw string("Najpiew wczytaj graf");
				break;
			case 4:
				if (graph) {
					bb = new BranchAndBound();
					system("cls");
					timer.start();
					bb->branchAndBround(*graph);
					timer.stop();
					timer.printResult();
					delete bb;
					waitingScreen();
				}
				else throw string("Najpiew wczytaj graf");
				break;
			case 5:
				if (graph) {
					dp = new DynamicProgramming();
					system("cls");
					timer.start();
					dp->dynamicProgramming(*graph);
					timer.stop();
					timer.printResult();
					delete dp;
					waitingScreen();
				}
				else throw string("Najpierw wczytaj graf");
				break;
			case 6:
				if (graph) delete graph;
				graph = new AdjacencyMatrix();
				int input;
				cout << "Podaj rozmiar grafu" << endl;
				cin >> input;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					cout << endl << "Wprowadz liczbe calkowita!";
					delete graph;
					graph = nullptr;
					waitingScreen();
					continue;
				}
				graph->generateRandom(input);
					system("cls");
					/*bf = new BruteForce();
					timer.start();
					bf->bruteForce(*graph);
					timer.stop();
					timer.printResult();
					delete bf;*/
					bb = new BranchAndBound();
					timer.start();
					bb->branchAndBround(*graph);
					timer.stop();
					timer.printResult();
					delete bb;
					dp = new DynamicProgramming();
					timer.start();
					dp->dynamicProgramming(*graph);
					timer.stop();
					timer.printResult();
					delete dp;
					waitingScreen();
				break;
			case 7: {
				system("cls");
				std::ofstream file;
				cout << "Przeprowadzanie testow...";
				//100 razy generujemy losowe instancje
				for (int i = 0; i < 100; i++) {
					//bf, bb, dp dla wierzcho³ków 6-12
					for (int j =6; j < 13; j++) {
						graph = new AdjacencyMatrix();
						graph->generateRandom(j);
						bf = new BruteForce();
						timer.start();
						bf->bruteForce(*graph);
						timer.stop();
						file.open("bruteForce" + std::to_string(j) + ".txt", std::ios_base::app);
						timer.printToFile(file);
						file.close();
						delete bf;
						bb = new BranchAndBound();
						timer.start();
						bb->branchAndBround(*graph);
						timer.stop();
						file.open("branchAndBound" + std::to_string(j) + ".txt", std::ios_base::app);
						timer.printToFile(file);
						file.close();
						delete bb;
						dp = new DynamicProgramming();
						timer.start();
						dp->dynamicProgramming(*graph);
						timer.stop();
						timer.stop();
						file.open("heldKarp" + std::to_string(j) + ".txt", std::ios_base::app);
						timer.printToFile(file);
						file.close();
						delete dp;
						delete graph;
						graph = nullptr;
					}
					//bb i dp dla wierzcho³ków 13-18
					for (int j = 13; j < 19; j++) {
						graph = new AdjacencyMatrix();
						graph->generateRandom(j);
						bb = new BranchAndBound();
						timer.start();
						bb->branchAndBround(*graph);
						timer.stop();
						file.open("branchAndBound" + std::to_string(j) + ".txt", std::ios_base::app);
						timer.printToFile(file);
						file.close();
						delete bb;
						dp = new DynamicProgramming();
						timer.start();
						dp->dynamicProgramming(*graph);
						timer.stop();
						timer.stop();
						file.open("heldKarp" + std::to_string(j) + ".txt", std::ios_base::app);
						timer.printToFile(file);
						file.close();
						delete dp;
						delete graph;
						graph = nullptr;
					}
				}
				//file.close();
				break; 
			}
			case 8:
				running = false;
				break;
			default:
				throw string("Niedostepna funkcja");
			}
		}
		catch (string e) {
			cout << endl << e;
			waitingScreen();
		}
	}
	
}
