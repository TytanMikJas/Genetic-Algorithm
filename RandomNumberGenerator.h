#pragma once
#include <random>

class RandomNumberGenerator {
public:
	// Constructor
	RandomNumberGenerator(){};

	// Metod to randomize 0 or 1
	int generateRandomGenotypes() {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, 1);
		return dis(gen);
	}

	// Method that generates random intager for crossOver from 1 to size-1 (crossover can not be performed on the 0 index and max index)
	int generateRandomCP(int size) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(1, size - 2);
		return dis(gen);
	}

	// Method that generates random double from 0 to 1
	double generateRandom01()
	{
		std::random_device rd;
		std::mt19937 eng(rd());
		std::uniform_real_distribution<> distr(0.0, 1.0);
		return distr(eng);
	}

	//Method that generates numbers for random parents
	int generateRandomParentsNuber(int populationSize)
	{
		std::random_device rd;
		std::mt19937 eng(rd());
		std::uniform_int_distribution<> distr(0, populationSize - 1);
		return distr(eng);
	}
};