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

    // Call function that loads map when user runs application
    // (after ui is shown so delay is needed)
    QTimer::singleShot(0, this, &MainWindow::loadFile);
    statusBar()->showMessage("Please select your map");

    // Load file
    connect(ui->actionLoad, &QAction::triggered, this, &MainWindow::loadFile);
    // Save file
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveFile);
    // Show help
    connect(ui->actionUsage, &QAction::triggered, this, &MainWindow::displayHelp);
}

void MainWindow::initGame(QString& content) {
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

void MainWindow::loadFile() {
    // Get filename
    QString filename = QFileDialog::getOpenFileName(this, "Open File", "", "Text Files (*.txt)");
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
    statusBar()->showMessage(QString("File \"%1\" loaded").arg(filename));

    initGame(content);
}

void MainWindow::saveFile() {
    // Get filename
    QString filename = QFileDialog::getSaveFileName(this, "Save File", "", "Text Files (*.txt)");
    if (filename.isEmpty()) {
        statusBar()->showMessage("No file saved");
        return;
    }

    // Open file
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        statusBar()->showMessage("Failed to save file");
        return;
    }

    QString content = ui->textBrowser->toPlainText();

    QStringList rows = content.split("\n");

    while (!rows.isEmpty() && rows.last().isEmpty()) {
        rows.removeLast();
    }

    int numRows = rows.size();
    int numCols = numRows > 0 ? rows[0].size() : 0;

    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            QChar c = rows[i][j];
            if (c == '0') {
                rows[i][j] = '.';
            } else if (c == '1') {
                rows[i][j] = 'X';
            } else if (c == '2') {
                rows[i][j] = 'K';
            } else if (c == '3') {
                rows[i][j] = 'S';
            } else if (c == '4') {
                rows[i][j] = 'T';
            } else if (c == '5') {
                rows[i][j] = 'G';
            }
        }
    }

    QString sizes = QString("%1 %2").arg(numRows).arg(numCols);
    QString gameState = sizes + "\n" + rows.join("\n") + "\n";

    // Write gameState to a file
    QTextStream out(&file);
    out << gameState;

    file.close();
    statusBar()->showMessage(QString("File \"%1\" saved").arg(filename));
}

void MainWindow::displayHelp() {
    QString message = "Help is here";
    QMessageBox::information(this, "Help", message);
    statusBar()->showMessage("Help is shown");
}

MainWindow::~MainWindow() {
    delete ui;
}
