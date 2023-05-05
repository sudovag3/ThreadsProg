#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->ButtonOK, &QPushButton::clicked, this, &MainWindow::buttonOK);
    connect(ui->ButtonChooseFile, &QPushButton::clicked, this, &MainWindow::load_folder);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::load_folder()
{
    QFileDialog fd;
        dir = fd.getOpenFileName();
        if (dir=="") ui->labelFileName->setText("Choose file!");//если пустая директория
        else
        {
           //директория
           dir.replace(QString('/'), QString("\\"));
           ui->labelFileName->setText(dir);

           rf = new ReadFile(ui->progressBar);
           rf->set_dir(dir);
           if (dir.contains("samples"))ui->ButtonOK->setEnabled(true);
           else ui->ButtonOK->setEnabled(false);
        }
}

void MainWindow::finished_thr()
{
    if (rf->isFinished())
    {
        ui->ButtonOK->setEnabled(false);
        delete rf;
    }
}

void MainWindow::buttonOK()
{
    QObject::connect(rf,SIGNAL(progress_bar(int)),ui->progressBar, SLOT(setValue(int)));
    QObject::connect(rf,SIGNAL(finished()),this, SLOT(finished_thr()));
    rf->start();
}
