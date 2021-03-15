#ifndef MERGESORT_H
#define MERGESORT_H
#endif // MERGESORT_H
#include<QString>
#include<QFile>
#include<QQueue>
#include<QDebug>

struct SortNode
{
    QString Word;
    int TimeS;
    int Position;
    SortNode()
    {
        Word="";
        Position=0;
        TimeS=1;
    }
};
struct MergeWord
{
    QString Word;
    int TimeS;
    int *PositionS;
    MergeWord()
    {
        Word="";
        TimeS=0;
        PositionS=NULL;
    }
    void Load(int *positions,int times)
    {
        TimeS=times;
        PositionS=new int[times];
        for(int i=0;i<times;i++)
        {
            PositionS[i]=positions[i];
        }
    }
};




class SortWays
{
public:
    SortWays()
    {
        Path="";
    }
    SortWays(QString path)
    {
        Path=path;
    }
    void SetPath(QString path)
    {
        Path=path;
    }
    void QuickSortData(SortNode* &Data,int number)
    {
        QuickSort(Data,0,number-1);
    }
    void SortData(SortNode* &Data,int number)//每块初始化，快排
    {
        QuickSort(Data,0,number-1);

        QByteArray bytearray=Path.toLatin1();
        char *WordName=bytearray.data();
        remove(WordName);
        QFile Write(Path);
        Write.open(QIODevice::ReadWrite);

        int WordEnd=-1;
        QString CurrentWord="";
        bool begin=0;
        for(int i=0;i<number;i++)
        {
            if(CurrentWord!=Data[i].Word)
            {
                if(begin!=0)
                {
                    Write.write((char*)&WordEnd,sizeof(int)*1);
                }
                begin=1;
                CurrentWord=Data[i].Word;
                QByteArray *bytearray1=new QByteArray(CurrentWord.toLatin1());
                WordName=bytearray1->data();
                Write.write((char*)WordName,CurrentWord.length());
                Write.write((char*)"\r\n",3);
            }
            Write.write((char*)&Data[i].Position,sizeof(int)*1);

        }
        Write.write((char*)&WordEnd,sizeof(int)*1);
    }
    void QuickSort(int * &Data,const int low,const int high)
    {
        if(low>=high)
        {
            return;
        }
        int first=low;
        int last=high;
        int key=Data[first];
        while(first<last)
        {
            while(first<last && Data[last] >=key)
            {
                last--;
            }
            Data[first]=Data[last];
            while(first<last &&Data[first]<=key)
            {
                first++;
            }
            Data[last]=Data[first];
        }
        Data[first]=key;
        QuickSort(Data,low,first-1);
        QuickSort(Data,first+1,high);
    }




    void SortData(int number)  //归并
    {        
        Files=new QFile*[number];

        for(int i=0;i<number;i++)
        {
            Files[i]=new QFile(QString(QString::number(i,10)+".txt"));
            Files[i]->open(QIODevice::ReadOnly);
        }
        MergeSort(number);
        for(int i=0;i<number;i++)
        {
            Files[i]->close();
        }
    }
protected:
    void QuickSort(SortNode* &Data,const int low,const int high)
    {
        if(low>=high)
        {
            return;
        }
        int first=low;
        int last=high;
        SortNode key=Data[first];
        while(first<last)
        {
            while(first<last && Data[last].Word >=key.Word)
            {
                last--;
            }
            Data[first]=Data[last];

            while(first<last &&Data[first].Word<=key.Word)
            {
                first++;
            }
            Data[last]=Data[first];
        }
        Data[first]=key;
        QuickSort(Data,low,first-1);
        QuickSort(Data,first+1,high);
    }
    void MergeSort(int FilesNumber)
    {
        remove("Dictionary.txt");
        QFile Dictionary("Dictionary.txt");
        Dictionary.open(QIODevice::ReadWrite);

        MergeNumber=FilesNumber;
        Losers=new int[MergeNumber];
        Feasible=new bool[MergeNumber];
        MergeDataS=new QString[MergeNumber+1];
        PositionS=new QQueue<int>[MergeNumber];

        char *Word=new char[1024];
        char *Word1;
        char null;        
        int length=0;
        int position=0;
        int Length=0;

        for(int i=0;i<MergeNumber;i++)
        {
            Feasible[i]=1;
            length=Files[i]->readLine((char*)Word,1024);
            Word[length-2]='\0';
            MergeDataS[i]=QString(QLatin1String(Word));
            Files[i]->read((char*)&null,sizeof(char)*1);
            while(1)
            {
                Files[i]->read((char*)&position,sizeof(int)*1);
                if(position!=-1)
                {
                    PositionS[i].push_back(position);
                }
                else
                {
                    break;
                }
            }
        }
        CreateLoserTree();

        int Remain=FilesNumber;
        int End=-1;
        bool begin=0;
        QString CurrentWord="";
        while(Remain!=0)
        {                       
            if(CurrentWord!=MergeDataS[Losers[0]])
            {
                if(begin!=0)
                {
                    Dictionary.write((char*)&End,sizeof(int)*1);
                }
                begin=1;
                CurrentWord=MergeDataS[Losers[0]];
                QByteArray *bytearray=new QByteArray(MergeDataS[Losers[0]].toLatin1());
                Word1=bytearray->data();
                Dictionary.write((char*)Word1,MergeDataS[Losers[0]].length());
                Dictionary.write((char*)"\r\n",3);
            }
            Length=PositionS[Losers[0]].length();
            for(int i=0;i<Length;i++)
            {
                Dictionary.write((char*)&PositionS[Losers[0]].front(),sizeof(int)*1);
                PositionS[Losers[0]].pop_front();
            }


            if(!Files[Losers[0]]->atEnd())
            {
                length=Files[Losers[0]]->readLine((char*)Word,1024);
                Word[length-2]='\0';
                MergeDataS[Losers[0]]=QString(QLatin1String(Word));
                Files[Losers[0]]->read((char*)&null,sizeof(char)*1);               
                while(1)
                {
                    Files[Losers[0]]->read((char*)&position,sizeof(int)*1);
                    if(position!=-1)
                    {
                         PositionS[Losers[0]].push_back(position);
                    }
                    else
                    {
                        break;
                    }
                }
                Adjust(Losers[0]);
            }
            else
            {
                Remain--;
                Feasible[Losers[0]]=0;
                MergeDataS[Losers[0]]="zzzzz";               
                Losers[0]=MergeNumber;
                for(int i=MergeNumber-1;i>=0;i--)
                {
                    Adjust(i);
                }
            }
        }

        Dictionary.write((char*)&End,sizeof(int)*1);
    }
    void CreateLoserTree()
    {
        MergeDataS[MergeNumber]="";
        for(int i=0;i<MergeNumber;i++)
        {
            Losers[i]=MergeNumber;
        }
        for(int i=MergeNumber-1;i>=0;i--)
        {
            Adjust(i);
        }

    }
    void Adjust(int Winner)
    {
        int NewLoser;                       //临时变量
        int Parent=(Winner+MergeNumber)/2;  //父节点，初始化
        while(Parent>0)                       //回溯到根节点
        {
            if(MergeDataS[Winner] > MergeDataS[Losers[Parent]]) //如果失败
            {
                NewLoser=Winner;         //交换
                Winner=Losers[Parent];
                Losers[Parent]=NewLoser;
            }
            Parent=Parent/2;
        }
        Losers[0]=Winner;
    }

private:
    QString Path;
    int *Losers;
    int MergeNumber;
    QFile** Files;
    bool *Feasible;

    QString *MergeDataS;
    QQueue<int> *PositionS;
    //int *TimeS;


};







