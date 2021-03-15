#include "map.h"
#include "ui_map.h"




Map::~Map()
{
    delete ui;
}


Map::Map(QWidget *parent) :QMainWindow(parent),ui(new Ui::Map)
{
    ui->setupUi(this);
    MapScene=new QGraphicsScene();
    QPixmap pixmap;
    pixmap.load("Map-2.bmp");
    ui->graphicsView->setScene(MapScene);
    MapScene->addPixmap(pixmap);
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    /*******************************************/
    CUGMap=new Graph(42);
    LoadInData();

    CUGMap->GetRealVerTex();

    ui->dockWidgetContents_3->resize(QSize(ui->groupBox->size()));


}

void Map::paintEvent(QPaintEvent *event)
{

}

void Map::on_pushButton_clicked()
{
    ui->textEdit->clear();
    QGraphicsLineItem *currentPath;
    while(!PathStack.empty())
    {
        currentPath=PathStack.pop();
        MapScene->removeItem(currentPath);
    }
    ui->graphicsView->viewport()->update();


    QString StartName=ui->comboBox->currentText();
    QString DestinationName=ui->comboBox_2->currentText();

    if(StartName !=DestinationName)
    {
        CUGMap->ShortestPath(StartName,DestinationName);


        int PathNumber = CUGMap->PathNumber;
        Node*PATHS = new Node[PathNumber];
        double *PathLength = new double[PathNumber];
        PATHS = CUGMap->Path;
        PathLength = CUGMap->PathLength;


        QPen LinePathPen(Qt::blue,6,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
        PathLine=new QGraphicsLineItem*[PathNumber];

        QString EachData;
        for (int i = 0; i < PathNumber-1; i++)
        {
            //cout << "名称：" << PATHS[i].Name << "  信息：" << PATHS[i].Data << "  X坐标：" <<
             //   PATHS[i].PositionX << "  Y坐标：" << PATHS[i].PositionY << endl;
            //cout << PathLength[i] << endl;
            PathLine[i]=new QGraphicsLineItem(PATHS[i].PositionX,PATHS[i].PositionY,PATHS[i+1].PositionX,PATHS[i+1].PositionY);
            PathLine[i]->setPen(LinePathPen);
            MapScene->addItem(PathLine[i]);
            PathStack.push(PathLine[i]);

            if(i>0)
            {
                if(PATHS[i].Name[0] !='#')
                {
                    EachData="To:"+PATHS[i].Name;
                }
                else
                {
                    EachData="To:"+PATHS[i].Data;
                }
                EachData=EachData+"  Distance:"+QString::number(PathLength[i]) +"m";
                ui->textEdit->append(EachData);
                if(i==PathNumber-2)
                {
                    if(PATHS[i+1].Name[0] !='#')
                    {
                        EachData="To:"+PATHS[i+1].Name;
                    }
                    else
                    {
                        EachData="To:"+PATHS[i+1].Data;
                    }
                    EachData=EachData+"  Distance:"+QString::number(PathLength[i+1]) +"m";
                    ui->textEdit->append(EachData);
                }
            }
            else if(i==0)
            {
                EachData="Start:"+PATHS[i].Name;
                ui->textEdit->append(EachData);
            }

        }


    }


}

void Map::on_checkBox_clicked()
{
    QPen LinePen(Qt::yellow,6,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
    if(ui->checkBox->checkState()==Qt::Checked)
    {
        int current=0;
        for(int i=0;i<42*2 -2;i++,i++)
        {
            line[current]=new QGraphicsLineItem(Points[i].x(),Points[i].y(),Points[i+1].x(),Points[i+1].y());
            line[current]->setPen(LinePen);
            MapScene->addItem(line[current]);
            StartStack.push(line[current]);
            current++;
        }
    }
    else if(ui->checkBox->checkState()==Qt::Unchecked)
    {
        QGraphicsLineItem *current;
        while(!StartStack.empty())
        {
            current=StartStack.pop();
            MapScene->removeItem(current);
        }
    }
    ui->graphicsView->viewport()->update();
}

void Map::on_checkBox_2_clicked()
{

    if(ui->checkBox_2->checkState()==Qt::Checked)
    {
        QPen CirclePen(Qt::black,1,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
        int RealVertexNumber=CUGMap->RealVertexNumber;
        Node *realVertex = CUGMap->RealVertex;
        Circels=new Circle*[RealVertexNumber];
        int current=0;
        for (int i = 0; i < RealVertexNumber; i++)
        {
            Circels[current]=new Circle(realVertex[i].PositionX-10,realVertex[i].PositionY-10,20,20);
            Circels[current]->SetInformation(realVertex[i].Name,realVertex[i].Data);
            Circels[current]->setPen(CirclePen);
            Circels[current]->setBrush(Qt::red);
            MapScene->addItem(Circels[current]);
            CircleStack.push(Circels[current]);
            current++;
        }
    }
    else if(ui->checkBox_2->checkState()==Qt::Unchecked)
    {
        Circle *current;
        while(!CircleStack.empty())
        {
            current=CircleStack.pop();
            MapScene->removeItem(current);
        }

    }
    ui->graphicsView->viewport()->update();
}





void Map::LoadInData()
{
    QFile VertexFile("MapData.txt");
    QString Name;
    QString Data;
    int X;
    int Y;
    if(VertexFile.open(QFile::ReadOnly))
    {
        QTextStream vertexData(&VertexFile);
        while(!vertexData.atEnd())
        {
            vertexData>>Name>>X>>Y>>Data;
            CUGMap->InsertVertex(Name,X,Y,Data);
            //qDebug()<<Name<<X<<Y<<Data;
        }
    }
    VertexFile.close();



    Points=new QPoint[42*2];
    line=new QGraphicsLineItem*[42];


    //MapScene->addItem(line);
    QFile PathFile("PathLength.txt");
    QString Name1;
    QString Name2;
    double Length;

    int current=0;
    if(PathFile.open(QFile::ReadOnly))
    {
        QTextStream PathData(&PathFile);
        while(!PathData.atEnd())
        {
            PathData>>Name1>>Name2>>Length;
            CUGMap->InsertEdge(Name1,Name2,Length);
            Points[current]=CUGMap->GetVertex(Name1);
            current++;
            Points[current]=CUGMap->GetVertex(Name2);
            current++;
        }
    }
    PathFile.close();



}




