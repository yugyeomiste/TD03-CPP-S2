#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include "ScopedTimer.hpp"

// Tableau de nombres aléatoires
std::vector<int> generate_random_vector(size_t const size, int const max = 100) {
    std::vector<int> vec(size);
    std::generate(vec.begin(), vec.end(), [&max]() { return std::rand() % max;} );
    return vec;
}

void selection_sort(std::vector<int> & vec) {
    if (vec.empty()) return;
    for (size_t i = 0; i < vec.size() - 1; ++i) {
        size_t min = i;
        for (size_t j = i + 1; j < vec.size(); ++j) {
            if (vec[j] < vec[min]) min = j;
        }
        if (min != i) std::swap(vec[i], vec[min]);
    }
}

int main() {
    std::cout << "Exo3: Comparaison des temps" << std::endl;
    
    // Tableau de 10 000 elmnts
    std::vector<int> base = generate_random_vector(10000);
    
    {
        std::vector<int> v1 = base;
        ScopedTimer timer("Temps de std::sort");
        std::sort(v1.begin(), v1.end());
    }
    {
        std::vector<int> v2 = base;
        ScopedTimer timer("Temps de notre selection_sort  (O(n^2))");
        selection_sort(v2);
    } 

    return 0;
}