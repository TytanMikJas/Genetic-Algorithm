#pragma once
#include "RandomNumberGenerator.h"
#include "ConstructorError.h"
#include <vector>
#include <iostream>
#include <string>

class Individual
{
public:
	//constructors
	Individual();
	Individual(int vectorSize);
	Individual(const Individual &other);
	Individual(Individual&& other) noexcept;
	~Individual();

	//operators
	Individual& operator = (const Individual& other);
	Individual& operator = (Individual&& other) noexcept;

	//methods
	void calculateFitness(const std::vector<double> &values,const std::vector<double> &weights,const int knapsackSize);
	void mutate(float probability);
	std::vector<Individual> crossover(Individual &other);
	std::vector<int>& getGenotype();
	void randomizeGenotype();
	void setGenotype(std::vector<int> &newGenotype);
	int getFitness();

private:
	std::vector<int> genotype;
	int fitness;
	RandomNumberGenerator rng;
};                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           