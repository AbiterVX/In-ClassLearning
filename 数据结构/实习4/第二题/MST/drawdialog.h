#ifndef DRAWDIALOG_H
#define DRAWDIALOG_H

#include <QMainWindow>
#include<QPainter>
#include"mstgraph.h"
namespace Ui {
class DrawDialog;
}

class DrawDialog : public QMainWindow
{
    Q_OBJECT

public:
    explicit DrawDialog(QWidget *parent = 0);
    ~DrawDialog();

    void paintEvent(QPaintEvent *event);
    void DrawCircle(int x,int y,int height,int width);
    void DrawLine(int x1,int y1,int x2,int y2);
    void DrawText(int x1,int y1,int x2,int y2,QString text);
    void DrawEmptyCircle(int x,int y,int height,int width);
    Graph* DrawGraph;


private:
    Ui::DrawDialog *ui;

public slots:
    void ConnectDrawGRaph(Graph* GraphDraw);
};

#endif // DRAWDIALOG_H
