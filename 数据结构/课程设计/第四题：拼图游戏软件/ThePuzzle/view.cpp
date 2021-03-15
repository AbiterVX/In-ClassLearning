#include "view.h"

View::View(QWidget *parent):QGraphicsView(parent)
{    
    Row=0;
    Column=0;
}


void View::mousePressEvent(QMouseEvent *event)
{
    int Bound;

    int ItemName;
    if(Row*Column==9)
    {
        Bound=2;
    }
    else if(Row*Column==16)
    {
        Bound=3;
    }

    QGraphicsItem *CurrentItem=itemAt(event->x(),event->y());
    if(CurrentItem!=NULL)
    {
        PuzzleItem *Current=(PuzzleItem *)CurrentItem;
        ItemName=Current->Name;
        int Width=Current->Width;
        int Height=Current->Height;
        int X=Current->offset().x();
        int Y=Current->offset().y();

        bool Move=0;
        if(X+Width<=Width*Bound && !Move)
        {
            Current->setOffset(X+Width,Y);
            if(!Current->collidingItems().empty())
            {
                Current->setOffset(X,Y);
            }
            else
            {
                Swap(ItemName,2);
                Move=1;
            }
        }
        if(0<=X-Width && !Move)
        {
            Current->setOffset(X-Width,Y);
            if(!Current->collidingItems().empty())
            {
                Current->setOffset(X,Y);
            }
            else
            {
                Swap(ItemName,1);
                Move=1;
            }
        }
        if(Y+Height<=Height*Bound && !Move)
        {
            Current->setOffset(X,Y+Height);
            if(!Current->collidingItems().empty())
            {
                Current->setOffset(X,Y);
            }
            else
            {
                Swap(ItemName,4);
                Move=1;
            }
        }
        if(0<=Y-Height && !Move)
        {
            Current->setOffset(X,Y-Height);
            if(!Current->collidingItems().empty())
            {
                Current->setOffset(X,Y);
            }
            else
            {
                Swap(ItemName,3);
                Move=1;
            }
        }

        if(IfTrue())
        {
            Scene->addItem(LastItem);
            LastItem->setOffset(Width*(Row-1),Height*(Column-1));
            QMessageBox message(QMessageBox::NoIcon,"Result","Win!");
            QPixmap pixmap;
            pixmap.load("3.jpg");
            message.setIconPixmap(pixmap.scaled(400,200));
            message.exec();
        }

    }
}













