/**
 * Logic of Game events and main thread as CONTROLLER
 * @file GameController.cpp
 * @authors Jakub Kratochvil (xkrato67), Dmitrii Ivanushkin (xivanu00)
 */

#include "Controller.h"

GameController::GameController(QStatusBar *statusBar, Ui::MainWindow *ui, QObject *parent) :
    statusBar(statusBar), ui(ui), QObject(parent)
{
    ui->centralwidget->installEventFilter(this);
}

void GameController::runGame(QString &content) {
    if (ui->centralwidget->layout()) {
        delete ui->centralwidget->layout();
    }

    startMap = content;

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

    createTmp();
    initWidgets();

    QObject::disconnect(&timer, &QTimer::timeout, nullptr, nullptr);

    timer.setInterval(300);
    timer.start();

    QObject::connect(&timer, &QTimer::timeout, [this, content](){
        if (temp_dir != Direction::NONE) {
            game->pacman->set_direction(temp_dir);
            temp_dir = Direction::NONE;
        }

        game->player_collision();
        game->ghost_collision();

        for (int i = 0; i < game->get_ghost_count(); ++i) {
            log(game->pacman->get_position_x(),
                game->pacman->get_position_y(),
                i,
                game->ghosts[i]->get_position_x(),
                game->ghosts[i]->get_position_y());
        }

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
                QObject::connect(endWidget, &EndWidget::saveGameplay, this, &GameController::onSaveGameplay);
                QObject::connect(endWidget, &EndWidget::gameRestarted, this, &GameController::onGameRestarted);
            } else {
                if (game->get_gamestate() == GameState::OVER) {
                    endWidget->updateContent(0, game->pacman->get_steps(), this->number_tries);
                    this->number_tries++;
                } else {
                    endWidget->updateContent(1, game->pacman->get_steps(), this->number_tries);
                    this->number_tries = 1;
                }
                layout->addWidget(endWidget);
                QObject::connect(endWidget, &EndWidget::saveGameplay, this, &GameController::onSaveGameplay);
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

void GameController::createTmp() {
    QDir logDir("../src");

    if (!logDir.exists()) {
        if (!logDir.mkpath("../src")) {
            statusBar->showMessage("Failed to create tmp for log");
            return;
        }
    }

    logFilename = logDir.filePath("log.txt");
}

void GameController::log(int pacman_x, int pacman_y, int ghost, int ghost_x, int ghost_y) {
    index++;
    QFile file(logFilename);

    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        statusBar->showMessage("Failed to start log");
        return;
    }

    if (index == 1) {
        file.close();
        QFile::remove(logFilename);
        file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
    }

    QTextStream stream(&file);
    QString newString = QString("%1: %2,%3,%4,%5,%6\n").arg(index).arg(pacman_x).arg(pacman_y).arg(ghost).arg(ghost_x).arg(ghost_y);

    stream << newString;

    file.close();
}

void GameController::onSaveGameplay() {
    QString filename = QFileDialog::getSaveFileName(qobject_cast<QWidget*>(parent()),
                                                    "Save File",
                                                    "../examples/", "Log Files (*.out)");
    if (filename.isEmpty()) {
        statusBar->showMessage("No file saved");
        return;
    }

    QFile logFile(logFilename);
    if (logFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QFile newFile(filename);
        if (newFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream in(&logFile);
            QTextStream out(&newFile);
            out << startMap;
            out << in.readAll();
            newFile.close();
            logFile.close();
        }
    }

    QFile::remove(logFilename);
    statusBar->showMessage(QString("Gameplay \"%1\" saved").arg(filename));
}

void GameController::replay() {
    if (ui->centralwidget->layout()) {
        delete ui->centralwidget->layout();
    }

    backButton = new QPushButton("Back", ui->centralwidget);
    backButton->setStyleSheet("QPushButton {"
                              "    color: white;"
                              "    font-size: 16pt;"
                              "    background-color: #333333;"
                              "    border: none;"
                              "    padding: 10px 20px;"
                              "}"
                              "QPushButton:hover {"
                              "    background-color: #555555;"
                              "}"
                              "QPushButton:pressed {"
                              "    background-color: #777777;"
                              "}");
    forwardButton = new QPushButton("Forward", ui->centralwidget);
    forwardButton->setStyleSheet("QPushButton {"
                                 "    color: white;"
                                 "    font-size: 16pt;"
                                 "    background-color: #333333;"
                                 "    border: none;"
                                 "    padding: 10px 20px;"
                                 "}"
                                 "QPushButton:hover {"
                                 "    background-color: #555555;"
                                 "}"
                                 "QPushButton:pressed {"
                                 "    background-color: #777777;"
                                 "}");
    exitButton = new QPushButton("Exit", ui->centralwidget);
    exitButton->setStyleSheet("QPushButton {"
                                 "    color: white;"
                                 "    font-size: 16pt;"
                                 "    background-color: #333333;"
                                 "    border: none;"
                                 "    padding: 10px 20px;"
                                 "}"
                                 "QPushButton:hover {"
                                 "    background-color: #555555;"
                                 "}"
                                 "QPushButton:pressed {"
                                 "    background-color: #777777;"
                                 "}");


    QHBoxLayout *replayLayout = new QHBoxLayout();
    replayLayout->addWidget(backButton);
    replayLayout->addWidget(forwardButton);

    QString filename = QFileDialog::getOpenFileName(qobject_cast<QWidget*>(parent()),
                                                    "Open File",
                                                    "../examples/", "Log Files (*.out)");
    if (filename.isEmpty()) {
        statusBar->showMessage("No file loaded");
        return;
    }

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        statusBar->showMessage("Failed to load file");
        return;
    }

    QTextStream in(&file);
    QString content = in.readAll();

    QStringList lines = content.split('\n');
    int rows = lines[0].split(' ')[0].toInt();
    int cols = lines[0].split(' ')[1].toInt();
    lines.removeFirst();

    QString map = "";
    for (int i = 0; i < rows; i++) {
        QString line = lines[i];
        map += line;
    }

    for (int i = 0; i < rows; i++) {
        lines.removeFirst();
    }

    QString linesJoined = lines.join("\n");

    replayWidget = new ReplayWidget(rows, cols, map, linesJoined);

    layout = new QVBoxLayout(ui->centralwidget);
    layout->addWidget(replayWidget);
    layout->addLayout(replayLayout);
    layout->addWidget(exitButton);
    layout->setAlignment(Qt::AlignCenter);
    ui->centralwidget->setLayout(layout);

    connect(forwardButton, &QPushButton::clicked, [this]() mutable {
        line_number++;
        replayWidget->setIndex(line_number);
    });

    connect(backButton, &QPushButton::clicked, [this]() mutable {
        line_number--;
        replayWidget->setIndex(line_number);
    });

    connect(exitButton, &QPushButton::clicked, [this]() {
        qApp->exit();
    });

    file.close();
    statusBar->showMessage(QString("File \"%1\" loaded").arg(filename));
}

void GameController::onFileLoaded(QString content) {
    if (game != nullptr) {
        game->map->free_map_objects();
        game->free_objects();
        delete gameWidget;
        gameWidget = nullptr;
        delete game;
        game = nullptr;
    }
    if (stepsLabel != nullptr) {
        stepsLabel->deleteLater();
        stepsLabel = nullptr;
    }
    if (healthLabel != nullptr) {
        healthLabel->deleteLater();
        healthLabel = nullptr;
    }
    runGame(content);
}

void GameController::onGameRestarted(QString content) {
    endWidget->hide();
    onFileLoaded(content);
}

Game* GameController::getGame() {
    return game;
}

void GameController::initWidgets() {
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

    layout = new QVBoxLayout(ui->centralwidget);
    layout->addLayout(labelsLayout);
    layout->addWidget(gameWidget);
    layout->setAlignment(Qt::AlignCenter);
    ui->centralwidget->setLayout(layout);
}
