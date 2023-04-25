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
    GHOST,
    INVALID
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
    Position get_next_position();

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
    int get_health();
    void take_damage();
};

/**
 * Ghost class
 */
class Ghost : public Character {
public:
    Ghost();
    void calculate_direction(std::vector<std::vector<MapObject>> map_layout, Mapsize map_size);
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
    TargetPos* target_pos;

    Map();
    std::vector<std::vector<MapObject>> get_layout();
    // creates map from input and calls char2mapObject
    void load_map(int width, int height, std::string map);
    // converts char to MapObject
    MapObject char2mapObject(char c);
    // frees memory of static objects
    void free_map_objects();

    MapObject get_object(int x, int y);
};

/**
 * Game class
 */
class Game {
private:
    Mapsize map_size;
    void init_pacman(int health);
    void init_ghosts(std::vector<Position> ghost_positions);
public:
    Pacman* pacman;
    Ghost** ghosts;
    Map* map;
    int num_ghosts;
    bool is_over;
    bool is_paused;
    bool contains_key = false;
    bool key_collected = false;

    Game();

    void init_map();

    int parse_map(QString &content);

    int get_width();

    int get_height();

    void check_collision();

    void free_objects();
};

#endif // MODEL_H
