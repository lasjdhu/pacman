#include "game_objects.h"

/**
 * Character class
 */
Character::Character(int speed) {
    this->speed = speed;

    std::cout << "[+] Character object created" << std::endl;
}

void Character::set_position(Position pos) {
    this->pos = pos;

    std::cout << "Character position set" << std::endl;
}

/**
 * Pacman class
 */
Pacman::Pacman(int speed, int health) : Character(speed) {
    this->health = health;

    std::cout << "[+] Pacman object created" << std::endl;
}

void Pacman::Move() {
    std::cout << "Pacman moved" << std::endl;
}

/**
 * Ghost class
 */
Ghost::Ghost(int speed) : Character(speed) {
    std::cout << "[+] Ghost object created" << std::endl;
}

void Ghost::Move() {
    std::cout << "Ghost moved" << std::endl;
}

/**
 * StaticMapObjects class
 */
StaticMapObjects::StaticMapObjects(Position pos) {
    this->pos = pos;
}

Key::Key(Position pos) : StaticMapObjects(pos) {
    std::cout << "[+] Key object created on (" << 
        pos.x << ", " << pos.y << ")" << std::endl;
}

StartPos::StartPos(Position pos) : StaticMapObjects(pos) {
    std::cout << "[+] Start object created on (" << 
        pos.x << ", " << pos.y << ")" << std::endl;
}

TargetPos::TargetPos(Position pos) : StaticMapObjects(pos) {
    std::cout << "[+] Target object created on (" << 
        pos.x << ", " << pos.y << ")" << std::endl;
}

/**
 * Map class
 */
Map::Map() {
    std::cout << "[+] Map object created" << std::endl;
}

void Map::load_map(int width, int height, std::string map) {
    this->map_layout.resize(height);

    for (int i = 0; i < map.size(); ++i) {
        int pos_x = i % width;
        int pos_y = i / width;

        if (pos_x == 0) {
            this->map_layout[pos_y].resize(width);
        }

        this->map_layout[pos_y][pos_x] = char2mapObject(map[i]);
    }

    std::cout << "[+] Map loaded" << std::endl;
}

MapObject Map::char2mapObject(char c) {
    switch (c) {
        case '.':
            return MapObject::EMPTY;
        case 'X':
            return MapObject::WALL;
        case 'S':
            return MapObject::START;
        case 'T':
            return MapObject::TARGET;
        case 'G':
            return MapObject::GHOST;
        case 'K':
            return MapObject::KEY;
        default:
            return MapObject::EMPTY;
    }
}

void Map::print_map() {
    for (int i = 0; i < this->map_layout.size(); i++) {
        for (int j = 0; j < this->map_layout[i].size(); j++) {
            std::cout << this->map_layout[i][j];
        }
        std::cout << std::endl;
    }
}

void Map::free_map_objects() {
    delete this->start_pos;
    delete this->target_pos;
    delete this->key;
}

/**
 * Game class
 */
Game::Game() {
    std::cout << "[+] Game object created" << std::endl;
}

void Game::init_pacman(int speed, int health) {
    this->pacman = new Pacman(speed, health);
}

void Game::init_ghosts(int speed) {
    this->ghosts = new Ghost*[this->num_ghosts];
    for (int i = 0; i < this->num_ghosts; i++) {
        this->ghosts[i] = new Ghost(speed);
    }
}

void Game::init_map() {
    this->map = new Map();
}

int Game::parse_map() {
    std::string line;
    std::getline(std::cin, line);
    std::stringstream ss(line);
    ss >> this->map_size.width >> this->map_size.height;

    std::string map_layout;
    int num_startpos = 0; int num_targetpos = 0; int num_keys = 0;

    char c;
    for(int i = 0, j = 0; (c = std::getchar()) != EOF; i++) {
        if (c == ' ' || c == '\n') {
            ++j;
            continue;
        }
        map_layout.push_back(c);

        switch (c) {
        case 'G':
            this->num_ghosts++;
            break;
        case 'K':
            num_keys++;
            this->has_key = true;
            this->map->key = new Key({j, i % this->map_size.width});
            break;
        case 'S':
            num_startpos++;
            this->map->start_pos = new StartPos({j, i % this->map_size.width});
            break;
        case 'T':
            num_targetpos++;
            this->map->target_pos = new TargetPos({j, i % this->map_size.width});
            break;
        default:
            break;
        }
    }

    // we can add more checks here later

    if (num_startpos != 1) return -1;

    if (num_targetpos != 1) return -2;

    if (num_keys > 1) return -3;

    // load map 
    this->map->load_map(this->map_size.width, this->map_size.height, map_layout);

    return 0;
}

void Game::free_objects() {
    delete this->pacman;
    for (int i = 0; i < this->num_ghosts; i++) {
        delete this->ghosts[i];
    }
    delete this->ghosts;
    delete this->map;
}

void Game::Start() {
    std::cout << "Game started" << std::endl;
}

void Game::End() {
    std::cout << "Game ended" << std::endl;
}

void Game::Pause() {
    std::cout << "Game paused" << std::endl;
}

void Game::Resume() {
    std::cout << "Game resumed" << std::endl;
}

void Game::Restart() {
    std::cout << "Game restarted" << std::endl;
}

void Game::Update() {
    std::cout << "Game updated" << std::endl;
}

void Game::Draw() {
    std::cout << "Game drawn" << std::endl;
}

/* Uncomment for testing */
/*
int main() {
    Game game;
    game.init_map();

    switch (game.parse_map()) {
    case -1:
        std::cerr << "[X] ERROR: Map needs to have specified starting position" << std::endl;
        game.map->free_map_objects();
        return 1;
    case -2:
        std::cerr << "[X] ERROR: Map needs to have specified target position" << std::endl;
        game.map->free_map_objects();
        return 1;
    case -3:
        // Maybe not count this as an error?
        std::cerr << "[X] ERROR: Map has more than one key" << std::endl;
        game.map->free_map_objects();
        return 1;
    default:
        break;
    }

    game.map->print_map();

    game.init_pacman(1, 1);
    game.init_ghosts(1);

    // cleanup memory
    game.map->free_map_objects();
    game.free_objects();
    return 0;
}
*/