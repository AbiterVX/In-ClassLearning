#ifndef GRAPHITEM_H
#define GRAPHITEM_H

#endif // GRAPHITEM_H

#include<QPixmap>
#include<QGraphicsSceneMouseEvent>
#include<QGraphicsPixmapItem>
#include<QGraphicsItem>
#include<QDebug>
class PuzzleItem :public QGraphicsPixmapItem
{
private:
    QPixmap Graph;
public:
    PuzzleItem(QGraphicsItem *parent=Q_NULLPTR) :QGraphicsPixmapItem(parent)
    {
    }
    PuzzleItem(QPixmap graph,int width,int heigth,int name=0,QGraphicsItem *parent=Q_NULLPTR)
        :QGraphicsPixmapItem(parent)
    {               
        Graph=graph;
        setPixmap(Graph.scaled(width,heigth));
        Name=name;
        Width=width;
        Height=heigth;
        //setFlag(QGraphicsItem::ItemIsMovable);
        //setAcceptHoverEvents(true);
    }  
    void Build(QPixmap graph,int width,int heigth,int name=0)
    {
        Graph=graph;
        setPixmap(Graph.scaled(width,heigth));
        Name=name;
        Width=width;
        Height=heigth;
    }
    int Name;
    int Width;
    int Height;
};


/*
int X;
int Y;
IfClicked=0;
X=0;
Y=0;
void mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    setOffset(event->pos().x()-X ,event->pos().y()-Y );
    setCursor(Qt::OpenHandCursor);
}
void mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    X=event->pos().x()-offset().toPoint().x();
    Y=event->pos().y()-offset().toPoint().y();
}
bool IfClicked;*/






