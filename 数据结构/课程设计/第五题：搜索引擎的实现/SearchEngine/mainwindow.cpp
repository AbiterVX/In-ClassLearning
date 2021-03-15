#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFileDialog>
#include<QStringList>
#include"invertedfileindex.h"

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    GetResult=new Result();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString Data;
    Data=ui->textEdit->toPlainText();
    if(Data!="")
    {
        QStringList WordList=Data.split(' ',QString::SkipEmptyParts);
        qSort(WordList.begin(),WordList.end());
        int WordCount=WordList.length();
        int RealCount=0;
        QString CurrentWord="";
        QQueue<QString> WordS;
        for(int i=0;i<WordCount;i++)
        {
            if(CurrentWord!=WordList.front())
            {
                CurrentWord=WordList.front();
                RealCount++;
                WordS.push_back(CurrentWord);
                WordList.pop_front();
            }
        }



        QQueue<int> URLS;
        QFile Dictionary("Dictionary.txt");
        Dictionary.open(QIODevice::ReadOnly);
        char *WordName=new char[1024];
        int length=0;        
        int position=0;
        char null;

        bool lasthave=0;
        while(!Dictionary.atEnd())
        {
            length=Dictionary.readLine((char*)WordName,1024);

            WordName[length-2]='\0';
            CurrentWord=QString(QLatin1String(WordName));
            Dictionary.read((char*)&null,sizeof(char)*1);

            if(CurrentWord==WordS.front())
            {
                while(1)
                {
                    Dictionary.read((char*)&position,sizeof(int)*1);
                    if(position!=-1)
                    {
                        URLS.push_back(position);
                    }
                    else
                    {
                        break;
                    }
                }
                lasthave=1;
            }
            else
            {
                if(lasthave==1)
                {
                    WordS.pop_front();
                    if(WordS.empty())
                    {
                        break;
                    }
                    lasthave=0;
                }

                while(1)
                {
                    Dictionary.read((char*)&position,sizeof(int)*1);
                    if(position==-1)
                    {
                        break;
                    }
                }
            }
        }

        length=URLS.length();
        int *DemandURLS=new int[length];
        for(int i=0;i<length;i++)
        {
            DemandURLS[i]=URLS.front();
            URLS.pop_front();
        }

        SortWays sortways;
        sortways.QuickSort(DemandURLS,0,length-1);

        int RealURLCount=0;
        int CurrentURL=-1;
        for(int i=0;i<length;i++)
        {
            if(CurrentURL!=DemandURLS[i])
            {
                DemandURLS[RealURLCount]=DemandURLS[i];
                CurrentURL=DemandURLS[i];
                RealURLCount++;
            }
        }


        GetResult->GetData(DemandURLS,RealURLCount);
        GetResult->show();
    }
}


void MainWindow::on_action_triggered()
{
    QString Path=QFileDialog::getOpenFileName(this,tr("Open File..."),".",
                                   tr("Files(*.doc *.txt *.docx )"));
    if(Path!="")
    {
        InvertedIndex Build(Path);
        Build.GetIndex();
    }
}








