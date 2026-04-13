#include <iostream>
#include <string>
#include <vector>

// Hashing simple
size_t folding_string_hash(std::string const& s, size_t max) {
    if (max == 0) return 0;
    
    size_t hash = 0;
    for (char c : s) {
        hash = (hash + c) % max; // modulo a chaque tour pour eviter l'overflow
    }
    return hash;
}

// Hashing ordonne
size_t folding_string_ordered_hash(std::string const& s, size_t max) {
    if (max == 0) return 0;
    
    size_t hash = 0;
    for (size_t i = 0; i < s.length(); ++i) {
        hash = (hash + s[i] * (i + 1)) % max;
    }
    return hash;
}

int main() {
    size_t max = 1024;
    std::string s1 = "abc";
    std::string s2 = "cba";

    std::cout << "Hash simple abc : " << folding_string_hash(s1, max) << std::endl;
    std::cout << "Hash simple cba : " << folding_string_hash(s2, max) << std::endl;

    std::cout << "Hash ordonne abc : " << folding_string_ordered_hash(s1, max) << std::endl;
    std::cout << "Hash ordonne cba : " << folding_string_ordered_hash(s2, max) << std::endl;

    return 0;
}