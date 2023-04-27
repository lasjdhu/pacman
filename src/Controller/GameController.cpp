#include "Controller.h"

GameController::GameController(QStatusBar *statusBar, Ui::MainWindow *ui, QObject *parent) :
    statusBar(statusBar), ui(ui), QObject(parent)
{
    ui->centralwidget->installEventFilter(this);
}

void GameController::onFileLoaded(QString content) {
    runGame(content);
}

Game* GameController::getGame() {
    return game;
}

void GameController::runGame(QString &content) {
    game = new Game;
    game->init_map();
    game->is_over = false;

    switch (game->parse_map(content)) {
    case -1:
        statusBar->showMessage("[X] ERROR: Map needs to have specified starting position");
        game->map->free_map_objects();
        return;
    case -2:
        statusBar->showMessage("[X] ERROR: Map needs to have specified target position");
        game->map->free_map_objects();
        return;
    case -3:
        // Maybe not count this as an error?
        statusBar->showMessage("[X] ERROR: Map has more than one key");
        game->map->free_map_objects();
        return;
    default:
        break;
    }

    gameWidget = new GameWidget(game);

    QVBoxLayout *layout = new QVBoxLayout(ui->centralwidget);
    layout->addWidget(gameWidget);
    layout->setAlignment(Qt::AlignCenter);
    ui->centralwidget->setLayout(layout);

    // Set up a timer to update the game state every 100 ms
    timer.setInterval(300);
    timer.start();
    QObject::connect(&timer, &QTimer::timeout, [this](){
        if (temp_dir != Direction::NONE) {
            game->pacman->set_direction(temp_dir);
            temp_dir = Direction::NONE;
        }

        game->check_collision();

        //std::cout << "Pacman position: " << game->pacman->get_position_x() << " " << game->pacman->get_position_y() << std::endl;

        gameWidget->updateGameState(game);

        // TODO: is_over || is_win
        if (game->is_over) {
            timer.stop();
            // cleanup memory
            game->map->free_map_objects();
            game->free_objects();
            delete gameWidget;
            gameWidget = nullptr;
            delete game;
            game = nullptr;
        }
    });
}

bool GameController::eventFilter(QObject* obj, QEvent* event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        switch (keyEvent->key()) {
        case Qt::Key_Up:
        case Qt::Key_W:
            temp_dir = Direction::UP;
            break;
        case Qt::Key_Down:
        case Qt::Key_S:
            temp_dir = Direction::DOWN;
            break;
        case Qt::Key_Left:
        case Qt::Key_A:
            temp_dir = Direction::LEFT;
            break;
        case Qt::Key_Right:
        case Qt::Key_D:
            temp_dir = Direction::RIGHT;
            break;
        }
        return true;
    }
    return false;
}
