#include "Controller.h"

GameController::GameController(QStatusBar *statusBar, Ui::MainWindow *ui, QObject *parent) :
    statusBar(statusBar), ui(ui), QObject(parent)
{
    ui->centralwidget->installEventFilter(this);
}

void GameController::onFileLoaded(QString content) {
    initGame(content);
}

void GameController::initGame(QString &content) {
    Game game;
    game.init_map();
    game.is_over = false;

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

    game.init_pacman(1);
    game.init_ghosts();

    game.pacman->start_position({game.map->start_pos->get_position_x(), game.map->start_pos->get_position_y()});
    game.pacman->set_direction(Direction::NONE);

    auto start = std::chrono::steady_clock::now();

    QCoreApplication* app = QCoreApplication::instance();

    // Start game loop
    while (true) {
        // keyboard input
        if (app->eventDispatcher()->hasPendingEvents()) {
            app->processEvents();
            if (temp_dir != Direction::NONE) {
                game.pacman->set_direction(temp_dir);
                temp_dir = Direction::NONE;
            }
        }

        // model update
        game.check_collision();
        std::cout << "Pacman position: " << game.pacman->get_position_x() << " " << game.pacman->get_position_y() << std::endl;

        // view update

        if (game.is_over) break;

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    // Display map - delete this later - view should handle this
    game.map->print_map(*ui->textBrowser);

    // cleanup memory
    game.map->free_map_objects();
    game.free_objects();
}

bool GameController::eventFilter(QObject* obj, QEvent* event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        switch (keyEvent->key()) {
        case Qt::Key_Up:
        case Qt::Key_W:
            std::cout << "UP" << std::endl;
            temp_dir = Direction::UP;
            break;
        case Qt::Key_Down:
        case Qt::Key_S:
            std::cout << "DOWN" << std::endl;
            temp_dir = Direction::DOWN;
            break;
        case Qt::Key_Left:
        case Qt::Key_A:
            std::cout << "LEFT" << std::endl;
            temp_dir = Direction::LEFT;
            break;
        case Qt::Key_Right:
        case Qt::Key_D:
            std::cout << "RIGHT" << std::endl;
            temp_dir = Direction::RIGHT;
            break;
        }
        return true;
    }
    return false;
}