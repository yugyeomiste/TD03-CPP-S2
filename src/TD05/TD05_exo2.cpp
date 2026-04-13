#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <fstream>

enum class Direction { Haut, Droite, Bas, Gauche };

struct Position {
    int x;
    int y;

    bool operator==(Position const& other) const {
        return x == other.x && y == other.y;
    }

    Position& operator+=(Position const& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
};

std::ostream& operator<<(std::ostream& os, Position const& p) {
    return os << "(" << p.x << ", " << p.y << ")";
}

Position dir_to_pos(Direction d) {
    switch (d) {
        case Direction::Haut:   return {0, -1};
        case Direction::Droite: return {1, 0};
        case Direction::Bas:    return {0, 1};
        case Direction::Gauche: return {-1, 0};
    }
    return {0, 0};
}

Position operator+(Position const& p, Direction const& d) {
    Position move = dir_to_pos(d);
    return {p.x + move.x, p.y + move.y};
}

Direction turn_right(Direction const& d) {
    switch (d) {
        case Direction::Haut:   return Direction::Droite;
        case Direction::Droite: return Direction::Bas;
        case Direction::Bas:    return Direction::Gauche;
        case Direction::Gauche: return Direction::Haut;
    }
    return Direction::Haut;
}

// Hash pour utiliser Position dans un unordered_set
namespace std {
    template <>
    struct hash<Position> {
        std::size_t operator()(const Position& pos) const {
            return hash<int>()(pos.x) ^ (hash<int>()(pos.y) << 1);
        }
    };
}

struct GuardState {
    Position pos;
    Direction dir;
    
    bool operator==(const GuardState& other) const {
        return pos == other.pos && dir == other.dir;
    }
};

// Hash pour detecter les boucles
namespace std {
    template <>
    struct hash<GuardState> {
        std::size_t operator()(const GuardState& state) const {
            return hash<Position>()(state.pos) ^ (hash<int>()(static_cast<int>(state.dir)) << 1);
        }
    };
}

struct Input_Structure {
    Position start_pos;
    Direction start_dir;
    std::unordered_set<Position> obstacles;
    int width = 0;
    int height = 0;
};

Input_Structure read_input(std::istream& input_stream) {
    Input_Structure data;
    std::string line;
    int y = 0;
    
    while (std::getline(input_stream, line) && !line.empty()) {
        data.width = line.size();
        for (int x = 0; x < line.size(); ++x) {
            char c = line[x];
            if (c == '#') data.obstacles.insert({x, y});
            else if (c == '^') { data.start_pos = {x, y}; data.start_dir = Direction::Haut; }
            else if (c == '>') { data.start_pos = {x, y}; data.start_dir = Direction::Droite; }
            else if (c == 'v') { data.start_pos = {x, y}; data.start_dir = Direction::Bas; }
            else if (c == '<') { data.start_pos = {x, y}; data.start_dir = Direction::Gauche; }
        }
        y++;
    }
    data.height = y;
    return data;
}

struct WalkResult {
    Position final_position;
    size_t steps_taken = 0;
    std::unordered_set<Position> visited_positions;
    bool is_loop = false; 
};

WalkResult simulate_guard(Input_Structure const& map_data) {
    WalkResult result;
    Position current_pos = map_data.start_pos;
    Direction current_dir = map_data.start_dir;
    
    std::unordered_set<GuardState> visited_states;
    
    result.visited_positions.insert(current_pos);
    visited_states.insert({current_pos, current_dir});
    
    while (true) {
        Position next_pos = current_pos + current_dir;
        
        // Verifie si on sort de la map
        if (next_pos.x < 0 || next_pos.x >= map_data.width || 
            next_pos.y < 0 || next_pos.y >= map_data.height) {
            result.final_position = next_pos;
            break; 
        }
        
        // Verifie les murs
        if (map_data.obstacles.find(next_pos) != map_data.obstacles.end()) {
            current_dir = turn_right(current_dir);
        } else {
            current_pos = next_pos;
            result.visited_positions.insert(current_pos); 
            result.steps_taken++;
        }

        // Detection de boucle infinie
        GuardState current_state = {current_pos, current_dir};
        if (visited_states.find(current_state) != visited_states.end()) {
            result.is_loop = true;
            break; 
        }
        visited_states.insert(current_state);
    }
    
    return result;
}

int main() {
    // Lecture du fichier test 
    std::ifstream file("/Users/romana/TD03 CPP S2/src/TD05/input_guard_patrol.txt");

    if (!file) {
        std::cerr << "Erreur fichier" << std::endl;
        return 1;
    }

    Input_Structure data = read_input(file);
    WalkResult resultat = simulate_guard(data);
    
    std::cout << "Partie 1 : cases visitees : " << resultat.visited_positions.size() << std::endl;

    int boucles_trouvees = 0;
    for (const Position& pos : resultat.visited_positions) {
        if (pos == data.start_pos) continue;

        Input_Structure test_data = data;
        test_data.obstacles.insert(pos); 

        WalkResult test_result = simulate_guard(test_data);
        if (test_result.is_loop) {
            boucles_trouvees++;
        }
    }

    std::cout << "Partie 2: boucles trouvees : " << boucles_trouvees << std::endl;

    return 0;
}