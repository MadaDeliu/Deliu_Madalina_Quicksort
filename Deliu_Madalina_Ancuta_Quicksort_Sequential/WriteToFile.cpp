#include "WriteToFile.h"
// Function to write the input vector to the input file
void writeInputToFile(const std::string& file_name, const std::vector<int>& arr) {
	std::ofstream input_file(file_name);
	if (!input_file) {
		std::cerr << "Error: could not open input file " << file_name << "\n";
		return;
	}
	// Write the size of the vector to the input file
	input_file << arr.size() << "\n";

	// Write the vector to the input file
	for (int j = 0; j < arr.size(); j++) {
		input_file << arr[j] << " ";
	}
	input_file.close();
}

// Function to write the sorted vector to the output file
void writeOutputToFile(const std::string& file_name, const std::vector<int>& arr) {
	std::ofstream output_file(file_name);
	if (!output_file) {
		std::cerr << "Error: could not open output file " << file_name << "\n";
		return;
	}
	for (int j = 0; j < arr.size(); j++) {
		output_file << arr[j] << " ";
	}
	output_file.close();
}
