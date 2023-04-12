#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "../Model/Model.h"
#include "../View/mainwindow.h"
#include "../View/ui_mainwindow.h"
#include <chrono>
#include <thread>
#include <QObject>
#include <QStatusBar>
#include <QKeyEvent>

class GameController : public QObject{
    Q_OBJECT
public:
    GameController(QStatusBar *statusBar, Ui::MainWindow *ui, QObject *parent);
    void initGame(QString &content);
    Direction temp_dir;
public slots:
    void onFileLoaded(QString content);
private:
    QStatusBar *statusBar;
    Ui::MainWindow *ui;
    bool eventFilter(QObject* obj, QEvent* event);
};

class InterfaceController : public QObject{
    Q_OBJECT
public:
    InterfaceController(QStatusBar *statusBar, Ui::MainWindow *ui, QObject *parent);
signals:
    void fileLoaded(QString content);
public slots:
    void loadFile();
    void saveFile();
    void displayHelp();
private:
    QStatusBar *statusBar;
    Ui::MainWindow *ui;
};

#endif // GAMECONTROLLER_H
