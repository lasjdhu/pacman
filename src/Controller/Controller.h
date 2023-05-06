/**
 * Header file for both Interface and Game controllers
 * @file Controller.h
 * @authors Name Surname(xlogin00), Dmitrii Ivanushkin (xivanu00)
 */

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "../Model/Model.h"
#include "../View/mainwindow.h"
#include "../View/ui_mainwindow.h"
#include <QObject>
#include <QStatusBar>
#include <QKeyEvent>
#include <QTimer>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

class GameWidget;
class EndWidget;

/**
 * GameController class
 */
class GameController : public QObject{
    Q_OBJECT
public:
    /**
     * GameController constructor
     * @param *statusBar pointer to statusBar from MainWindow
     * @param *ui pointer to ui from MainWindow
     * @param *parent pointer to a parent widget
     */
    GameController(QStatusBar *statusBar, Ui::MainWindow *ui, QObject *parent);

    /**
     * Main thread with all processes for Game instance
     * @param &content content of map from text file
     */
    void runGame(QString &content);

    /**
     * Get actual state of game instance
     */
    Game* getGame();

    /**
     * All widgets manager
     */
    void initWidgets();

    Direction temp_dir;
public slots:
    /**
     * Run new Game instance when file is loaded
     * @param content content of map from text file
     */
    void onFileLoaded(QString content);

    /**
     * Run new Game instance when game is restarted
     * @param content content of map from text file
     */
    void onGameRestarted(QString content);

    /**
     * Replay game
     */
    void replayGame();
private:
    QStatusBar *statusBar;
    QTimer timer;
    Game *game;
    GameWidget *gameWidget;
    EndWidget *endWidget = nullptr;
    QLabel *stepsLabel;
    QLabel *healthLabel;
    QPushButton *backButton;
    QPushButton *forwardButton;
    QVBoxLayout *layout;
    int number_tries = 1;
    Ui::MainWindow *ui;

    /**
     * User input from keyboard to Pacman moving
     * @param *obj
     * @param *event pointer to a key event
     */
    bool eventFilter(QObject *obj, QEvent *event);
};

/**
 * InterfaceController class
 */
class InterfaceController : public QObject{
    Q_OBJECT
public:
    /**
     * InterfaceController constructor
     * @param *statusBar pointer to statusBar from MainWindow
     * @param *ui pointer to ui from MainWindow
     * @param *parent pointer to a parent widget
     */
    InterfaceController(QStatusBar *statusBar, Ui::MainWindow *ui, QObject *parent);
signals:
    /**
     * signal from 'Load Game' button
     * @param content content of map from text file
     */
    void fileLoaded(QString content);
public slots:
    /**
     * Load map from text file
     */
    void loadFile();

    /**
     * Save current game state to file
     * @param game Game state - map
     */
    void saveFile(Game *game);

    /**
     * Display basic usage
     */
    void displayHelp();
private:
    QStatusBar *statusBar;
    Ui::MainWindow *ui;
};

#endif // GAMECONTROLLER_H
