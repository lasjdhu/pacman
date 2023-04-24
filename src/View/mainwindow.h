#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../Controller/Controller.h"
#include "GameWidget.h"
#include <QMainWindow>
#include <QtWidgets>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow* getUi();
    QStatusBar* getStatusBar();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
