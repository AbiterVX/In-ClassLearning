#ifndef VIEW_H
#define VIEW_H

#include<QGraphicsView>
#include<QMouseEvent>

class View :public QGraphicsView
{
    Q_OBJECT
public:
    View(QWidget *parent=0);
protected:
    //void mouseMoveEvent(QMouseEvent *event);
    //void mouseReleaseEvent(QMouseEvent *event);
    //void mousePressEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
};

#endif // VIEW_H
