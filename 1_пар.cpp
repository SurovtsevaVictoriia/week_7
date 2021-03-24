#include <thread>
#include <iostream>
#include <random>


auto s_func(int & N, int & S) {

    std::random_device rd;
    std::mt19937 mersenne(rd());
    std::uniform_real_distribution<> real(0.0, 1.0);


    for (int count = 0; count < N/2; ++count)
    {
        auto x = real(mersenne);
        auto y = real(mersenne);
        if (x * x + y * y < 1) { S++; };
    }

}

int main() {

    int S = 0;
    int N = 1000000000;
   

    std::thread thread1(s_func, N, S);
    std::thread thread2(s_func, N, S);

    std::cout << "pi: " << 4 * (float)S / (float)N << std::endl;


}


