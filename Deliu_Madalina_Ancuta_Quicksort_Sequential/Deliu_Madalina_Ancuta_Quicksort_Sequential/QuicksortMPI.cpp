#include <mpi.h>
#include <iostream>
#include <vector>
#include <string>
#include "Timer.h"
#include "WriteToFile.h"
#include "RandomGenerator.h"
#include "QuicksortSequential.h"

// Function to perform quicksort on the input vector
void quicksort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int pivot = arr[right];
        int i = left - 1;

        for (int j = left; j < right; j++) {
            if (arr[j] <= pivot) {
                i++;
                std::swap(arr[i], arr[j]);
            }
        }

        std::swap(arr[i + 1], arr[right]);

        int pivot_index = i + 1;

        quicksort(arr, left, pivot_index - 1);
        quicksort(arr, pivot_index + 1, right);
    }
}

// Function to perform quicksort on the input vector and measure the execution time
void performQuicksort(std::vector<int>& arr, const std::string& input_file_name, const std::string& output_file_name) {
    Timer timer;
    quicksort(arr, 0, arr.size() - 1);
    double elapsed_time = timer.elapsed();
    // std::cout << "Quicksort took " << elapsed_time << " seconds for input file " << input_file_name << "\n";
    writeOutputToFile(output_file_name, arr);
}

int main(int argc, char* argv[]) {
    const int dataset_sizes[] = { 10, 50, 100, 1000, 10000, 1000000 };
    const int num_datasets = sizeof(dataset_sizes) / sizeof(dataset_sizes[0]);
    const std::string input_directory = "input_files/";
    const std::string output_directory = "output_files/";
    int low = 0;
    int high = 10000;

    MPI_Init(&argc, &argv);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    for (int i = 0; i < num_datasets; i++) {
        std::string input_file_name = input_directory + "input" + std::to_string(dataset_sizes[i]) + ".txt";
        std::string output_file_name = output_directory + "output" + std::to_string(dataset_sizes[i]) + ".txt";

        if (world_rank == 0) {
            Timer timer;
            std::vector<int> arr = generateRandomVector(dataset_sizes[i], low, high);

            int elements_per_process = dataset_sizes[i] / world_size;
            int remaining_elements = dataset_sizes[i] % world_size;

            // Distribute the vector to all processes
            for (int dest = 1; dest < world_size; dest++) {
                int start_index = dest <= remaining_elements ? dest * (elements_per_process + 1) : (remaining_elements * (elements_per_process + 1)) + ((dest - remaining_elements) * elements_per_process);
                int end_index = start_index + (dest <= remaining_elements ? elements_per_process : elements_per_process - 1);
                int num_elements = end_index - start_index + 1;

                MPI_Send(&num_elements, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
                MPI_Send(&arr[start_index], num_elements, MPI_INT, dest, 0, MPI_COMM_WORLD);
            }

            // Sort the local portion of the vector
            std::vector<int> local_arr(arr.begin(), arr.begin() + elements_per_process + (world_rank < remaining_elements ? 1 : 0));
            performQuicksort(local_arr, input_file_name, output_file_name);

            // Gather the sorted vectors from all processes
            for (int src = 1; src < world_size; src++) {
                int num_elements;
                MPI_Recv(&num_elements, 1, MPI_INT, src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

                std::vector<int> received_arr(num_elements);
                MPI_Recv(&received_arr[0], num_elements, MPI_INT, src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

                local_arr.insert(local_arr.end(), received_arr.begin(), received_arr.end());
            }

            // Merge the sorted vectors
            quicksort(local_arr, 0, local_arr.size() - 1);

            std::cout << "Time for set " << i + 1 << " with " << dataset_sizes[i] << " numbers: " << timer.elapsed() << " seconds\n";
            timer.reset();

            // Write the final sorted vector to file
            writeOutputToFile(output_file_name, local_arr);
        }
        else {
            int num_elements;
            MPI_Recv(&num_elements, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            std::vector<int> local_arr(num_elements);
            MPI_Recv(&local_arr[0], num_elements, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            // Sort the local portion of the vector
            performQuicksort(local_arr, input_file_name, output_file_name);

            // Send the sorted vector back to the root process
            MPI_Send(&num_elements, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
            MPI_Send(&local_arr[0], num_elements, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();

    return 0;
}
