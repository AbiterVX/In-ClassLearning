#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"result.h"


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
    void on_pushButton_clicked();

    void on_action_triggered();

private:
    Ui::MainWindow *ui;
    Result* GetResult;
};

#endif // MAINWINDOW_H
