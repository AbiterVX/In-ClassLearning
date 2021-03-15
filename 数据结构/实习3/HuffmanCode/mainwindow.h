#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<compress.h>

#include<tread.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    HufumanCompress *FileCompress;

private:
    Ui::MainWindow *ui;
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

    void handleResults(int value);
    void startThread();    
};

#endif // MAINWINDOW_H
