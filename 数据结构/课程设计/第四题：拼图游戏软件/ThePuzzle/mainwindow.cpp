#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFileDialog>
#include<QMessageBox>

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainScene=new QGraphicsScene();
    ReferenceScene =new QGraphicsScene();
    ui->graphicsView->setScene(MainScene);
    ui->graphicsView_2->setScene(ReferenceScene);

    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_triggered()//导入图片
{
    MainScene->clear();
    ReferenceScene->clear();
    QString Path=QFileDialog::getOpenFileName(this,tr("Open File..."),".",
                                   tr("Picture Files(*.png *.bnp *.jpg )"));
    QPixmap MainPixMap;
    MainPixMap.load(Path);
    PuzzleItem *ReferenceItem=new PuzzleItem(MainPixMap,ui->graphicsView_2->width(),ui->graphicsView_2->height());
    ReferenceScene->addItem(ReferenceItem);

    Width=ui->graphicsView->width();
    Height=ui->graphicsView->height();
    int Type=ui->comboBox->currentIndex();
    if(Type==0)
    {
        Row=3;
        Column=3;
        SplitPixMap(MainPixMap.scaled(Width,Height));
    }
    else if(Type==1)
    {
        Row=4;
        Column=4;
        SplitPixMap(MainPixMap.scaled(Width,Height));
    }
}
void MainWindow::SplitPixMap(QPixmap pixmap)//切割图片
{    
    ItemS=new PuzzleItem**[Row];
    int Count=0;
    for(int i=0;i<Row;i++)
    {
        ItemS[i]=new PuzzleItem*[Column];
        for(int j=0;j<Column;j++)
        {
            QPixmap Part;
            Part=pixmap.copy(i*Width/Row,j*Height/Column,Width/Row,Height/Column);
            ItemS[i][j]=new PuzzleItem(Part,Width/Row,Height/Column,Count);
            Count++;
        }
    }
    Disorganize();
}

void MainWindow::Disorganize()//打乱
{
   //int InverseNumber=0;
   int *Queue=new int[Row*Column];
   for(int i=0;i<Row*Column;i++)
   {
       Queue[i]=i;
   }
   int **Matrix=GetPuzzle(Queue);
   int Exchange=0;
   int ExchangeTimes=Row*Column*10;
   int CurrentRow=Row-1;
   int CurrentColumn=Column-1;
   int From=0;
   qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
   int CurrentDerection=qrand()%(4);
   while(ExchangeTimes>0)
   {
       Exchange=Matrix[CurrentRow][CurrentColumn];
       if(CurrentRow+1<=Row-1 &&CurrentDerection==0&&From!=1)//下移
       {
           Matrix[CurrentRow][CurrentColumn]=Matrix[CurrentRow+1][CurrentColumn];
           Matrix[CurrentRow+1][CurrentColumn]=Exchange;
           CurrentRow+=1;
           From=2;//下
           ExchangeTimes--;
       }
       else if(CurrentRow-1>=0 &&CurrentDerection==1&&From!=2)//上移
       {
           Matrix[CurrentRow][CurrentColumn]=Matrix[CurrentRow-1][CurrentColumn];
           Matrix[CurrentRow-1][CurrentColumn]=Exchange;
           CurrentRow-=1;
           From=1;//上
           ExchangeTimes--;
       }
       else if(CurrentColumn+1<=Column-1&&CurrentDerection==2&&From!=3)//右移
       {
           Matrix[CurrentRow][CurrentColumn]=Matrix[CurrentRow][CurrentColumn+1];
           Matrix[CurrentRow][CurrentColumn+1]=Exchange;
           CurrentColumn+=1;
           From=4;
           ExchangeTimes--;
       }
       else if(CurrentColumn-1>=0&&CurrentDerection==3&&From!=4)//左移
       {
           Matrix[CurrentRow][CurrentColumn]=Matrix[CurrentRow][CurrentColumn-1];
           Matrix[CurrentRow][CurrentColumn-1]=Exchange;
           CurrentColumn-=1;
           From=3;
           ExchangeTimes--;
       }
       CurrentDerection=qrand()%(4);
   }

 /*
   if(Row*Column==9)
   {
       do
       {
           InverseNumber=0;
           Queue=RandomSequence(9);
           for(int i=0;i<8;i++)
           {
               for(int j=i+1;j<8;j++)
               {
                   if(Queue[i]>Queue[j])
                   {
                       InverseNumber++;
                   }
               }
           }
       }while(InverseNumber%2!=0);
   }
   else if(Row*Column==16)
   {
       int iii[16]={15,0,1,2,4,5,6,3,8,9,10,7,12,13,14,11};
       int jjj[16]={0,1,2,3,4,5,6,7,8,9,10,11,15,12,13,14};
       for(int i=0;i<16;i++)
       {
           Queue[i]=iii[i];
       }
       //Queue[15]=14;
       //Queue[14]=15;
       Queue=RandomSequence(16);
   }

   Begin=Queue;
   int **Matrix=GetPuzzle(Queue);
   */
   ui->graphicsView->setMatrix(Matrix,Row,Column,ItemS[Row-1][Column-1],MainScene);
   for(int i=0;i<Row;i++)
   {
       for(int j=0;j<Column;j++)
       {
           if(Matrix[i][j]==Row*Column-1)
           {
               BeginX=i;
               BeginY=j;
           }
           MainScene->addItem(ItemS[i][j]);
           if(Row==3&&j==Column-1)
           {
               ItemS[Matrix[i][j]/Row][Matrix[i][j]%Column]->setOffset(i*Width/Row,j*Height/Column-1);
           }
           else
           {
               ItemS[Matrix[i][j]/Row][Matrix[i][j]%Column]->setOffset(i*Width/Row,j*Height/Column);
           }
       }
   }
   MainScene->removeItem(ItemS[Row-1][Column-1]);

   int Count=0;
   Begin=new int[Row*Column];
   for(int i=0;i<Row;i++)
   {
       for(int j=0;j<Column;j++)
       {
           Begin[Count]=Matrix[i][j];
           Count++;
       }
   }
   /*for(int i=0;i<Row;i++)
   {
       for(int j=0;j<Column;j++)
       {
           MainScene->addItem(ItemS[i][j]);
           if(Row==3&&j==Column-1)
           {
               ItemS[Queue[Count]/Row][Queue[Count]%Column]->setOffset(i*Width/Row,j*Height/Column-1);
           }
           else
           {
               ItemS[Queue[Count]/Row][Queue[Count]%Column]->setOffset(i*Width/Row,j*Height/Column);
           }
           Count++;
       }
   }
   MainScene->removeItem(ItemS[Row-1][Column-1]);*/
}

