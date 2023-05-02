#include "RandomGenerator.h"

// Function to generate a vector of n random numbers in the range [low, high]
std::vector<int> generateRandomVector(int n, int low, int high) {
	std::random_device rd; // generated seed of a random hardware device
	std::mt19937 gen(rd()); // number generator initialized with the seed
	std::uniform_int_distribution<> dis(low, high); //distribution is in the range [low, high]
	std::vector<int> vec(n);
	for (int i = 0; i < n; i++) {
		vec[i] = dis(gen); // generate a random number in the specified range
	}
	return vec;
}