#include "drawdialog.h"
#include "ui_drawdialog.h"

DrawDialog::DrawDialog(QWidget *parent) :QMainWindow(parent),ui(new Ui::DrawDialog)
{
    ui->setupUi(this);
}

DrawDialog::~DrawDialog()
{
    delete ui;
}

void DrawDialog::paintEvent(QPaintEvent *event)
{
    int VertexNumber=0;                             //顶点个数
    VertexNumber=DrawGraph->GetVertexNumber();
    Node* Result = new Node[VertexNumber];
    char *VertexS=new char[VertexNumber+1];
    VertexS=DrawGraph->GeTVertexS();
    Result = DrawGraph->Kruskal();

    int CurrentHeight=this->height();
    int CurrentWidth=this->width();
    int CurrentRadius=0;
    int CurrentMin=CurrentHeight;
    if(CurrentHeight>CurrentWidth)
    {
        CurrentMin=CurrentWidth;
    }
    CurrentRadius=CurrentMin*3/8;

    double *PointX=new double[VertexNumber];        //x坐标
    double *PointY=new double[VertexNumber];        //y坐标

    double VertexRadius=(CurrentMin-CurrentRadius*2)/4;  //顶点的半径
    DrawEmptyCircle(CurrentWidth/2-CurrentRadius,CurrentHeight/2-CurrentRadius,CurrentRadius*2,CurrentRadius*2);


    double PartDegree=360/VertexNumber;             //一份的度数
    QString Text;
    for(int i=0;i<VertexNumber;i++)
    {
        PointX[i]=CurrentWidth/2-CurrentRadius*cos(i*PartDegree*acos(-1.0) / 180);
        PointY[i]=CurrentHeight/2+CurrentRadius*sin(i*PartDegree*acos(-1.0) / 180);
        DrawCircle(PointX[i]-VertexRadius-VertexRadius*cos(i*PartDegree*acos(-1.0) / 180),
                   PointY[i]-VertexRadius+VertexRadius*sin(i*PartDegree*acos(-1.0) / 180),
                   VertexRadius*2,VertexRadius*2);

        Text=VertexS[i];
        DrawText(PointX[i]-VertexRadius-VertexRadius*cos(i*PartDegree*acos(-1.0) / 180),
                 PointY[i]-VertexRadius+VertexRadius*sin(i*PartDegree*acos(-1.0) / 180),
                 VertexRadius*2,VertexRadius*2,Text);
    }

    for(int i=0;i<VertexNumber-1;i++)
    {
        DrawLine(PointX[Result[i].FirstAddress],PointY[Result[i].FirstAddress],
                PointX[Result[i].SecondAddress],PointY[Result[i].SecondAddress]);
    }
    /*for (int i = 0; i < 6; i++)
      {
         cout << Result[i].FirstAddress << " " << Result[i].SecondAddress << " " << Result[i].Weight << endl;
      }
    */
}

void DrawDialog::DrawCircle(int x,int y,int height,int width)
{
    QPainter painter(this);
    QPen pen(Qt::black,1,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);//画刷，线宽，画笔风格，
    painter.setPen(pen);                                           //画笔端点风格，画笔连接风格

    painter.setBrush(Qt::blue);
    painter.drawEllipse(x,y,height,width);
    painter.end();
}

void DrawDialog::DrawEmptyCircle(int x,int y,int height,int width)
{
    QPainter painter(this);
    QPen pen(Qt::black,1,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);//画刷，线宽，画笔风格，
    painter.setPen(pen);                                           //画笔端点风格，画笔连接风格
    painter.drawEllipse(x,y,height,width);
    painter.end();
}

void DrawDialog::DrawLine(int x1,int y1,int x2,int y2)
{
    QPainter painter(this);
    QPen pen(Qt::black,5,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
    painter.setPen(pen);

    painter.drawLine(QPoint(x1,y1),QPoint(x2,y2));
    painter.end();
}
void DrawDialog::DrawText(int x1,int y1,int x2,int y2,QString text)
{
    QPainter painter(this);
    QPen pen(Qt::white,1,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
    painter.setPen(pen);

    QRectF rect(x1,y1,x2,y2);
    //painter.drawRect(rect);
    QFont font("宋体",x2/2,QFont::Bold,false); //字体，点大小，粗体，是否斜体

    painter.setFont(font);
    painter.drawText(rect,Qt::AlignHCenter,text); //矩形，对齐方式，文字
    painter.end();
}




void DrawDialog::ConnectDrawGRaph(Graph* GraphDraw)
{
     DrawGraph = GraphDraw;
}