void MainWindow::Move(int **puzzzle)
{
    for(int i=0;i<Row;i++)
    {
        for(int j=0;j<Column;j++)
        {
            MainScene->addItem(ItemS[i][j]);
            if(Row==3&&j==Column-1)
            {
                ItemS[puzzzle[i][j]/Row][puzzzle[i][j]%Column]->setOffset(i*Width/Row,j*Height/Column-1);
            }
            else
            {
                ItemS[puzzzle[i][j]/Row][puzzzle[i][j]%Column]->setOffset(i*Width/Row,j*Height/Column);
            }
        }
    }
    MainScene->removeItem(ItemS[Row-1][Column-1]);

}
int** MainWindow::GetPuzzle(int *Queue)
{
    int **Matrix=new int*[Row];
    int count=0;
    for(int i=0;i<Row;i++)
    {
        Matrix[i]=new int[Column];
        for(int j=0;j<Column;j++)
        {
            Matrix[i][j]=Queue[count];
            count++;
        }
    }
    return Matrix;
}

int* MainWindow::RandomSequence(int N)//生成随机数列
{
    int *Number = new int[N];
    bool Result;
    int CurrentNumber;
    for(int i=0;i<N-1;i++)
    {
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        do
        {
            Result=1;
            CurrentNumber=qrand()%(N-1);
            for(int j=0;j<i;j++)
            {
                if(CurrentNumber==Number[j])
                {
                    Result=0;
                    break;
                }
            }
        }while(Result==0);
        Number[i]=CurrentNumber;
    }
    Number[N-1]=N-1;
    /*for(int i=0;i<N;i++)
    {
        qDebug()<<Number[i];
    }*/
    return Number;
}

void MainWindow::sleep(unsigned int msec)
{
    QTime reachTime=QTime::currentTime().addMSecs(msec);

    while(QTime::currentTime()<reachTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
    }
}

void MainWindow::on_pushButton_clicked()
{    
    if(MainScene->items().count()!=0)
    {
        AStar astar(Row,Column,GetPuzzle(Begin),BeginX,BeginY);
        Step* Last=astar.BFS();
        QStack<Step*> StepS;
        Step*Current=Last;
        while(Current->Parent!=NULL)
        {
            StepS.push(Current);
            Current=Current->Parent;
        }


        while(!StepS.empty())
        {
            Current=StepS.pop();
            Move(Current->Puzzle);
            sleep(300);
        }

        MainScene->addItem(ItemS[Row-1][Column-1]);

        ItemS[Row-1][Column-1]->setOffset((Row-1)*Width/Row,(Column-1)*Height/Column-1);
        ui->graphicsView->viewport()->update();
        QMessageBox message(QMessageBox::NoIcon,"Result","Win!");
        QPixmap pixmap;
        pixmap.load("3.jpg");
        message.setIconPixmap(pixmap.scaled(400,200));
        message.exec();
    }


}















