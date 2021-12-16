#include "BBvertice.h"

BBvertice::BBvertice(std::vector<std::vector<int>> matrix, int cost, int realVertice, std::vector<int> avaiableVertices, std::vector<int> visitedVertices, int priority)
{
	this->matrix = matrix;
	this->cost = cost;
	this->realVertice = realVertice;
	this->avaiableVertices = avaiableVertices;
	this->visitedVertices = visitedVertices;
	this->priority = priority;
}

BBvertice::BBvertice()
{
	this->matrix = std::vector<std::vector<int>>{ 0 };
	this->cost = 0;
	this->realVertice = 0;
	this->avaiableVertices = std::vector<int>{ 0 };
	this->visitedVertices = std::vector<int>{ 0 };
	this->priority = 0;
}

BBvertice::~BBvertice()
{
	std::vector<int>().swap(avaiableVertices);
	std::vector<int>().swap(visitedVertices);
	std::vector<std::vector<int>>().swap(matrix);
}
