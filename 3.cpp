#include <iostream>
#include <algorithm>
#include <thread>
#include <vector>
#include <numeric>
#include <functional>
#include <future>

template < typename Iterator, typename T >
T parallel_for_each(Iterator first, Iterator last, T f)
{
	const std::size_t length = std::distance(first, last);

	const std::size_t max_size = 25;

	if (length <= max_size)
	{
		return std::for_each(first, last, f);
	}
	else
	{
		Iterator middle = first;
		std::advance(middle, length / 2);

		std::future < T > first_half_result =
			std::async(parallel_for_each < Iterator, T >, first, middle, f);

		T second_half_result = parallel_for_each(middle, last, f);

		return first_half_result.get();
	}
}


auto print(int& n) { std::cout << n << std::endl; };

int main() {
    int S = 100;
    

    std::vector <int> v(S);
    std::iota(v.begin(), v.end(), 1);

    parallel_for_each(v.begin(), v.end(), print);

	return 0;
}
