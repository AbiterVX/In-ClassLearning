#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"drawdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    DrawDialog* drawdialog;
    Graph *graph;
private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

signals:
    void GraphConnect(Graph* NewGrahp);

};

#endif // MAINWINDOW_H
