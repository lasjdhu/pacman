#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <QString>
#include <QTextBrowser>

struct Position {
    int x;
    int y; 
};

struct Mapsize {
    int width;
    int height;
};

typedef enum {
    EMPTY,
    WALL,
    KEY,
    START,
    TARGET,
    GHOST
} MapObject;

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
} Direction;

/**
 * Character class
 */
class Character {
private:
    Position pos;
    Direction dir;
public:
    Character();

    void start_position(Position pos);

    Direction get_direction();
    void set_direction(Direction dir);

    int get_position_x();
    int get_position_y();
    void update_position();
};

/**
 * Pacman class
 */
class Pacman : public Character {
private:
    int health;
public:
    Pacman(int health);
};

/**
 * Ghost class
 */
class Ghost : public Character {
public:
    Ghost();
};

/**
 * StaticMapObjects class
 */
class StaticMapObjects {
private:
    Position pos;
public:
    StaticMapObjects(Position pos);
    int get_position_x();
    int get_position_y();
};

// Key map object
class Key : public StaticMapObjects {
public:
    Key(Position pos);
};

// Starting position
class StartPos : public StaticMapObjects {
public:
    StartPos(Position pos);
};

// Target position
class TargetPos : public StaticMapObjects {
public:
    TargetPos(Position pos);
};

/**
 * Map class
 */
class Map {
private:
    std::vector <std::vector <MapObject>> map_layout;
public:
    Key* key;
    StartPos* start_pos;
    TargetPos* target_pos;

    Map();
    std::vector<std::vector<MapObject>> get_layout();
    // creates map from input and calls char2mapObject
    void load_map(int width, int height, std::string map);
    // converts char to MapObject
    MapObject char2mapObject(char c);
    // print map on a screen
    void print_map(QTextBrowser &text);
    // frees memory of static objects
    void free_map_objects();
};

/**
 * Game class
 */
class Game {
private:
    Mapsize map_size;
    int num_ghosts;
public:
    Pacman* pacman;
    Ghost** ghosts;
    Map* map;
    bool is_over;
    bool is_paused;
    bool contains_key = false;
    bool key_collected = false;

    Game();

    void init_pacman(int health);

    void init_ghosts();

    void init_map();

    int parse_map(QString &content);

    void check_collision();

    void free_objects();
};

#endif // MODEL_H
