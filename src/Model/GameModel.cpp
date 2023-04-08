#include "Model.h"

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
            this->has_key = true;
            this->map->key = new Key({i, j});
            break;
        case 'S':
            num_startpos++;
            this->map->start_pos = new StartPos({i, j});
            break;
        case 'T':
            num_targetpos++;
            this->map->target_pos = new TargetPos({i, j});
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
