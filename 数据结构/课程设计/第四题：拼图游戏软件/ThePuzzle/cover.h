#ifndef COVER_H
#define COVER_H

#include <QMainWindow>
#include"mainwindow.h"

namespace Ui {
class Cover;
}

class Cover : public QMainWindow
{
    Q_OBJECT

public:
    explicit Cover(QWidget *parent = 0);
    ~Cover();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Cover *ui;

    MainWindow* mainwindow;
};

#endif // COVER_H
