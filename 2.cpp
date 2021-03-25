#include <algorithm>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>
#include <functional>
#include <chrono>
#include <ratio>
#include <fstream>

template < typename Iterator, typename T >
struct accumulate_block
{
	void operator()(Iterator first, Iterator last, T& result)
	{
		result = std::accumulate(first, last, result); // !
	}
};

template < typename Iterator, typename T >
T parallel_accumulate(Iterator first, Iterator last, T init, int N)
{
	const std::size_t length = std::distance(first, last);

	if (!length)
		return init;

	const std::size_t min_per_thread = 25;
	const std::size_t max_threads =
		(length + min_per_thread - 1) / min_per_thread;

	const std::size_t hardware_threads =
		std::thread::hardware_concurrency();

	const std::size_t num_threads = N;
		

	const std::size_t block_size = length / num_threads;

	std::vector < T > results(num_threads);
	std::vector < std::thread > threads(num_threads - 1);

	Iterator block_start = first;

	for (std::size_t i = 0; i < (num_threads - 1); ++i)
	{
		Iterator block_end = block_start;
		std::advance(block_end, block_size);

		threads[i] = std::thread(
			accumulate_block < Iterator, T >(),
			block_start, block_end, std::ref(results[i])); // !

		block_start = block_end;
	}

	accumulate_block < Iterator, T >()(block_start, last, results[num_threads - 1]);

	std::for_each(threads.begin(), threads.end(),
		std::mem_fn(&std::thread::join));

	return std::accumulate(results.begin(), results.end(), init);
}

int main(int argc, char** argv)
{
	std::string outFile = "accumulate_data.dat";
	std::ofstream out(outFile);


	if (!out.is_open()) {
		std::cerr << "cannot open outFile" << outFile << std::endl;
		return EXIT_FAILURE;
	}

	std::vector < int > v(100);

	std::iota(v.begin(), v.end(), 1);//fills vector

	std::vector< std::chrono::milliseconds> times;

	for (int N = 1; N < std::thread::hardware_concurrency() + 1; N++) {
		auto now = std::chrono::system_clock::now();
		std::cout << parallel_accumulate(v.begin(), v.end(), 0, N) << std::endl;
		auto end = std::chrono::system_clock::now();

		out << N << "\t" << std::chrono::duration_cast<std::chrono::microseconds>(end - now).count() << "\n";
	}

	out.close();
	

	return EXIT_SUCCESS;
}