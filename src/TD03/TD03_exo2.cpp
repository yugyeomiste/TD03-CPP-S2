#include <iostream>
#include <vector>
#include <algorithm>

bool is_sorted(std::vector<int> const& vec) { 
    return std::is_sorted(vec.begin(), vec.end()); 
}

//TRI FUSION
void merge_sort_merge(std::vector<int> & vec, size_t const left, size_t const middle, size_t const right) {

    std::vector<int> left_part(vec.begin() + left, vec.begin() + middle + 1);
    std::vector<int> right_part(vec.begin() + middle + 1, vec.begin() + right + 1);

    size_t i = 0, j = 0, k = left;

    //  Fusion avec le plus petit à chaque fois
    while (i < left_part.size() && j < right_part.size()) {
        if (left_part[i] <= right_part[j]) {
            vec[k++] = left_part[i++];
        } else {
            vec[k++] = right_part[j++];
        }
    }

    // On vide le reste
    while (i < left_part.size()) vec[k++] = left_part[i++];
    while (j < right_part.size()) vec[k++] = right_part[j++];
}

void merge_sort(std::vector<int> & vec, size_t const left, size_t const right) {
    if (left >= right) return;
    
    size_t middle = left + (right - left) / 2;
    
    merge_sort(vec, left, middle);
    merge_sort(vec, middle + 1, right);
    merge_sort_merge(vec, left, middle, right);
}

void merge_sort(std::vector<int> & vec) {
    if (!vec.empty()) merge_sort(vec, 0, vec.size() - 1);
}

// TRI RAPIDE
size_t quick_sort_partition(std::vector<int> & vec, size_t left, size_t right) {
    int pivot = vec[right]; // pivot à la fin
    size_t i = left;

    for (size_t j = left; j < right; ++j) {
        if (vec[j] <= pivot) {
            std::swap(vec[i], vec[j]);
            i++;
        }
    }
    std::swap(vec[i], vec[right]); //  remet le pivot à sa place
    return i;
}

void quick_sort(std::vector<int> & vec, size_t const left, size_t const right) {
    if (left >= right) return;
    
    size_t p = quick_sort_partition(vec, left, right);
    
    if (p > 0) quick_sort(vec, left, p - 1);
    quick_sort(vec, p + 1, right);
}

void quick_sort(std::vector<int> & vec) {
    if (!vec.empty()) quick_sort(vec, 0, vec.size() - 1);
}

int main() {
    std::cout << "Exo2: Tris recursifs" << std::endl;
    std::vector<int> v1 = {6, 2, 8, 1, 5, 3, 9};
    std::vector<int> v2 = v1;

    merge_sort(v1);
    quick_sort(v2);

    if (is_sorted(v1) && is_sorted(v2)) {
        std::cout << "Succes : Les tableaux sont tries !" << std::endl;
    } else {
        std::cout << "Erreur de tri." << std::endl;
    }
    
    return 0;
}