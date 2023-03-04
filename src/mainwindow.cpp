#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QLabel"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QLabel* scoreLabel = new QLabel("Score: 0");
    statusBar()->addPermanentWidget(scoreLabel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

