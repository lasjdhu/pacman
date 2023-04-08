#include "Controller.h"

InterfaceController::InterfaceController(QStatusBar *statusBar, Ui::MainWindow *ui, QObject *parent) :
    statusBar(statusBar), ui(ui), QObject(parent)
{}

void InterfaceController::loadFile() {
    // Get filename
    QString filename = QFileDialog::getOpenFileName(qobject_cast<QWidget*>(parent()), "Open File", "../examples/", "Text Files (*.txt)");
    if (filename.isEmpty()) {
        statusBar->showMessage("No file loaded");
        return;
    }

    // Open file
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        statusBar->showMessage("Failed to load file");
        return;
    }

    // Read content, get strings and convert them to a byte array
    QTextStream in(&file);
    QString content = in.readAll();

    file.close();
    statusBar->showMessage(QString("File \"%1\" loaded").arg(filename));

    emit fileLoaded(content);
}

void InterfaceController::saveFile() {
    // Get filename
    QString filename = QFileDialog::getSaveFileName(qobject_cast<QWidget*>(parent()), "Save File", "../examples/", "Text Files (*.txt)");
    if (filename.isEmpty()) {
        statusBar->showMessage("No file saved");
        return;
    }

    // Open file
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        statusBar->showMessage("Failed to save file");
        return;
    }

    QString content = ui->textBrowser->toPlainText();
    QStringList rows = content.split("\n");

    while (!rows.isEmpty() && rows.last().isEmpty()) {
        rows.removeLast();
    }

    int numRows = rows.size();
    int numCols = numRows > 0 ? rows[0].size() : 0;

    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            QChar c = rows[i][j];
            if (c == '0') {
                rows[i][j] = '.';
            } else if (c == '1') {
                rows[i][j] = 'X';
            } else if (c == '2') {
                rows[i][j] = 'K';
            } else if (c == '3') {
                rows[i][j] = 'S';
            } else if (c == '4') {
                rows[i][j] = 'T';
            } else if (c == '5') {
                rows[i][j] = 'G';
            }
        }
    }

    QString sizes = QString("%1 %2").arg(numRows).arg(numCols);
    QString gameState = sizes + "\n" + rows.join("\n") + "\n";

    // Write gameState to a file
    QTextStream out(&file);
    out << gameState;

    file.close();
    statusBar->showMessage(QString("File \"%1\" saved").arg(filename));
}

void InterfaceController::displayHelp() {
    QString message = "Help is here";
    QMessageBox::information(qobject_cast<QWidget*>(parent()), "Help", message);
    statusBar->showMessage("Help is shown");
}
