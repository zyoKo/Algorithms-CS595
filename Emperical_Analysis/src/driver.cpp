#include "lis.h"
#include "stopwatch.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <random>
#include <string>

void create_sequence_of_size(int size, std::vector<int>& sequence)
{
	sequence.reserve(size);
	for (int i = 0; i < size; ++i)
		sequence.push_back(std::rand() % (10 * size));
}

void OutputToFile(const std::vector<int>& data, const std::string& filename)
{
	std::ofstream outfile(filename);
	if (outfile.is_open())
	{
		std::cout << "Writing to file: " << filename << "!\n";
		for (const int i : data)
			outfile << i << " ";

		outfile.close();
		std::cout << "Finished writing to file: " << filename << "!\n\n";
	}
	else
	{
		std::cerr << "Unable to open the file [" << filename << "] for writing." << std::endl;
	}
}

void BackTrackingLIS(const std::vector<int>& sizeOfData, std::vector<int>& data, int num_tests, std::vector<double>& timeToExecute)
{
	Stopwatch stopwatch;
	for (const auto& dataSize : sizeOfData)
	{
		stopwatch.start();
		for (int i = 0; i < num_tests; ++i)
		{
			std::vector<int> sequence;
			create_sequence_of_size(dataSize, sequence);

			data.push_back(longest_increasing_subsequence(sequence));
		}
		auto timeTakenToExecute = stopwatch.elapsed_milliseconds();
		timeToExecute.push_back(timeTakenToExecute);
		stopwatch.clear();

		std::string fileName = "./src/data." + std::to_string(dataSize);
		OutputToFile(data, fileName);

		data.clear();
	}
}

int main()
{
	//std::srand(static_cast<unsigned>(std::time(nullptr)));

	static std::vector<int> sizeOfData = { 100, 200, 300, 400, 500, 750, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000 };
	static constexpr int num_tests = 200;
	std::vector<int> data;
	std::vector<double> timeToExecute;

	//BackTrackingLIS(sizeOfData, data, num_tests, timeToExecute);

	// C++11 RNG
	std::random_device rd;
	std::mt19937 gen(rd()); // random engine

	for (auto size : sizeOfData)
	{
		// create array size n with values [-n/3,2n/3] !!!!!!!!!!!!!!!!!!!!!!!!!
		int* a = new int[size];
		for (int i = 0; i < size; ++i) {
			a[i] = i - size / 3;
		}

		for (int experiment = 0; experiment < num_tests; ++experiment)
		{
			std::shuffle(a, a + size, gen); // C++11

			// Kadane's algorithm starts here
			int max_so_far = a[0], max_ending_here = a[0];

			for (int i = 0; i < size; ++i)
			{
				max_ending_here = max_ending_here + a[i];
				if (max_so_far < max_ending_here)
					max_so_far = max_ending_here;

				if (max_ending_here < 0)
					max_ending_here = 0;
			}
			// Kadane's algorithm ends here

			//std::cout << max_so_far << " "; // solution
			data.push_back(max_so_far);
		}

		std::string fileName = "./experiments/data." + std::to_string(size);
		OutputToFile(data, fileName);

		data.clear();

		delete[] a;
	}

	return 0;
}
