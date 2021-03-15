#include "cover.h"
#include "ui_cover.h"

Cover::Cover(QWidget *parent) :QMainWindow(parent),ui(new Ui::Cover)
{
    ui->setupUi(this);
}

Cover::~Cover()
{
    delete ui;
}

void Cover::on_pushButton_clicked()
{
    mainwindow=new MainWindow();
    mainwindow->show();
    close();
}
