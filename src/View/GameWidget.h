#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include "../Controller/Controller.h"
#include <QtWidgets>

class GameWidget : public QWidget {
    Q_OBJECT
public:
    GameWidget(Game* game, QWidget* parent = nullptr);
    void updateGameState(Game* game);
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    Game *game;
};

#endif // GAMEWIDGET_H
