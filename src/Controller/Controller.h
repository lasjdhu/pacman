#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "../Model/Model.h"
#include "../View/mainwindow.h"
#include "../View/ui_mainwindow.h"
#include <QObject>
#include <QStatusBar>
#include <QKeyEvent>
#include <QTimer>

class GameWidget;

class GameController : public QObject{
    Q_OBJECT
public:
    GameController(QStatusBar *statusBar, Ui::MainWindow *ui, QObject *parent);
    void runGame(QString &content);
    Game* getGame();
    Direction temp_dir;
public slots:
    void onFileLoaded(QString content);
private:
    QStatusBar *statusBar;
    QTimer timer;
    Game *game;
    GameWidget *gameWidget;
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
    void saveFile(Game *game);
    void displayHelp();
private:
    QStatusBar *statusBar;
    Ui::MainWindow *ui;
};

#endif // GAMECONTROLLER_H
