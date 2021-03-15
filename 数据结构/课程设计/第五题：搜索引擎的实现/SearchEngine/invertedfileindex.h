#ifndef INVERTEDFILEINDEX_H
#define INVERTEDFILEINDEX_H
#endif // INVERTEDFILEINDEX_H
#include<QVector>
#include<QString>
#include<QFile>
#include"list.h"
#include"mergesort.h"

using namespace std;


struct URLNode
{
    QString URL;
    QString Date;
    int Count;
    URLNode()
    {
        URL="";
        Date="";
        Count=0;
    }
};

class InvertedIndex
{
public:
    InvertedIndex(QString path);
    void GetIndex();
    void GetPageRank();
    int GetHashValue(QString url);

private:
    QString Path;
    QFile *ReadFile;
    int URLCount;     //URL总数
    Queue *HashOfURL;
};

InvertedIndex::InvertedIndex(QString path)
{
    ReadFile=new QFile(path);
    ReadFile->open(QIODevice::ReadOnly);
    Path=path;
}
void InvertedIndex::GetIndex()//处理原文件，生成两个文件
{
    remove("URLIndex.txt");
    QFile URLFile("URLIndex.txt");
    URLFile.open(QIODevice::WriteOnly);
    SortNode* WriteBuffer=new SortNode[20000];
    HashOfURL=new Queue[10000];
    URLNode* URLBuffer=new URLNode[5000];
    int URLBufferCount=0;
    QString CurrentURL;

    char* Data=new char[3*1024];
    int length=0;
    URLCount=-1;
    int HashIndex=0;
    int CurrentBuffer=0;
    int Count=0;

    while(!ReadFile->atEnd())
    {
        length=ReadFile->readLine(Data,3072);
        if(length==-1)
        {
            break;
        }

        if(Data[0]=='P')        //URL
        {                       // count,url,date
            URLCount++;
            Data[length-2]='\0';
            CurrentURL=QString(QLatin1String(Data));
            HashIndex=GetHashValue(Data);
            URLBuffer[URLBufferCount].URL=CurrentURL;
        }
        else if(Data[0]=='T')   //时间
        {
            HashOfURL[HashIndex].Insert(URLCount,CurrentURL,Data);

            Data[length-2]='\0';
            URLBuffer[URLBufferCount].Date=QString(QLatin1String(Data));
            URLBuffer[URLBufferCount].Count=URLBufferCount;
            URLBufferCount++;
            if(URLBufferCount==5000)
            {
                for(int i=0;i<5000;i++)
                {
                    QByteArray *bytearray1=new QByteArray(URLBuffer[i].URL.toLatin1());
                    char *data1=bytearray1->data();
                    QByteArray *bytearray2=new QByteArray(URLBuffer[i].Date.toLatin1());
                    char *data2=bytearray2->data();

                    URLFile.write((char*)&URLBuffer[i].Count,sizeof(int)*1);
                    URLFile.write(data1,URLBuffer[i].URL.length());
                    URLFile.write((char*)"\r\n",3);
                    URLFile.write(data2,URLBuffer[i].Date.length());
                    URLFile.write((char*)"\r\n",3);
                }
                URLBufferCount=0;
            }
        }
        else if(Data[0]=='Q')   //关键字
        {                       //格式:  单词（换行）int（位置）
            QString Word="";
            for(int i=2;i<length;i++)
            {
                if(Data[i]==' ' || Data[i]=='\r')
                {
                    if(CurrentBuffer==20000)
                    {
                        SortWays quicksort(QString(QString::number(Count,10)+".txt"));
                        Count++;
                        quicksort.SortData(WriteBuffer,20000);
                        CurrentBuffer=0;
                    }
                    WriteBuffer[CurrentBuffer].Word=Word;
                    WriteBuffer[CurrentBuffer].Position=URLCount;
                    CurrentBuffer++;
                    Word="";
                }
                else
                {
                    Word+=Data[i];
                }
            }
        }
    }

    if(CurrentBuffer!=0)
    {
        SortWays quicksort(QString(QString::number(Count,10)+".txt"));
        Count++;
        quicksort.SortData(WriteBuffer,CurrentBuffer);
    }
    if(URLBufferCount!=0)
    {
        for(int i=0;i<URLBufferCount;i++)
        {
            QByteArray *bytearray1=new QByteArray(URLBuffer[i].URL.toLatin1());
            char *data1=bytearray1->data();
            QByteArray *bytearray2=new QByteArray(URLBuffer[i].Date.toLatin1());
            char *data2=bytearray2->data();

            URLFile.write((char*)&URLBuffer[i].Count,sizeof(int)*1);
            URLFile.write(data1,URLBuffer[i].URL.length());
            URLFile.write((char*)"\r\n",3);
            URLFile.write(data2,URLBuffer[i].Date.length());
            URLFile.write((char*)"\r\n",3);
        }
        //URLBufferCount++;
    }

    SortWays quicksort;
    quicksort.SortData(Count);


    for(int i=0;i<Count;i++)
    {
        QString filename=QString(QString::number(i,10)+".txt");
        QFile j(filename);
        j.remove();
    }

    GetPageRank();
}

int InvertedIndex::GetHashValue(QString url)
{
    int Length=url.length();
    QByteArray bytearray;
    char *Data;
    bytearray=url.toLatin1();
    Data=bytearray.data();

    int Position=0;
    if(Length>=29)
    {
        for(int i=9;i<29;i++)
        {
            Position+=Data[i];
        }
    }
    else
    {
        for(int i=9;i<Length;i++)
        {
            Position+=Data[i];
        }
    }
    return Position%10000;
}
void InvertedIndex::GetPageRank()
{
    double Weight=0;
    double *Result=new double[URLCount];
    for(int i=0;i<URLCount;i++)
    {
        Result[i]=0;
    }

    QFile *GetRank=new QFile(Path);
    GetRank->open(QIODevice::ReadOnly);
    int CurrentPage=-1;
    char* Data=new char[3*1024];
    int length=0;
    int position=0;

    QQueue<int> LinkS;
    while(!GetRank->atEnd())
    {
        length=GetRank->readLine(Data,3072);
        if(length==-1)
        {
            break;
        }

        if(Data[0]=='P')        //URL
        {
            if(Weight!=0)
            {
                while(!LinkS.empty())
                {
                    Result[LinkS.front()]+=1/Weight;
                    LinkS.pop_back();
                }
            }
            CurrentPage++;
            Weight=0;
        }
        else if(Data[0]=='L')    //超链接
        {
            Data[0]='P';
            position=HashOfURL[GetHashValue(Data)].Find(Data);
            if(position!=-1)
            {
                LinkS.push_back(position);
                Weight++;
            }
        }
    }
    while(!LinkS.empty())
    {
        Result[LinkS.front()]+=1/Weight;
        LinkS.pop_back();
    }

    remove("PageRank.txt");
    QFile PageRank("PageRank.txt");
    PageRank.open(QIODevice::WriteOnly);
    for(int i=0;i<URLCount;i++)
    {
        PageRank.write((char*)&i,sizeof(int)*1);
        PageRank.write((char*)&Result[i],sizeof(double)*1);
    }
}
