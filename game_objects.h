#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H

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

/**
 * Character class
 */
class Character {
protected:
    Position pos;
    int speed;
public:
    Character(int speed);

    void set_position(Position pos);
};

/**
 * Pacman class
 */
class Pacman : Character {
private:
    int health;
public:

    Pacman(int speed, int health);

    void Move();
};

/**
 * Ghost class
 */
class Ghost : Character {
public:
    Ghost(int speed);

    void Move();
};

/**
 * StaticMapObjects class
 */
class StaticMapObjects {
private:
    Position pos;
public:
    StaticMapObjects(Position pos);
};

// Key map object
class Key : StaticMapObjects {
public:
    Key(Position pos);
};

// Starting position
class StartPos : StaticMapObjects {
public:
    StartPos(Position pos);
};

// Target position
class TargetPos : StaticMapObjects {
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
    // creates map from input and calls char2mapObject
    void load_map(int width, int height, std::string map);
    // converts char to MapObject
    MapObject char2mapObject(char c);
    // for debugging
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
    Pacman* pacman;
    Ghost** ghosts;
    int num_ghosts;
    bool has_key = false;
    // maybe needed for later
    bool has_started = false;
    bool is_paused = false;
    bool is_over = false;
public:
    Map* map;

    Game();

    void init_pacman(int speed, int health);

    void init_ghosts(int speed);

    void init_map();

    int parse_map(QString &content);

    void free_objects();

    void Start();

    void End();

    void Pause();

    void Resume();

    void Restart();

    void Update();

    void Draw();
};
#endif // GAME_OBJECTS_H
