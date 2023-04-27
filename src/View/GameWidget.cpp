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
            QRectF rect(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
            QColor color;
            if (o == WALL) {
                color = Qt::blue;
            } else if (o == TARGET) {
                color = Qt::green;
            } else if (o == KEY) {
                color = Qt::red;
            } else {
                color = Qt::black;
            }
            painter.fillRect(rect, color);
        }
    }
    // Draw the characters
    painter.setBrush(Qt::yellow); // Pacman color
    painter.drawEllipse(game->pacman->get_position_x() * TILE_SIZE, game->pacman->get_position_y() * TILE_SIZE, TILE_SIZE, TILE_SIZE);
    painter.setBrush(Qt::white); // Ghost color
    for (int i = 0; i < game->num_ghosts; ++i) {
        painter.drawEllipse(game->ghosts[i]->get_position_x() * TILE_SIZE, game->ghosts[i]->get_position_y() * TILE_SIZE, TILE_SIZE, TILE_SIZE);
    }
}
