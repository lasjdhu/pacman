#include "Model.h"

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
