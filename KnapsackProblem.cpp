#include "KnapsackProblem.h"


// Parameterized constructor with file name as parameter, reads from file into the member variables in Class
KnapsackProblem::KnapsackProblem(const std::string& fileName) 
{
	bestValue = 0;
	loadFromFile(fileName);
}

// Parameterized constructor
KnapsackProblem::KnapsackProblem(int numOfItems, double SizeOfKnapsack, const std::vector<double>& SizesVector, const std::vector<double>& ValuesVector) 
{
	if (numOfItems <= 0) {
		throw ConstructorError("Invalid input for NumberOfItems in Knapsack\nExpected Natural Inager\nProvided: " + std::to_string(numOfItems));
	}
	else if (SizeOfKnapsack <= 0) {
		throw ConstructorError("Invalid input for KnapsackSize in Knapsack\nExpected Natural Inager\nProvided: " + std::to_string(SizeOfKnapsack));
	}
	itemsCount = numOfItems;
	knapsackSize = SizeOfKnapsack;
	bestValue = 0;
	weights = SizesVector;
	values = ValuesVector;
}

// Copy constructor
KnapsackProblem::KnapsackProblem(const KnapsackProblem& other) 
{
	itemsCount = other.itemsCount;
	knapsackSize = other.knapsackSize;
	weights = other.weights;
	values = other.values;
	bestValue = other.bestValue;
}

// Move constructor
KnapsackProblem::KnapsackProblem(KnapsackProblem&& other) noexcept 
{
	itemsCount = other.itemsCount;
	knapsackSize = other.knapsackSize;
	weights = move(other.weights);
	values = move(other.values);
	bestValue = other.bestValue;
	other.itemsCount = 0;
	other.knapsackSize = 0;
	other.bestValue = 0;
}

// Destructor
KnapsackProblem::~KnapsackProblem() 
{
	//no dynamically allocated memory to deallocate
}

// Assignment operator 
KnapsackProblem& KnapsackProblem::operator=(const KnapsackProblem& other)
{
	if (this != &other) {
		itemsCount = other.itemsCount;
		knapsackSize = other.knapsackSize;
		bestValue = other.bestValue;
		weights = other.weights;
		values = other.values;
	}
	return *this;
}

// Move assignment operator
KnapsackProblem& KnapsackProblem::operator=(KnapsackProblem&& other) noexcept
{
	if (this != &other)
	{
		itemsCount = other.itemsCount;
		knapsackSize = other.knapsackSize;
		bestValue = other.bestValue;
		weights = move(other.weights);
		values = move(other.values);
		other.itemsCount = 0;
		other.knapsackSize = 0;
		other.bestValue = 0;
	}
	return *this;
}

// Takes in an individual's genotype and calculates the value of the solution represented by that genotype
int KnapsackProblem::valueSolution(std::vector<int> &genotype) 
{
	double totalValue = 0;
	double totalWeight = 0;
	double result = 0;
	for (int i = 0; i < genotype.size(); i++)
	{
		if (genotype[i] == 1)
		{
			totalValue += values[i];
			totalWeight += weights[i];
		}
	}

	if (totalWeight <= knapsackSize)
	{
		result = totalValue;
	}
	return result;
}

// This method loads the data for a knapsack problem instance from a file.
void KnapsackProblem::loadFromFile(const std::string& fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open()) {
		throw FileReadError(fileName, " file not found.");
	}

	std::string input;
	std::regex validInt("^[1-9]\\d*$");
	std::regex validDouble(R"(^\+?[0-9]\d*(\.\d+)?$)");

	file >> input;
	if (!(std::regex_match(input, validDouble))) {
		throw FileReadError(fileName, "Invalid input for numberOfItems\nExpected: Natural Integer\nProvided: " + input);
	}
	itemsCount = std::stoi(input);

	file >> input;
	if (!(std::regex_match(input, validDouble))) {
		throw FileReadError(fileName, "Invalid input for KnapsackSize\nExpected: Postivive Double\nProvided: " + input);
	}
	knapsackSize = std::stod(input);

	for (int i = 0; i < itemsCount; i++)
	{
		file >> input;
		if (!(std::regex_match(input,validDouble))) {
			throw FileReadError(fileName, "Invalid input for itemValue\nExpected: Positive Double\nProvided: " + input);
		}
		values.push_back(std::stod(input));

		file >> input;
		if (!(std::regex_match(input, validDouble))) {
			throw FileReadError(fileName, "Invalid input for itemWeight\nExpected: Positive Double\nProvided: " + input);
		}
		weights.push_back(std::stod(input));
	}

	file.close();
}

// This method displays the soultion to Knapsack Problem
void KnapsackProblem::displaySolution(std::vector<int> bestGenotype)
{
	std::cout << "best value: " << valueSolution(bestGenotype) << '\n';
	for (int i : bestGenotype)
		std::cout << i << ' ';
}

// Returns the amout of items
int KnapsackProblem::getItemsCount()
{
	return itemsCount;
}

std::vector<double>& KnapsackProblem::getWeights()
{
	return weights;
}

std::vector<double>& KnapsackProblem::getValues()
{
	return values;
}

int KnapsackProblem::getKnapsackSize()
{
	return knapsackSize;
}