#include "drawdialoge1.h"
#include "ui_drawdialoge1.h"
#include<math.h>

DrawDialoge1::DrawDialoge1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DrawDialoge1)
{
    ui->setupUi(this);
}

DrawDialoge1::~DrawDialoge1()
{
    delete ui;
}

void DrawDialoge1::paintEvent(QPaintEvent *event)
{
    int depth= TreeDraw->Depth(TreeDraw->GetRoot()) ; //深度
    int UnitLength=this->width()/pow(2,depth+1);      //单位长度
    int UnitHeight=this->height()/(depth+2);          //单位高度
    int CurrentX=(pow(2,depth)-1)*UnitLength +UnitLength; //当前坐标X
    int CurrentY=UnitHeight/3;                            //当前坐标Y

    TreeNode<char>* CurrentNode;                          //当前的节点
    CurrentNode=TreeDraw->GetRoot();                      //指向根结点
    TreeNode<char> *EmptyNode=new TreeNode<char>;
    EmptyNode->Data='#';

    Queue<TreeNode<char>*> NodeQueue;                //节点队列
    Queue<point> PointQueue;                         //点队列

    //TreeNode<char> *EndNode=new TreeNode<char>;
    int CurrentLevelNode=0;
    int NextLevelNode=0;
    while (CurrentNode != NULL)
    {        
        DrawCircle(CurrentX,CurrentY,UnitLength,UnitLength);                         //画圆

        char CHAR=CurrentNode->Data;
        char*text=new char[2];
        text[0]=CHAR;
        text[1]='\0';
        QString Text=text;
        DrawText(CurrentX,CurrentY,UnitLength,UnitLength,Text);  //画出数字

        if(CurrentNode->Data !='#')
        {
            point CurrentPoint(CurrentX,CurrentY);
            if (CurrentNode->LeftChild != NULL)          //左child入队
            {               
                point ChildPoint(CurrentX-pow(2,depth-1)*UnitLength,CurrentY+UnitHeight);
                NodeQueue.Insert(CurrentNode->LeftChild);
                PointQueue.Insert(CurrentPoint);
                PointQueue.Insert(ChildPoint);
                NextLevelNode++;
            }
           else
            {              
                point ChildPoint(CurrentX-pow(2,depth-1)*UnitLength,CurrentY+UnitHeight);
                EmptyDrawLine(CurrentPoint.X+UnitLength/2,CurrentPoint.Y+UnitLength,
                      ChildPoint.X+UnitLength-UnitLength/2,ChildPoint.Y);
                EmptyDrawCircle(ChildPoint.X,ChildPoint.Y,UnitLength,UnitLength);
                QString Text="#";
                DrawText(ChildPoint.X,ChildPoint.Y,UnitLength,UnitLength,Text);
            }
            if (CurrentNode->RightChild != NULL)         //右child入队
            {               
                point ChildPoint(CurrentX+pow(2,depth-1)*UnitLength,CurrentY+UnitHeight);
                NodeQueue.Insert(CurrentNode->RightChild);
                PointQueue.Insert(CurrentPoint);
                PointQueue.Insert(ChildPoint);
                NextLevelNode++;

            }
            else
            {                
                point ChildPoint(CurrentX+pow(2,depth-1)*UnitLength,CurrentY+UnitHeight);
                EmptyDrawLine(CurrentPoint.X+UnitLength/2,CurrentPoint.Y+UnitLength,
                      ChildPoint.X+UnitLength-UnitLength/2,ChildPoint.Y);
                EmptyDrawCircle(ChildPoint.X,ChildPoint.Y,UnitLength,UnitLength);
                QString Text="#";
                DrawText(ChildPoint.X,ChildPoint.Y,UnitLength,UnitLength,Text);
            }           
        }
        if(CurrentLevelNode==0)
        {
            depth--;
            CurrentLevelNode=NextLevelNode;
            NextLevelNode=0;
        }


            if (!NodeQueue.IfEmpty())                //出队
            {
                point CurrentPoint=PointQueue.PointGetTopData();
                PointQueue.Remove();
                point NextPoint(PointQueue.PointGetTopData().X,PointQueue.PointGetTopData().Y);               
                CurrentX=PointQueue.PointGetTopData().X;
                CurrentY=PointQueue.PointGetTopData().Y;
                PointQueue.Remove();

                DrawLine(CurrentPoint.X+UnitLength/2,CurrentPoint.Y+UnitLength,
                            NextPoint.X+UnitLength-UnitLength/2,NextPoint.Y);
                CurrentNode = NodeQueue.GetTopData();
                NodeQueue.Remove();
                CurrentLevelNode--;
            }
            else
            {
                break;
            }
    }
}

void DrawDialoge1::DrawCircle(int x,int y,int height,int width)
{
    QPainter painter(this);
    QPen pen(Qt::black,1,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);//画刷，线宽，画笔风格，
    painter.setPen(pen);                                           //画笔端点风格，画笔连接风格

    painter.setBrush(Qt::blue);
    painter.drawEllipse(x,y,height,width);
    painter.end();
}

void DrawDialoge1::DrawLine(int x1,int y1,int x2,int y2)
{
    QPainter painter(this);
    QPen pen(Qt::black,2,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
    painter.setPen(pen);

    painter.drawLine(QPoint(x1,y1),QPoint(x2,y2));
    painter.end();
}
void DrawDialoge1::DrawText(int x1,int y1,int x2,int y2,QString text)
{
    QPainter painter(this);
    QPen pen(Qt::white,1,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
    painter.setPen(pen);

    QRectF rect(x1,y1,x2,y2);
   // painter.drawRect(rect);
    QFont font("宋体",x2/2,QFont::Bold,false); //字体，点大小，粗体，是否斜体

    painter.setFont(font);
    painter.drawText(rect,Qt::AlignHCenter,text); //矩形，对齐方式，文字
    painter.end();
}



void DrawDialoge1::EmptyDrawCircle(int x,int y,int height,int width)
{
    QPainter painter(this);
    QPen pen(Qt::black,3,Qt::DashLine,Qt::RoundCap,Qt::RoundJoin);//画刷，线宽，画笔风格，
    painter.setPen(pen);                                           //画笔端点风格，画笔连接风格

    painter.setBrush(QColor(200,0,255));
    painter.drawEllipse(x,y,height,width);


    painter.end();
}

void DrawDialoge1::EmptyDrawLine(int x1,int y1,int x2,int y2)
{
    QPainter painter(this);
    QPen pen(Qt::black,2,Qt::DashLine,Qt::RoundCap,Qt::RoundJoin);
    painter.setPen(pen);

    painter.drawLine(QPoint(x1,y1),QPoint(x2,y2));
    painter.end();
}






void DrawDialoge1::ConnectDrawTree(TheBinaryTree<char>* treedraw)
{
     TreeDraw = treedraw;
}

