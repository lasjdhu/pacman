#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "game_objects.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Add label
    QLabel* scoreLabel = new QLabel("");
    statusBar()->addPermanentWidget(scoreLabel);
    statusBar()->showMessage("No file loaded");

    // Load file
    connect(ui->actionLoad, &QAction::triggered, this, &MainWindow::loadFile);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::loadFile() {
    // Get filename
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text Files (*.txt)"));
    if (filename.isEmpty()) {
        statusBar()->showMessage("No file loaded");
        return;
    }

    // Open file
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        statusBar()->showMessage("Failed to load file");
        return;
    }

    // Read content, get strings and convert them to a byte array
    QTextStream in(&file);
    QString content = in.readAll();

    file.close();
    statusBar()->showMessage(tr("File \"%1\" loaded").arg(filename));

    initGame(content);
}

void MainWindow::initGame(const QString& content) {
    Game game;
    game.init_map();

    switch (game.parse_map(content)) {
    case -1:
        statusBar()->showMessage("[X] ERROR: Map needs to have specified starting position");
        game.map->free_map_objects();
        return;
    case -2:
        statusBar()->showMessage("[X] ERROR: Map needs to have specified target position");
        game.map->free_map_objects();
        return;
    case -3:
        // Maybe not count this as an error?
        statusBar()->showMessage("[X] ERROR: Map has more than one key");
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
