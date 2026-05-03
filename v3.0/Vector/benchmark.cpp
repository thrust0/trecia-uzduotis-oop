#include "vector.hpp"
#include <vector>
#include <chrono>
#include <iomanip>

unsigned int sz = 100000000;

int main()
{
    std::cout << "size: " << sz << "\n";
    std::vector<int> v1;

    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < sz; i++)
        v1.push_back(i);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout <<  std::fixed << std::setprecision(6) << "Time for std::vector: " << duration.count() << " seconds\n";  

    my::vector<int> v2;
    auto start1 = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < sz; i++)
        v2.push_back(i);
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration1 = end1 - start1;
    std::cout << std::fixed << std::setprecision(6) << "Time for my::vector: " << duration1.count() << " seconds\n";  
}