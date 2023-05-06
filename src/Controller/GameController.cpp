/**
 * Logic of Game events and main thread as CONTROLLER
 * @file GameController.cpp
 * @authors Name Surname(xlogin00), Dmitrii Ivanushkin (xivanu00)
 */

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

void GameController::onGameRestarted(QString content) {
    endWidget->hide();
    onFileLoaded(content);
}

void GameController::runGame(QString &content) {
    if (ui->centralwidget->layout()) {
        delete ui->centralwidget->layout();
    }

    game = new Game;
    game->init_map();
    game->set_gamestate(GameState::RUNNING);

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
        statusBar->showMessage("[X] ERROR: Map has more than one key");
        game->map->free_map_objects();
        return;
    default:
        break;
    }

    gameWidget = new GameWidget(game);
    stepsLabel = new QLabel(gameWidget);
    stepsLabel->setText(QString("Steps: %1").arg(game->pacman->get_steps()));
    stepsLabel->setStyleSheet("QLabel { color: white; font-size: 16pt; }");

    healthLabel = new QLabel(gameWidget);
    healthLabel->setText(QString("Health: %1").arg(game->pacman->get_health()));
    healthLabel->setStyleSheet("QLabel { color: white; font-size: 16pt; }");

    QHBoxLayout *labelsLayout = new QHBoxLayout();
    labelsLayout->addWidget(stepsLabel);
    labelsLayout->addWidget(healthLabel);

    QVBoxLayout *layout = new QVBoxLayout(ui->centralwidget);
    layout->addLayout(labelsLayout);
    layout->addWidget(gameWidget);
    layout->setAlignment(Qt::AlignCenter);
    ui->centralwidget->setLayout(layout);

    QObject::disconnect(&timer, &QTimer::timeout, nullptr, nullptr);

    timer.setInterval(300);
    timer.start();

    QObject::connect(&timer, &QTimer::timeout, [this, layout, content](){
        if (temp_dir != Direction::NONE) {
            game->pacman->set_direction(temp_dir);
            temp_dir = Direction::NONE;
        }

        game->player_collision();
        game->ghost_collision();

        gameWidget->updateGameState(game);
        stepsLabel->setText(QString("Steps: %1").arg(game->pacman->get_steps()));
        healthLabel->setText(QString("Health: %1").arg(game->pacman->get_health()));

        if (game->get_gamestate() == GameState::OVER || game->get_gamestate() == GameState::WIN) {
            timer.stop();

            if (stepsLabel) {
                stepsLabel->deleteLater();
                stepsLabel = nullptr;
            }
            if (healthLabel) {
                healthLabel->deleteLater();
                healthLabel = nullptr;
            }

            if (endWidget == nullptr) {
                if (game->get_gamestate() == GameState::OVER) {
                    endWidget = new EndWidget(0, game->pacman->get_steps(), this->number_tries, content);
                    this->number_tries++;
                } else {
                    endWidget = new EndWidget(1, game->pacman->get_steps(), this->number_tries, content);
                    this->number_tries = 1;
                }
                layout->addWidget(endWidget);
                QObject::connect(endWidget, &EndWidget::gameRestarted, this, &GameController::onGameRestarted);
            } else {
                if (game->get_gamestate() == GameState::OVER) {
                    endWidget->updateContent(0, game->pacman->get_steps(), this->number_tries);
                    this->number_tries++;
                } else {
                    endWidget->updateContent(1, game->pacman->get_steps(), this->number_tries);
                    this->number_tries = 1;
                }
            }

            endWidget->show();
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

bool GameController::eventFilter(QObject *obj, QEvent *event) {
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
