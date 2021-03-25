#include <iostream>
#include <algorithm>
#include <thread>
#include <vector>
#include <numeric>
#include <functional>
#include <future>
#include <chrono>
#include <ratio>
#include <ppl.h>
#include <concurrent_vector.h>
#include <execution>

#include <iomanip>
#include <utility>



auto print(int& n) { n++; };

int main() {

    int S = 1000000;
    std::vector <int> v(S);
    std::iota(v.begin(), v.end(), 1);


    auto now1 = std::chrono::system_clock::now();
    std::for_each(v.begin(), v.end(), print);
    auto end1 = std::chrono::system_clock::now();

   std::cout << "for_each time: " <<  std::chrono::duration_cast<std::chrono::microseconds>(end1 - now1).count() << "\n";

   std::for_each(v.begin(), v.end(), print);

   auto now2 = std::chrono::system_clock::now();
   concurrency::parallel_for_each(v.begin(), v.end(), print);
   auto end2 = std::chrono::system_clock::now();

   std::cout << "parallel_for_each time: " << std::chrono::duration_cast<std::chrono::microseconds>(end2 - now2).count() << "\n";

  /* const std::vector<long> v2(100'000'007, 1);

   auto now3 = std::chrono::system_clock::now();
   std::reduce(std::execution::seq, v2.cbegin(), v2.cend());
   auto end3 = std::chrono::system_clock::now();

   std::cout << "reduce time: " << std::chrono::duration_cast<std::chrono::microseconds>(end3 - now3).count() << "\n";*/



}