#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <regex>
#include "FileReadError.h"
#include "ConstructorError.h"

class KnapsackProblem
{
public:
	//constructors
	KnapsackProblem(const std::string& fileName);
	KnapsackProblem(int numOfItems, double SizeOfKnapsack, const std::vector<double>& WeightsVector, const std::vector<double>& ValuesVector);
	KnapsackProblem(const KnapsackProblem& other);
	KnapsackProblem(KnapsackProblem&& other) noexcept;
	~KnapsackProblem();

	//operators
	KnapsackProblem& operator=(const KnapsackProblem& other);
	KnapsackProblem& operator=(KnapsackProblem&& other) noexcept;

	//methods
	int valueSolution(std::vector<int> &genotype);
	void loadFromFile(const std::string& fileName);
	void displaySolution(std::vector<int> bestGenotype);
	int getItemsCount();
	std::vector<double>& getWeights();
	std::vector<double>& getValues();
	int getKnapsackSize();

private:
	int itemsCount;
	int bestValue;
	double knapsackSize;
	std::vector<double> weights;
	std::vector<double> values;
};