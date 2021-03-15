#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<fstream>
#include<math.h>

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->textEdit->append("abcdefg");
    ui->textEdit_2->append("0 28 M M M 10 M \r"
                           "28 0 16 M M M 14 \r"
                           "M 16 0 12 M M M \r"
                           "M M 12 0 22 M 18 \r"
                           "M M M 22 0 25 24 \r"
                           "10 M M M 25 0 M \r"
                           "M 14 M 18 24 M 0 \r" );

    drawdialog=new DrawDialog();
    graph =new Graph();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString Data;
    int VertexNumber;
    Data=ui->textEdit->toPlainText();
    VertexNumber=Data.length();
    char *data;
    QByteArray transform;
    transform=Data.toLatin1();
    data=transform.data();

    QString Data1;
    Data1=ui->textEdit_2->toPlainText();
    char *data1;
    QByteArray transform1;
    int EachSection=0;
    QString EachEdge;
    int EdgeLength=0;
    double EdgeWeight=0;
    int PointPow=-1;


    double **EdgeData=new double*[VertexNumber];
    for(int i=0;i<VertexNumber;i++)
    {
        EdgeData[i]=new double[VertexNumber];
        for(int j=0;j<VertexNumber;j++)
        {
            EachEdge=Data1.section(' ',EachSection,EachSection);
            EachSection++;
            transform1=EachEdge.toLatin1();
            data1=transform1.data();

            if(data1[0]=='0' &&EachEdge.length()==1)
            {
                EdgeData[i][j]=0;
            }
            else if(data1[0]=='M')
            {
                EdgeData[i][j]=Max;
            }
            else if(data1[0]=='\r')
            {
                j--;
            }
            else
            {
                EdgeLength=EachEdge.length();
                for(int k=0;k<EdgeLength;k++)
                {
                    if(data1[k]!='.')
                    {
                        EdgeWeight*=10;
                        EdgeWeight+=(data1[k]-48);
                    }
                    else
                    {
                        EdgeWeight+=(data1[k]-48)*pow(10,PointPow);
                        PointPow-=1;
                    }
                }
                EdgeData[i][j]=EdgeWeight;
                EdgeWeight=0;
                PointPow=-1;
            }
        }
    }
    graph->BuildGraph(VertexNumber);
    for(int i=0;i<VertexNumber;i++)
    {
        graph->InsertVertex(data[i]);
    }
    graph->InsertAllEdge(EdgeData);

    connect(this,SIGNAL(GraphConnect(Graph*)),drawdialog, SLOT(ConnectDrawGRaph(Graph*)) );
    emit GraphConnect(graph);
    drawdialog->show();
}


















