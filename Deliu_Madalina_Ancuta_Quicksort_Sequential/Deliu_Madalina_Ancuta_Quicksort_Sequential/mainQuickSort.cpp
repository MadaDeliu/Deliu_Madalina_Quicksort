//#include "Timer.h"
//#include "WriteToFile.h"
//#include "RandomGenerator.h"
//#include "QuicksortSequential.h"
//
//
// //Function to perform quicksort on the input vector and measure the execution time
//void performQuicksort(std::vector<int>& arr, const std::string& input_file_name, const std::string& output_file_name) {
//	Timer timer;
//	Quicksort qs;
//	qs.sort(arr);
//	double elapsed_time = timer.elapsed();
//	//std::cout << "Quicksort took " << elapsed_time << " seconds for input file " << input_file_name << "\n";
//	writeOutputToFile(output_file_name, arr);
//}
//
//
//int main() {
//    const int dataset_sizes[] = { 10, 50, 100, 1000, 10000, 1000000 };
//    const int num_datasets = sizeof(dataset_sizes) / sizeof(dataset_sizes[0]); //the number of elements of dataset_sizes
//    const std::string input_directory = "input_files/";
//    const std::string output_directory = "output_files/";
//    int low = 0;
//    int high = 10000;
//    Timer timer;
//
//    for (int i = 0; i < num_datasets; i++) {
//        
//        std::string input_file_name = input_directory + "input" + std::to_string(dataset_sizes[i]) + ".txt";
//        std::string output_file_name = output_directory + "output" + std::to_string(dataset_sizes[i]) + ".txt";
//        // Process each dataset
//        for (int j = 0; j < dataset_sizes[i]; j++) {
//            timer.start();
//            // Generate a random vector of size dataset_sizes[i]
//            std::vector<int> arr = generateRandomVector(dataset_sizes[i], low, high);
//            performQuicksort(arr, input_file_name, output_file_name);
//            timer.stop();
//        }
//        std::cout << "Time for set " << i+1 << " with " << dataset_sizes[i] << " numbers: " << timer.elapsed() << " seconds\n";
//        timer.reset();
//    }
//    return 0;
//}
//
//
//
//
//
//
