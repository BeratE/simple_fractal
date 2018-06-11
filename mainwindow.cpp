#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->centralWidget, SIGNAL(updateLabelC(QString)), ui->lblC, SLOT(setText(QString)));
    connect(ui->centralWidget, SIGNAL(updateLabelZoom(QString)), ui->lblZoom, SLOT(setText(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
