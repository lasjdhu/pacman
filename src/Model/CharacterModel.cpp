#include "Model.h"

/**
 * Character class
 */
Character::Character() {

    std::cout << "[+] Character object created" << std::endl;
}

void Character::start_position(Position pos) {
    this->pos = pos;

    std::cout << "Start position set" << std::endl;
}

Direction Character::get_direction() {
    return this->dir;
}

void Character::set_direction(Direction dir) {
    this->dir = dir;

    std::cout << "Direction set" << std::endl;
}   

int Character::get_position_x() {
    return this->pos.x;
}
int Character::get_position_y() {
    return this->pos.y;
}

void Character::update_position() {
    switch (this->dir) {
    case Direction::UP:
        this->pos.y--;
        break;
    case Direction::DOWN:
        this->pos.y++;
        break;
    case Direction::LEFT:
        this->pos.x--;
        break;
    case Direction::RIGHT:
        this->pos.x++;
        break;
    default:
        break;
    }

    std::cout << "Position updated" << std::endl;
}

/**
 * Pacman class
 */
Pacman::Pacman(int health) {
    this->health = health;

    std::cout << "[+] Pacman object created" << std::endl;
}

/**
 * Ghost class
 */
Ghost::Ghost() {
    std::cout << "[+] Ghost object created" << std::endl;
}
