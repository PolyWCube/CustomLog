#include "../include/Log.hpp"

#include <chrono>
#include <iostream>
#include <sstream>
#include <thread>

DEFINE_LOG_LEVEL(Info, FG_GREEN, NONE);

const int ITERATIONS = 100000;

void NullSink() {
	std::cout << "Null sink (no console out - pure process) test" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(3));
	std::cout << "Test start" << std::endl;
	int iterations = ITERATIONS;

	std::ostringstream null_stream;
	std::streambuf* old_cout = std::cout.rdbuf();
	std::cout.rdbuf(null_stream.rdbuf());

	auto start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < iterations; ++i) {
		Custom::Log::Info("Hello world");
	}

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

	std::cout.rdbuf(old_cout);

	std::cout << "Time taken: " << duration.count() << " ms" << std::endl;
	std::cout << "Average time per iteration: " << static_cast<double>(duration.count()) / iterations << " ms" << std::endl;
	std::cout << std::endl;
}

void PrintNumber() {
	std::cout << "Print numbers test:" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(3));
	std::cout << "Test start" << std::endl;
	int iterations = ITERATIONS;

	auto start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < iterations; ++i) {
		Custom::Log::Info(i);
	}

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

	std::cout << "Time taken: " << duration.count() << " ms" << std::endl;
	std::cout << "Average time per iteration: " << static_cast<double>(duration.count()) / iterations << " ms" << std::endl;
	std::cout << std::endl;
}

int main() {
	std::cout << "Iterations: " << ITERATIONS << "\nBenchmark will start in 3 seconds:" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(3));
	NullSink();
	std::cout << "\nNext test in 3 seconds." << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(3));
	PrintNumber();
	std::cout << "Benchmark finished, press Enter to close..." << std::endl;
	getchar();
	return 0;
}