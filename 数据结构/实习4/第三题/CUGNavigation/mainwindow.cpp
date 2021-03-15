#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPixmap>

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    CUGMap=new Map();

    QPixmap pixmap;
    pixmap.load("1.jpg");
    ui->label->setPixmap(pixmap);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    CUGMap->show();
    close();
}
