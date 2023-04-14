#include "Model.h"

/**
 * Game class
 */
Game::Game() {
    std::cout << "[+] Game object created" << std::endl;
}

void Game::init_pacman(int health) {
    this->pacman = new Pacman(health);
}

void Game::init_ghosts() {
    this->ghosts = new Ghost*[this->num_ghosts];
    for (int i = 0; i < this->num_ghosts; i++) {
        this->ghosts[i] = new Ghost();
    }
}

void Game::init_map() {
    this->map = new Map();
}

int Game::parse_map(QString &content) {
    std::stringstream ss(content.toStdString());
    ss >> this->map_size.width >> this->map_size.height;

    std::string map_layout;
    int num_startpos = 0; int num_targetpos = 0; int num_keys = 0;
    this->num_ghosts = 0;

    char c;
    int i = -1; // We don't count first line with width and height declaration
    int j = 0;
    while (ss.get(c)) {
        if (c != ' ' && c != '\n') {
            map_layout.push_back(c);
        }

        switch (c) {
        case 'G':
            this->num_ghosts++;
            break;
        case 'K':
            num_keys++;
            this->contains_key = true;
            this->map->key = new Key({j, i});
            break;
        case 'S':
            num_startpos++;
            this->map->start_pos = new StartPos({j, i});
            break;
        case 'T':
            num_targetpos++;
            this->map->target_pos = new TargetPos({j, i});
            break;
        default:
            break;
        }

        j++;
        if (c == '\n') {
            i++;
            j = 0;
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

void Game::check_collision() {
    // Calculate next position
    Position next_position;

    switch (this->pacman->get_direction()) {
    case Direction::UP:
        //std::cout << "UP" << std::endl;
        next_position = {this->pacman->get_position_x(), this->pacman->get_position_y()-1};
        break;
    case Direction::DOWN:
        //std::cout << "DOWN" << std::endl;
        next_position = {this->pacman->get_position_x(), this->pacman->get_position_y()+1};
        break;
    case Direction::LEFT:
        //std::cout << "LEFT" << std::endl;
        next_position = {this->pacman->get_position_x()-1, this->pacman->get_position_y()};
        break;
    case Direction::RIGHT:
        //std::cout << "RIGHT" << std::endl;
        next_position = {this->pacman->get_position_x()+1, this->pacman->get_position_y()};
        break;
    case Direction::NONE:
        return;
    }

    // Check if next position is out of bounds
    if (next_position.x < 0 || next_position.x >= this->map_size.width) {
        return;
    }
    if (next_position.y < 0 || next_position.y >= this->map_size.height) {
        return;
    }

    // Check if next position is a wall
    if (this->map->get_layout()[next_position.y][next_position.x] == WALL) {
        return;
    }

    // Check if next position is a ghost
    for (int i = 0; i < this->num_ghosts; i++) {
        if (this->ghosts[i]->get_position_x() == next_position.x
            && this->ghosts[i]->get_position_y() == next_position.y) {
            return;
            // TODO: Game over
        }
    }

    // Check if next position is a key
    if (this->contains_key) {
        if (this->map->key->get_position_x() == next_position.x
            && this->map->key->get_position_y() == next_position.y) {
            this->key_collected = true;
            // TODO: remove key from map
        }
    }

    // Target collision
    bool target_reached = false;

    if (this->pacman->get_position_x() == this->map->target_pos->get_position_x()
         && this->pacman->get_position_y() == this->map->target_pos->get_position_y()) {
        target_reached = true;
    }
    if (this->contains_key) {
        if (this->key_collected && target_reached) {
            this->is_over = true;
            // TODO: Win
        }
    } else {
        if (target_reached) {
            this->is_over = true;
            // TODO: Win
        }
    }

    // Move pacman
    this->pacman->update_position();
}

void Game::free_objects() {
    delete this->pacman;
    for (int i = 0; i < this->num_ghosts; i++) {
        delete this->ghosts[i];
    }
    delete this->ghosts;
    delete this->map;
}

