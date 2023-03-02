#pragma once
#include "Individual.h"
#include "RandomNumberGenerator.h"
#include "KnapsackProblem.h"
#include "ConstructorError.h"
#include <vector>

class GeneticAlgorithm 
{
public:

	//constructors
	GeneticAlgorithm(int populationSize, float mutationProb, float crossoverProb, int stopCriteria);
	GeneticAlgorithm(const GeneticAlgorithm& other);
	GeneticAlgorithm(GeneticAlgorithm&& other) noexcept;
	~GeneticAlgorithm();

	//operators
	GeneticAlgorithm& operator=(const GeneticAlgorithm& other);
	GeneticAlgorithm& operator=(GeneticAlgorithm&& other) noexcept;


	//methods
	void run(KnapsackProblem &problem);

private:

	//methods
	void initializePopulation(KnapsackProblem& problem);
	void evaluatePopulation(KnapsackProblem& problem);
	std::vector<int> selectParents();
	void updatePopulation(std::vector<Individual>& newPopulation);
	void evaluateCrossovers(KnapsackProblem& problem);
	void evaluateMutations();
	void updateBestSolution();
	Individual& getBestSolution();
	std::vector<Individual>& getPopulation();

	int populationSize;
	float mutationProb;
	float crossoverProb;
	int stopCriteria;
	std::vector<Individual> population;
	Individual bestSolution;
	RandomNumberGenerator rng;
};