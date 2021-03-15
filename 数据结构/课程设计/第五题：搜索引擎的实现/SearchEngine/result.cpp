#include "result.h"
#include "ui_result.h"
#include<QDebug>
//#include"list.h"
Result::Result(QWidget *parent) :QMainWindow(parent),ui(new Ui::Result)
{
    ui->setupUi(this);
}

void Result::findURL()
{    
    QFile URLS("URLIndex.txt");
    URLS.open(QIODevice::ReadOnly);    
    char *CurrentURL=new char[1024];
    int length=0;
    int Current=0;

    EachURL *ResultURL=new EachURL[Count];   
    char null;   
    int name=0;

    while(!URLS.atEnd())
    {
        if(Current==Count)
        {
            break;
        }
        URLS.read((char*)&name,sizeof(int)*1);
        if(Data[Current]==name)
        {
            length=URLS.readLine(CurrentURL,1024);
            CurrentURL[length-2]='\0';
            ResultURL[Current].URL=QString(QLatin1String(CurrentURL));
            URLS.read((char*)&null,sizeof(char)*1);

            length=URLS.readLine(CurrentURL,1024);
            CurrentURL[length-2]='\0';
            ResultURL[Current].Date=QString(QLatin1String(CurrentURL));
            URLS.read((char*)&null,sizeof(char)*1);
            Current++;
        }
        else
        {
            URLS.readLine(CurrentURL,1024);
            URLS.read((char*)&null,sizeof(char)*1);
            URLS.readLine(CurrentURL,1024);
            URLS.read((char*)&null,sizeof(char)*1);
        }

    }


    int *Ranking=new int[Count];
    int Name=0;
    int Rank=0;
    Current=0;
    QFile *PageRank=new QFile("PageRank.txt");
    PageRank->open(QIODevice::WriteOnly);
    bool Ifopen=0;
    while(!PageRank->atEnd())
    {
        Ifopen=1;
        PageRank->read((char*)&Name,sizeof(int)*1);
        PageRank->read((char*)&Rank,sizeof(int)*1);
        if(Name==Data[Current])
        {
            Ranking[Current]=Rank;
            if(Current==Count-1)
            {
                break;
            }
        }
    }
    if(Ifopen==1)
    {
        QuickSort(ResultURL,Data,0,Count-1);
    }

    ui->listWidget->clear();
    for(int i=0;i<Count;i++)
    {
        ResultURL[i].URL=ResultURL[i].URL.right(ResultURL[i].URL.length()-2);
        ui->listWidget->addItem(ResultURL[i].URL);
        ResultURL[i].Date=ResultURL[i].Date.right(ResultURL[i].Date.length()-2);
        ui->listWidget->addItem(ResultURL[i].Date);
    }
    ui->listWidget->hide();
    ui->listWidget->show();

}
void Result::QuickSort(EachURL * &ResultURL,int * &Data,const int low,const int high)
{
    if(low>=high)
    {
        return;
    }
    int first=low;
    int last=high;
    int key=Data[first];
    EachURL NewURL=ResultURL[first];
    while(first<last)
    {
        while(first<last && Data[last] >=key)
        {
            last--;
        }
        Data[first]=Data[last];
        ResultURL[first]=ResultURL[last];
        while(first<last &&Data[first]<=key)
        {
            first++;
        }
        Data[last]=Data[first];
        ResultURL[last]=ResultURL[first];
    }
    Data[first]=key;
    ResultURL[first]=NewURL;
    QuickSort(ResultURL,Data,low,first-1);
    QuickSort(ResultURL,Data,first+1,high);
}

Result::~Result()
{   
    delete ui;
}
