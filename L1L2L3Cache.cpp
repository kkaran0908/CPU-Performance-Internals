#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>

void benchmark(const size_t memSizeKb)
{	
	const size_t noOfBytes    = memSizeKb*1024;
	const size_t noOfElements = noOfBytes/(sizeof(size_t));

	std::vector<size_t> vec(noOfElements);
	std::vector<size_t> indices(noOfElements);

	for(size_t i=0; i < noOfElements; i++)
		indices[i] = i;

	//shuffle the random vector
	std::shuffle(indices.begin(), indices.end(), std::mt19937(std::random_device{}()));

	//create the dependency chain, so that CPU can not parallise the computation
	for(size_t i =0; i<noOfElements-1; i++) {
		vec[indices[i]] = indices[i+1];
	}
	vec[indices[noOfElements-1]] = indices[0];

	const size_t accessIterations = 1000000;
	volatile size_t idx = 0;
	const auto startTime = std::chrono::high_resolution_clock::now();
	for(size_t i=0; i< accessIterations; i++) {	
		idx = vec[idx];
	}

	const auto endTime = std::chrono::high_resolution_clock::now();
	const auto totalTime = duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
	const double avgAccessTimePerElement = static_cast<double>(totalTime)/accessIterations;

	std::cout << "Size: "<< memSizeKb << " KB" << " | Avg latency: " << avgAccessTimePerElement << " ns" << std::endl;
}

int main()
{
	//this memory is in kb
	std::vector<size_t> memorySize = { 4, 32, 256, 1024, 8192, 32768};
    for (const auto size : memorySize){
    	benchmark(size);
    }
    return 0;
}