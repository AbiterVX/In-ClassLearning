#include "view.h"

View::View(QWidget *parent):QGraphicsView(parent)
{

}


void View::wheelEvent(QWheelEvent *event)
{
    QGraphicsView::wheelEvent(event);
    if(event->delta()>0)
    {
        scale(1.1,1.1);
    }
    else
    {
        scale(0.9,0.9);
    }
}
