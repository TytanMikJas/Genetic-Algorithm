#include <iostream>
#include "Individual.h"
#include "GeneticAlgorithm.h"
#include "KnapsackProblem.h"

int main()
{
	std::vector<double> weights;
	weights.push_back(4);
	weights.push_back(1);
	weights.push_back(3);
	weights.push_back(2);
	std::vector<double> sizes;
	sizes.push_back(5);
	sizes.push_back(1);
	sizes.push_back(4);
	sizes.push_back(3);
	try {
		GeneticAlgorithm testForList = GeneticAlgorithm(4, 0.2, 0.7, 20);
		KnapsackProblem problemFromList = KnapsackProblem(4, 5, weights, sizes);

		std::cout << "Knapsack Problem from TEP list test:\n\nExpected answer:\nbest value: 7\n\nAnswer from Genetic Algorithm:" << std::endl;
		testForList.run(problemFromList);


		GeneticAlgorithm testForFile = GeneticAlgorithm(40, 0.2, 0.7, 20);
		KnapsackProblem problemFromFile = KnapsackProblem("C:\\TEP\\KnapsackProblem\\low_dim_problem1.txt");

		std::cout << "\n\nKnapsack Problem from file test:\n\nExpected answer:\nbest value: 295\n\nAnswer from Genetic Algorithm:" << std::endl;
		testForFile.run(problemFromFile);
		std::cout << std::endl;
	}
	catch(ConstructorError& Constructionerror) {
		std::cout << Constructionerror.displayError() << std::endl;
	}
	catch (FileReadError& ReadError) {
		std::cout << ReadError.displayError() << std::endl;
	}

	
}

