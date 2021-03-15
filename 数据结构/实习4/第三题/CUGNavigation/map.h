#ifndef MAP_H
#define MAP_H

#include <QMainWindow>

#include<QGraphicsScene>

#include<circleclass.h>
#include<QGraphicsLineItem>



#include<QDebug>
#include"minpath.h"

#include<QFile>
#include<QTextStream>
#include"view.h"

#include<QStack>
#include<QPainter>

namespace Ui {
class Map;
}

class Map : public QMainWindow
{
    Q_OBJECT

public:
    explicit Map(QWidget *parent = 0);
    ~Map();

    void paintEvent(QPaintEvent *event);

protected:

private slots:
    void on_pushButton_clicked();
    void on_checkBox_clicked();

    void on_checkBox_2_clicked();

private:
    Ui::Map *ui;
    QGraphicsScene *MapScene;

    Graph *CUGMap;
    void LoadInData();


    Circle **Circels;
    QGraphicsLineItem **PathLine;
    QGraphicsLineItem **line;
    QStack<Circle*> CircleStack;
    QStack<QGraphicsLineItem*> PathStack;
    QStack<QGraphicsLineItem*> StartStack;

    QPoint *Points;



};

#endif // MAP_H
