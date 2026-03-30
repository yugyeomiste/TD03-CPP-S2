#include <iostream>
#include <vector>
#include <algorithm>

// Verifie si le tableau est trié
bool is_sorted(std::vector<int> const& vec) { 
    return std::is_sorted(vec.begin(), vec.end()); 
}

// On cherche le minimum et on le place au début
void selection_sort(std::vector<int> & vec) {
    if (vec.empty()) return;

    for (size_t i = 0; i < vec.size() - 1; ++i) {
        size_t index_min = i;
        
        for (size_t j = i + 1; j < vec.size(); ++j) {
            if (vec[j] < vec[index_min]) {
                index_min = j;
            }
        }
        
        if (index_min != i) {
            std::swap(vec[i], vec[index_min]);
        }
    }
}

// TRI À BULLES  On fait remonter les plus grands à la fin
void bubble_sort(std::vector<int> & vec) {
    if (vec.empty()) return;
    
    bool echange;
    size_t taille = vec.size();
    
    do {
        echange = false;
        for (size_t i = 0; i < taille - 1; ++i) {
            if (vec[i] > vec[i + 1]) {
                std::swap(vec[i], vec[i + 1]);
                echange = true;
            }
        }
        taille--; 
        
    } while (echange); // Arrêt si le tableau déjà trié
}

int main() {
    std::cout << "--- Exo1 : Tris iteratifs ---" << std::endl;
    
    std::vector<int> v1 = {6, 2, 8, 1, 5, 3, 9};
    std::vector<int> v2 = v1; 

    selection_sort(v1);
    bubble_sort(v2);

    if (is_sorted(v1) && is_sorted(v2)) {
        std::cout << "Succes : Les tableaux sont tries !" << std::endl;
    } else {
        std::cout << "Erreur de tri." << std::endl;
    }
    
    return 0;
}