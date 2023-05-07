/**
 * Widget header file
 * @file GameWidget.h
 * @authors Name Surname(xlogin00), Dmitrii Ivanushkin (xivanu00)
 */

#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include "../Controller/Controller.h"
#include <QtWidgets>

/**
 * GameWidget class
 */
class GameWidget : public QWidget {
    Q_OBJECT
public:
    /**
     * GameWidget constructor
     * @param *game pointer to an object of Game class
     * @param *parent pointer to a parent widget
     */
    GameWidget(Game *game, QWidget *parent = nullptr);

    /**
     * Update game on the screen
     * @param game pointer to an object of Game class
     */
    void updateGameState(Game *game);
    /**
     * Update steps
     * @param steps count of steps
     */
    void updateSteps(int steps);
    /**
     * Update lives
     * @param steps count of steps
     */
    void updateLives(int health);
protected:
    /**
     * Paint rectangles and load assets to a widget
     * @param *event QPaintEvent
     */
    void paintEvent(QPaintEvent *event) override;
private:
    Game *game;
};

/**
 * EndWidget class
 */
class EndWidget : public QWidget {
    Q_OBJECT
public:
    /**
     * EndWidget constructor
     * @param mode Game Over (0) or Win (1)
     * @param steps count of steps
     * @param tries count of tries
     * @param content current map for restart
     * @param *parent pointer to a parent widget
     */
    EndWidget(int mode, int steps, int tries, QString content, QWidget *parent = nullptr);

    /**
     * Update widget
     * @param mode Game Over (0) or Win (1)
     * @param steps count of steps
     * @param tries count of tries
     */
    void updateContent(int mode, int steps, int tries);
signals:
    /**
     * signal from 'Restart' button
     * @param content content of map from text file
     */
    void gameRestarted(QString content);

    /**
     * signal from 'Save this gameplay' button
     */
    void saveGameplay();
private:
    QVBoxLayout *layout;
    QLabel *label;
    QLabel *labelSaved;
    QPushButton *exitButton;
    QPushButton *restartButton;
    QPushButton *saveButton;
};

#endif // WIDGET_H
