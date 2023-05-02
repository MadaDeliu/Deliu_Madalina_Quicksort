#include <string>
#include "Timer.h"
#include <algorithm>
#include "RandomGenerator.h"
#include <omp.h>
#include "QuicksortParallel.h"

int main() {
    const std::string input_directory = "input_files/";
    const std::string output_directory = "output_files/";
	  const int dataset_sizes[] = { 10, 50, 100, 1000, 10000, 1000000 };
	  const int num_datasets = sizeof(dataset_sizes) / sizeof(dataset_sizes[0]); //the number of elements of dataset_sizes
    Timer timer;
    const int num_threads = omp_get_max_threads();
    const int max_active_levels = 2;
    omp_set_max_active_levels(max_active_levels);
    const int low = 0;
    const int high = 10000;
    
	  for (int i = 0; i < num_datasets; i++) {
        const int chunk_size = i / num_threads;
        std::string input_file_name = input_directory + "input" + std::to_string(i) + ".txt";
        std::string output_file_name = output_directory + "output" + std::to_string(i) + ".txt";
 
//   Process each dataset
		for (int j = 0; j < dataset_sizes[i]; j++) {
			timer.start();
			// Generate a random vector of size dataset_sizes[i]
			std::vector<int> arr = generateRandomVector(dataset_sizes[i], low, high);
			//#pragma omp parallel num_threads(num_threads)
        {
#pragma omp for schedule(static, chunk_size)
            for (int j = 0; j < num_threads; j++) {
                int left = j * chunk_size;
                int right = std::min((j + 1) * chunk_size - 1, i - 1);
                QuicksortParallel::quicksort_parallel(arr, left, right);
            }
        }
        timer.stop();
		}
		std::cout << "Time for set " << i + 1 << " with " << dataset_sizes[i] << " numbers: " << timer.elapsed() << " seconds\n";
		timer.reset();
    }
    return 0;
}
