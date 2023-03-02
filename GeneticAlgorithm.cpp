#include "GeneticAlgorithm.h"
#include <random>

//Parametrized constructor
GeneticAlgorithm::GeneticAlgorithm(int populationS, float mutationP, float crossoverP, int stopCrit)
{
    if (populationS <= 0) {
        throw ConstructorError("Invalid input for populationSize in GeneticAlgorithm\nExpected: natural Integer\nProvided: " + std::to_string(populationS));
    }
    else if (mutationP < 0 || mutationP > 1) {
        throw ConstructorError("Invalid input for mutationProb in GeneticAlgorithm\nExpected: Double between 0 and 1\nProvided: " + std::to_string(mutationP));
    }
    else if (crossoverP < 0 || crossoverP > 1) {
        throw ConstructorError("Invalid input for crossoverProb in GeneticAlgorithm\nExpected: Double between 0 and 1\nProvided: " + std::to_string(crossoverP));
    }
    else if (stopCrit <= 0) {
        throw ConstructorError("Invalid input for stopCriteria in GeneticAlgorithm\nExpected: Natural Integer");
    }
    populationSize = populationS;
    mutationProb = mutationP;
    crossoverProb = crossoverP;
    stopCriteria = stopCrit;
    population = std::vector<Individual>();
    bestSolution = Individual(populationS);
    rng = RandomNumberGenerator();
}

// Copy constructor
GeneticAlgorithm::GeneticAlgorithm(const GeneticAlgorithm& other)
{
    populationSize = other.populationSize;
    mutationProb = other.mutationProb;
    crossoverProb = other.crossoverProb;
    stopCriteria = other.stopCriteria;
    population = other.population;
    bestSolution = other.bestSolution;
    rng = other.rng;
}

// Move constructor
GeneticAlgorithm::GeneticAlgorithm(GeneticAlgorithm&& other) noexcept 
{
    populationSize = other.populationSize;
    mutationProb = other.mutationProb;
    crossoverProb = other.crossoverProb;
    stopCriteria = other.stopCriteria;
    population = move(other.population);
    bestSolution = std::move(other.bestSolution);
    rng = std::move(other.rng);
}

// Destructor
GeneticAlgorithm::~GeneticAlgorithm()
{
    population.clear();
}

// Assignment operator
GeneticAlgorithm& GeneticAlgorithm::operator=(const GeneticAlgorithm& other)
{
    if (this != &other) {
        populationSize = other.populationSize;
        mutationProb = other.mutationProb;
        crossoverProb = other.crossoverProb;
        stopCriteria = other.stopCriteria;
        population = other.population;
        bestSolution = other.bestSolution;
        rng = other.rng;
    }
    return *this;
}

// Move assignment operator
GeneticAlgorithm& GeneticAlgorithm::operator=(GeneticAlgorithm&& other) noexcept
{
    if (this != &other) {
        populationSize = other.populationSize;
        mutationProb = other.mutationProb;
        crossoverProb = other.crossoverProb;
        stopCriteria = other.stopCriteria;
        population = move(other.population);
        bestSolution = std::move(other.bestSolution);
        rng = std::move(other.rng);
    }
    return *this;
}

// Starts the genetic algorithm
void GeneticAlgorithm::run(KnapsackProblem& problem)
{
    initializePopulation(problem);
    while (stopCriteria > 0)
    {
        evaluatePopulation(problem);
        updateBestSolution();
        evaluateCrossovers(problem);
        updateBestSolution();
        evaluateMutations();
        updateBestSolution();
        stopCriteria--;
    }
    problem.displaySolution(bestSolution.getGenotype());
    //population = std::vector<Individual>();
    //bestSolution = Individual(populationS);
}

// Creates the innitial population
void GeneticAlgorithm::initializePopulation(KnapsackProblem& problem)
{
    for (int i = 0; i < populationSize; i++)
    {
        population.push_back(Individual(problem.getItemsCount()));
        population[i].randomizeGenotype();
    }
}

// Evaluates the fitness of each Individual from population
void GeneticAlgorithm::evaluatePopulation(KnapsackProblem& problem)
{
    for (int i = 0; i < populationSize; i++) {
        population[i].calculateFitness(problem.getValues(), problem.getWeights(), problem.getKnapsackSize());
    }
}


void GeneticAlgorithm::updatePopulation(std::vector<Individual> &newPopulation)
{
    population = std::move(newPopulation);
}

std::vector<int> GeneticAlgorithm::selectParents()
{
    std::vector<int> indexesOfParents;
    int index1 = rng.generateRandomParentsNuber(populationSize);
    int index2 = rng.generateRandomParentsNuber(populationSize);
    int index3 = rng.generateRandomParentsNuber(populationSize);
    int index4 = rng.generateRandomParentsNuber(populationSize);

    if (population[index1].getFitness() > population[index2].getFitness()) {
        indexesOfParents.push_back(index1);
    }
    else {
        indexesOfParents.push_back(index2);
    }

    if (population[index3].getFitness() > population[index4].getFitness()) {
        indexesOfParents.push_back(index3);
    }
    else {
        indexesOfParents.push_back(index4);
    }

    return indexesOfParents;
}


// Performs crossovers on the population
void GeneticAlgorithm::evaluateCrossovers(KnapsackProblem& problem)
{
    std::vector<Individual> newPopulation;
    while (newPopulation.size() != populationSize)
    {
        std::vector<int> parentsToCrossOver = selectParents();
        if (rng.generateRandom01() < crossoverProb) {
            std::vector<Individual> children = population[parentsToCrossOver[0]].crossover(population[parentsToCrossOver[1]]);
            if (newPopulation.size() + 1 == populationSize) {
                children[0].calculateFitness(problem.getValues(), problem.getWeights(), problem.getKnapsackSize());
                children[1].calculateFitness(problem.getValues(), problem.getWeights(), problem.getKnapsackSize());
                if (children[0].getFitness() > children[1].getFitness()) {
                    newPopulation.push_back(children[0]);
                }
                else {
                    newPopulation.push_back(children[1]);
                }
            }
            else {
                newPopulation.push_back(children[0]);
                newPopulation.push_back(children[1]);
            }
        }
        else {
            if (newPopulation.size() + 1 == populationSize) {
                if (population[parentsToCrossOver[0]].getFitness() > population[parentsToCrossOver[1]].getFitness()) {
                    newPopulation.push_back(population[parentsToCrossOver[0]]);
                }
                else {
                    newPopulation.push_back(population[parentsToCrossOver[1]]);
                }                
            }
            else {
                newPopulation.push_back(population[parentsToCrossOver[0]]);
                newPopulation.push_back(population[parentsToCrossOver[1]]);
            }
        }
    }
    updatePopulation(newPopulation);
}


// Performs mutations on the population
void GeneticAlgorithm::evaluateMutations()
{
    for (int i = 0; i < populationSize; i++) {
        population[i].mutate(mutationProb);
    }
}

// Updates the best so-far-created individual
void GeneticAlgorithm::updateBestSolution()
{
    for (int i = 0; i < populationSize; i++)
    {
        if (population[i].getFitness() > bestSolution.getFitness()){
            bestSolution = population[i];
        }
    }
}

// Returns the best so-far-created individual
Individual& GeneticAlgorithm::getBestSolution()
{
    return bestSolution;
}

// Returns population of the algorithm
std::vector<Individual>& GeneticAlgorithm::getPopulation()
{
    return population;
}
