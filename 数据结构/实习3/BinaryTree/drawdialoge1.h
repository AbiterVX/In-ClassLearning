#ifndef DRAWDIALOGE1_H
#define DRAWDIALOGE1_H

#include <QMainWindow>

#include<QPainter>
#include"mainbinarytree.h"
#include<QProcess>
namespace Ui {
class DrawDialoge1;
}

class DrawDialoge1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit DrawDialoge1(QWidget *parent = 0);
    ~DrawDialoge1();

    void paintEvent(QPaintEvent *event);
    void DrawLine();
    void DrawCircle();
    void DrawText();

    TheBinaryTree<char> *TreeDraw;


    void DrawCircle(int x,int y,int height,int width);
    void DrawLine(int x1,int y1,int x2,int y2);
    void DrawText(int x1,int y1,int x2,int y2,QString text);
    void EmptyDrawCircle(int x1,int y1,int x2,int y2);
    void EmptyDrawLine(int x1,int y1,int x2,int y2);



private:
    Ui::DrawDialoge1 *ui;

public slots:
    void ConnectDrawTree(TheBinaryTree<char>* treedraw);

};

#endif // DRAWDIALOGE1_H
