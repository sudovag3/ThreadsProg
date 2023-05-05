#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "readfile.h"
#include <QFileDialog>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void load_folder();
    void finished_thr();
    void buttonOK();

private:
    Ui::MainWindow *ui;
    QString dir;
    ReadFile* rf;
};

#endif // MAINWINDOW_H
