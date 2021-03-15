#ifndef VIEW_H
#define VIEW_H

#include<QGraphicsView>
#include<QMouseEvent>
#include<QGraphicsItem>
#include<QDebug>
#include"graphitem.h"
#include<QMessageBox>
#include<QGraphicsScene>

class View:public QGraphicsView
{
public:
    View(QWidget *parent=0);
    void setMatrix(int **matrix,int row,int column,PuzzleItem* item,QGraphicsScene *scene)
    {
        Matrix=matrix;
        Row=row;
        Column=column;
        LastItem=item;
        Scene=scene;
        /*for(int i=0;i<Row;i++)
        {
            for(int j=0;j<Column;j++)
            {
                qDebug()<<Matrix[i][j];
            }
            //qDebug()<<endl;
        }*/
    }
    bool IfTrue()
    {
        int Count=0;
        for(int i=0;i<Row;i++)
        {
            for(int j=0;j<Column;j++)
            {
                if(Matrix[i][j]!=Count)
                {
                    return false;
                }
                else
                {
                    Count++;
                }
            }
        }
        return true;
    }
    void Swap(int name,int type)
    {
        int row;
        int column;
        int exchange;
        for(int i=0;i<Row;i++)
        {
            for(int j=0;j<Column;j++)
            {
                if(Matrix[i][j]==name)
                {
                    row=i;
                    column=j;
                    break;
                }
            }
        }
        if(type==1)
        {
            exchange=Matrix[row-1][column];
            Matrix[row-1][column]=name;
            Matrix[row][column]=exchange;
        }
        else if(type==2)
        {
            exchange=Matrix[row+1][column];
            Matrix[row+1][column]=name;
            Matrix[row][column]=exchange;
        }
        else if(type==3)
        {
            exchange=Matrix[row][column-1];
            Matrix[row][column-1]=name;
            Matrix[row][column]=exchange;
        }
        else if(type==4)
        {
            exchange=Matrix[row][column+1];
            Matrix[row][column+1]=name;
            Matrix[row][column]=exchange;
        }

        /*for(int i=0;i<Row;i++)
        {
            for(int j=0;j<Column;j++)
            {
                qDebug()<<Matrix[i][j];
            }
            //qDebug()<<endl;
        }*/
    }

    int **Matrix;
    int Row;
    int Column;
    PuzzleItem* LastItem;
    QGraphicsScene *Scene;
protected:    
    void mousePressEvent(QMouseEvent *event);

};

#endif // VIEW_H
