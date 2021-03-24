#include <iostream>
#include <random>

int main() {
	int N = 1000000;

	std::random_device rd;
	std::mt19937 mersenne(rd());
    std::uniform_real_distribution<> real(0.0, 1.0);

    int S = 0;

    for (int count = 0; count < N; ++count)
    {
        auto x = real(mersenne);
        auto y = real(mersenne);
        if (x * x + y * y < 1) { S++; };
    }
    
    std::cout << "pi: " << 4 * (float)S / (float)N << std::endl;

}