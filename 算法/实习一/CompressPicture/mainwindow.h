#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"pressclass.h"
#include<thread.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

    /*void handleResults(int value);
    void startThread();*/

private:
    Ui::MainWindow *ui;
    PressPicture *FileCompress;
};

#endif // MAINWINDOW_H
