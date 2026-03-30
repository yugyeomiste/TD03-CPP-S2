#include <iostream>
#include <vector>

// Recherche dichotomique : le tableau doit être trié 
int search(std::vector<int> const& vec, int value) {
    if (vec.empty()) return -1;

    int left = 0;
    int right = vec.size() - 1;

    while (left <= right) {
        int middle = left + (right - left) / 2;

        if (vec[middle] == value) {
            return middle; // trouvé 
        }
        else if (vec[middle] < value) {
            left = middle + 1; // cherche dans la moitié droite
        } 
        else {
            right = middle - 1; // dans la moitié gauche
        }
    }
    return -1; // Introuvable
}
int main() {
    std::cout << "Exo4 : Dichotomie" << std::endl;
    
    std::vector<int> test1 = {1, 2, 2, 3, 4, 8, 12};
    std::cout << "Indice de 8 dans le tableau 1 : " << search(test1, 8) << std::endl;

    // Tri du tableau de TD
    std::vector<int> test2 = {1, 2, 3, 3, 6, 12, 14, 15}; 
    std::cout << "Indice de 15 dans le tableau 2 : " << search(test2, 15) << std::endl;

    std::vector<int> test3 = {2, 2, 3, 4, 5, 8, 12, 15, 16};
    std::cout << "Indice de 16 dans le tableau 3 : " << search(test3, 16) << std::endl;

    std::vector<int> test4 = {5, 6, 7, 8, 9, 10, 11, 12, 13};
    std::cout << "Indice de 6 dans le tableau 4 : " << search(test4, 6) << std::endl;

    std::vector<int> test5 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::cout << "Indice de 10 dans le tableau 5 : " << search(test5, 10) << std::endl;
    // normalement ça affiche -1 car pas de 10

    return 0;
}