#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Add label to the right
    QLabel* scoreLabel = new QLabel("");
    statusBar()->addPermanentWidget(scoreLabel);

    InterfaceController *interface = new InterfaceController(statusBar(), ui, this);
    GameController *game = new GameController(statusBar(), ui, this);

    QTimer::singleShot(0, interface, &InterfaceController::loadFile);
    statusBar()->showMessage("Please select your map");
    // Set listener for onFileLoaded signal
    connect(interface, &InterfaceController::fileLoaded, game, &GameController::onFileLoaded);

    // Load file
    connect(ui->actionLoad, &QAction::triggered, interface, &InterfaceController::loadFile);
    // Save file
    connect(ui->actionSave, &QAction::triggered, [=]() { interface->saveFile(game->getGame()); });
    // Show help
    connect(ui->actionUsage, &QAction::triggered, interface, &InterfaceController::displayHelp);
}

MainWindow::~MainWindow() {
    delete ui;
}
