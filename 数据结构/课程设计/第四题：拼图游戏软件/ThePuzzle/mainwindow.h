#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QGraphicsScene>
#include"view.h"

#include<QtGlobal>
#include<QTime>
#include"astar.h"
#include<QStack>

#include<QApplication>
#include<QTime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void SplitPixMap(QPixmap pixmap);
    void Disorganize();
    int *RandomSequence(int N);
    void Move(int **puzzzle);
    int** GetPuzzle(int *Queue);

    void sleep(unsigned int msec);
    int *Begin;
private:
    Ui::MainWindow *ui;

    QGraphicsScene *MainScene;
    QGraphicsScene *ReferenceScene;
    PuzzleItem ***ItemS;
    int Width;
    int Height;
    int Row;
    int Column;
    int BeginX;
    int BeginY;
private slots:
    void on_action_triggered();
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H













