#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <chrono>
#include "QuicksortSequential.h"

// Function to generate a vector of n random numbers in the range [low, high]
std::vector<int> generateRandomVector(int n, int low, int high) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(low, high);
    std::vector<int> vec(n);
    for (int i = 0; i < n; i++) {
        vec[i] = dis(gen);
    }
    return vec;
}

int main() {
    // Set the sizes of the datasets
    const int dataset_sizes[] = { 10, 50, 100, 1000, 10000, 1000000 };
    const int num_datasets = sizeof(dataset_sizes) / sizeof(dataset_sizes[0]);

    // Set the range for the random numbers
    const int low = 1;
    const int high = 10000;

    // Process each dataset
    for (int i = 0; i < num_datasets; i++) {
        // Generate a random vector of size dataset_sizes[i]
        std::vector<int> arr = generateRandomVector(dataset_sizes[i], low, high);

        // Construct the input file name
        std::string input_file_name = "input" + std::to_string(dataset_sizes[i]) + ".txt";

        // Open the input file
        std::ofstream input_file(input_file_name);
        if (!input_file) {
            std::cerr << "Error: could not open input file " << input_file_name << "\n";
            return 1;
        }

        // Write the size of the vector to the input file
        input_file << dataset_sizes[i] << "\n";

        // Write the vector to the input file
        for (int j = 0; j < dataset_sizes[i]; j++) {
            input_file << arr[j] << " ";
        }
        input_file.close();

        // Perform quicksort and measure the time taken
        Quicksort quicksort;
        auto start_time = std::chrono::high_resolution_clock::now();
        quicksort.sort(arr);
        auto end_time = std::chrono::high_resolution_clock::now();
        auto time_taken = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();

        // Output the time taken
        std::cout << "Quicksort completed successfully for " << dataset_sizes[i] << " elements in " << time_taken << " microseconds\n";

        // Construct the output file name
        std::string output_file_name = "output" + std::to_string(dataset_sizes[i]) + ".txt";

        // Write output to file
        std::ofstream output_file(output_file_name);
        if (!output_file) {
            std::cerr << "Error: could not open output file " << output_file_name << "\n";
            return 1;
        }
        for (int j = 0; j < dataset_sizes[i]; j++) {
            output_file << arr[j] << " ";
        }
        output_file.close();
    }

    return 0;
}
