#include "Controller.h"

GameController::GameController(QStatusBar *statusBar, Ui::MainWindow *ui, QObject *parent) :
    statusBar(statusBar), ui(ui), QObject(parent)
{}

void GameController::onFileLoaded(QString content) {
    initGame(content);
}

void GameController::initGame(QString &content) {
    Game game;
    game.init_map();

    switch (game.parse_map(content)) {
    case -1:
        statusBar->showMessage("[X] ERROR: Map needs to have specified starting position");
        game.map->free_map_objects();
        return;
    case -2:
        statusBar->showMessage("[X] ERROR: Map needs to have specified target position");
        game.map->free_map_objects();
        return;
    case -3:
        // Maybe not count this as an error?
        statusBar->showMessage("[X] ERROR: Map has more than one key");
        game.map->free_map_objects();
        return;
    default:
        break;
    }

    // Display map
    game.map->print_map(*ui->textBrowser);

    game.init_pacman(1, 1);
    game.init_ghosts(1);

    // cleanup memory
    game.map->free_map_objects();
    game.free_objects();
}
