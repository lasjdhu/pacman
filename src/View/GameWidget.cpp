#include "GameWidget.h"

const int TILE_SIZE = 50;

GameWidget::GameWidget(Game* game, QWidget* parent) :
    QWidget(parent),
    game(game)
{
    setFixedSize(game->get_width() * TILE_SIZE, game->get_height() * TILE_SIZE);
}

void GameWidget::updateGameState(Game* game) {
    update();
}

void GameWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    // Draw the map
    for (int y = 0; y < game->get_height(); y++) {
        for (int x = 0; x < game->get_width(); x++) {
            MapObject o = game->map->get_object(x, y);
            QRect rect(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
            QPixmap pixmap;
            QColor color;
            switch (o) {
            case WALL:
                color = Qt::blue;
                break;
            case TARGET:
                color = Qt::white;
                break;
            case KEY:
                if (game->key_collected == false) {
                    pixmap = QPixmap("../src/images/key.png");
                } else {
                    color = Qt::black;
                }
                break;
            default:
                break;
            }
            if (!pixmap.isNull()) {
                painter.drawPixmap(rect, pixmap);
            } else {
                painter.fillRect(rect, color);
            }
        }
    }
    // Draw the characters
    QPixmap pacmanPixmap("../src/images/pacman.png");
    QPixmap ghostPixmapBlue("../src/images/ghostBlue.png");
    QPixmap ghostPixmapRed("../src/images/ghostRed.png");
    painter.drawPixmap(game->pacman->get_position_x() * TILE_SIZE,
                       game->pacman->get_position_y() * TILE_SIZE,
                       TILE_SIZE, TILE_SIZE, pacmanPixmap);
    for (int i = 0; i < game->num_ghosts; ++i) {
        if (i % 2 == 0) {
            painter.drawPixmap(game->ghosts[i]->get_position_x() * TILE_SIZE,
                               game->ghosts[i]->get_position_y() * TILE_SIZE,
                               TILE_SIZE, TILE_SIZE, ghostPixmapBlue);
        } else {
            painter.drawPixmap(game->ghosts[i]->get_position_x() * TILE_SIZE,
                               game->ghosts[i]->get_position_y() * TILE_SIZE,
                               TILE_SIZE, TILE_SIZE, ghostPixmapRed);
        }
    }
}
