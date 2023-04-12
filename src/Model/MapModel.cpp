#include "Model.h"

/**
 * Map class
 */
Map::Map() {
    std::cout << "[+] Map object created" << std::endl;
}

std::vector<std::vector<MapObject>> Map::get_layout() {
    return this->map_layout;
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

void Map::print_map(QTextBrowser &text) {
    for (int i = 0; i < this->map_layout.size(); i++) {
        for (int j = 0; j < this->map_layout[i].size(); j++) {
            text.insertPlainText(QString::number(this->map_layout[i][j]));
        }
        text.insertPlainText("\n");
    }
}

void Map::free_map_objects() {
    delete this->start_pos;
    delete this->target_pos;
    delete this->key;
}

/**
 * StaticMapObjects class
 */
StaticMapObjects::StaticMapObjects(Position pos) {
    this->pos = pos;
}

int StaticMapObjects::get_position_x() {
    return this->pos.x;
}

int StaticMapObjects::get_position_y() {
    return this->pos.y;
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
