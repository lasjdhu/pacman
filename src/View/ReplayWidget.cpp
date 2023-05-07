/**
 * Painting and updating Game events from Replay as VIEW
 * @file ReplayWidget.cpp
 * @authors Jakub Kratochvil (xkrato67), Dmitrii Ivanushkin (xivanu00)
 */

#include "Widget.h"

const int TILE_SIZE = 50;

ReplayWidget::ReplayWidget(int rows, int cols, QString &map, QString &linesJoined, QWidget* parent) :
    QWidget(parent),
    rows(rows),
    cols(cols),
    map(map),
    linesJoined(linesJoined)
{
    setFixedSize(cols * TILE_SIZE, rows * TILE_SIZE);
}

void ReplayWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            QRect rect(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
            QPixmap pixmap;

            QChar tile = map.at(y * cols + x);

            if (tile != '.') {
                pixmap = QPixmap("../src/images/grass.jpg");
                painter.drawPixmap(rect, pixmap);
            }

            switch (tile.toLatin1()) {
            case 'X':
                pixmap = QPixmap("../src/images/wall.jpg");
                painter.drawPixmap(rect, pixmap);
                break;
            case 'T':
                pixmap = QPixmap("../src/images/flag.png");
                painter.drawPixmap(rect, pixmap);
                break;
            case 'K':
                pixmap = QPixmap("../src/images/key.png");
                painter.drawPixmap(rect, pixmap);
                break;
            default:
                break;
            }
        }
    }
}

void ReplayWidget::setIndex(int i) {
    QPainter painter(this);

    QStringList lines = linesJoined.split('\n');
    int p_x = lines[i].split(',')[1].toInt();
    int p_y = lines[i].split(',')[2].toInt();
    int g = lines[i].split(',')[3].toInt();
    int g_x = lines[i].split(',')[4].toInt();
    int g_y = lines[i].split(',')[5].toInt();

    QPixmap pacmanPixmap("../src/images/pacman.png");
    QPixmap ghostPixmapBlue("../src/images/ghostBlue.png");
    QPixmap ghostPixmapRed("../src/images/ghostRed.png");
    painter.drawPixmap(p_x * TILE_SIZE, p_y * TILE_SIZE,
                       TILE_SIZE, TILE_SIZE, pacmanPixmap);
    for (int i = 0; i < g; ++i) {
        if (i % 2 == 0) {
            painter.drawPixmap(g_x * TILE_SIZE, g_y * TILE_SIZE,
                               TILE_SIZE, TILE_SIZE, ghostPixmapBlue);
        } else {
            painter.drawPixmap(g_x * TILE_SIZE, g_y * TILE_SIZE,
                               TILE_SIZE, TILE_SIZE, ghostPixmapRed);
        }
    }

    update();
}