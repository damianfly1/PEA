#include "AdjacencyMatrix.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::vector;

bool AdjacencyMatrix::file_read_line(ifstream& file, vector<int> &vec, int size)
{
	string s;
	getline(file, s);
	vec.clear();
	vec.reserve(size);
	if (file.fail() || s.empty())
		return(false);
	std::stringstream in_ss(s);
	int number;
	for (int i = 0; i < size; i++) {
		in_ss >> number;
		vec.push_back(number);
		if (in_ss.fail())
			return(false);
	}
	return(true);
}

void AdjacencyMatrix::generateRandom(int size)
{
	srand(time(NULL));
	this->graphSize = size;
	graph.resize(size, vector< int>(size));
	for (int i = 0; i < graph.size(); i++)
	{
		for (int j = 0; j < graph[i].size(); j++)
		{
			if (i == j) graph[i][j] = 0;
			else graph[i][j] = rand() % (INT_MAX - 1) + 1;
		}
	}
}

AdjacencyMatrix::~AdjacencyMatrix()
{
	std::vector<std::vector<int>>().swap(graph);
}

void AdjacencyMatrix::printGraph()
{
	for (int i = 0; i < graph.size(); i++)
	{
		for (int j = 0; j < graph[i].size(); j++)
		{
			cout << graph[i][j] << " ";
		}
		cout << endl;
	}
}

void AdjacencyMatrix::createFromFile(string filename)
{
		ifstream file;
		file.open(filename);
		vector<int> helper;
		if (file.is_open())
		{
			if (file_read_line(file, helper, 1))
			{
				this->graphSize = helper.at(0);
				graph.resize(graphSize, vector< int>(graphSize));
				for (int i = 0; i < this->graphSize; i++)
					if (file_read_line(file, helper, graphSize))
					{
						for (int j = 0; j < graphSize; j++) {
							graph[i][j] = helper.at(j);
						}
					}
					else
					{
						throw string("File error - READ EDGE");
						break;
					}
			}
			else
				throw string("File error - READ INFO");
			file.close();
		}
		else
			throw string("File error - OPEN");
}
