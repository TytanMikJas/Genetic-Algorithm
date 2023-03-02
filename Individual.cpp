#include "Individual.h"


// Default constructor
Individual::Individual()
{
	fitness = 0;
	rng = RandomNumberGenerator();
}

// Parametrized Constructor
Individual::Individual(int vectorSize) 
{
	if (vectorSize < 0) {
		throw ConstructorError("Invalid input for vectorSize in Individual\nExpected: natural Integer\nProvided : " + std::to_string(vectorSize));
	}
	fitness = 0;
	genotype.resize(vectorSize);
	rng = RandomNumberGenerator();
}

// Copy constructor
Individual::Individual(const Individual& other)
{
	fitness = other.fitness;
	genotype = other.genotype;
	rng = other.rng;
}

// Move constructor
Individual::Individual(Individual&& other) noexcept
{
	fitness = other.fitness;
	genotype = move(other.genotype);
	rng = std::move(other.rng);
}

// Destructor
Individual::~Individual()
{

}

// Assignment operator
Individual& Individual::operator = (const Individual& other)
{
	if (this != &other) {
		genotype = other.genotype;
		fitness = other.fitness;
		rng = other.rng;
	}
	return *this;
}

// Move assignment operator
Individual& Individual::operator = (Individual&& other) noexcept
{
	if (this != &other) {
		genotype = move(other.genotype);
		fitness = other.fitness;
		rng = std::move(other.rng);
		other.fitness = 0;
	}
	return *this;
}

// Method that calculates fitness of our Individual based on it's genotype
void Individual::calculateFitness(const std::vector<double> &values,const std::vector<double> &weights,const int knapsackSize) 
{
	double totalValue = 0;
	double totalWeight = 0;
	for (int i = 0; i < genotype.size(); i++)
	{
		if (genotype[i] == 1)
		{
			totalValue += values[i];
			totalWeight += weights[i];
		}
	}

	if (totalWeight > knapsackSize)
	{
		fitness = 0;
	}
	else
	{
		fitness = totalValue;
	}
}

// Method that mutates our Individual's genotypes
void Individual::mutate(float probability)
{
	for (int i = 0; i < genotype.size(); i++)
	{
		if (rng.generateRandom01() < probability)
		{
			genotype[i] = 1 - genotype[i];
		}
	}
}

// Method that creates two individuals from crossover of this Individual + otherIndividual
std::vector<Individual> Individual::crossover(Individual& other)
{
	std::vector<Individual> children;
	int size = (int)genotype.size();
	int crossoverPoint = rng.generateRandomCP(size);
	Individual child1 = Individual(size);
	Individual child2 = Individual(size);
	for (int i = 0; i < crossoverPoint; i++)
	{
		child1.genotype[i] = genotype[i];
		child2.genotype[i] = other.genotype[i];
	}
	for (int i = crossoverPoint; i < size; i++)
	{
		child1.genotype[i] = other.genotype[i];
		child2.genotype[i] = genotype[i];
	}
	children.push_back(child1);
	children.push_back(child2);
	
	return children;
}

// Genotype getter
std::vector<int>& Individual::getGenotype()
{
	return genotype;
}

//Method to randomize genotype of our individual
void Individual::randomizeGenotype()
{
	for (int i = 0; i < genotype.size(); i++)
	{
		genotype[i] = rng.generateRandomGenotypes();
	}
}

//method to set new values to genotype
void Individual::setGenotype(std::vector<int>& newGenotype)
{
	genotype = newGenotype;
}

int Individual::getFitness()
{
	return fitness;
}
