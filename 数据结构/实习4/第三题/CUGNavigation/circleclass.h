#ifndef CIRCLECLASS_H
#define CIRCLECLASS_H

#endif // CIRCLECLASS_H
#include<QGraphicsEllipseItem>
#include<QGraphicsSceneHoverEvent>
#include<QGraphicsSceneContextMenuEvent>
#include<QString>
#include<QMouseEvent>
#include<QCursor>

#include<QPixmap>
#include<QStatusBar>
#include<QLabel>
#include<QDebug>
#include<QWidget>

class Circle :public QGraphicsEllipseItem
{
public:
    Circle(qreal x,qreal y,qreal width,qreal height)
    {
        setAcceptHoverEvents(true);
        setRect(x,y,width,height);

        statusLabel=new QLabel();

    }

    void SetInformation(QString information,QString data=".")
    {
        QString photo;

        photo=information+".jpg";

        Information=information;
        pixmap.load(photo);
        pixmap=pixmap.scaled(pixmap.width(),pixmap.height());
        statusLabel->setPixmap(pixmap);


        QString Data;
        Data=information+":"+data;
        statusLabel->setWindowTitle(Data);

    }

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event)
    {
        QGraphicsEllipseItem::hoverEnterEvent(event);
        setCursor(Qt::OpenHandCursor);
        setToolTip(Information);
        statusLabel->setVisible(true);       
        statusLabel->setGeometry( cursor().pos().x()+20, cursor().pos().y()+20,pixmap.width(),pixmap.height());
    }
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
    {
        statusLabel->setVisible(false);
    }

private:
    QString Information;
    QPixmap pixmap;

    QLabel *statusLabel;
    QStatusBar *statusBar;



};
