#ifndef RESULT_H
#define RESULT_H

#include <QMainWindow>
#include<QFile>


struct EachURL
{
    QString URL;
    QString Date;    
};



namespace Ui {
class Result;
}

class Result : public QMainWindow
{
    Q_OBJECT

public:

    explicit Result(QWidget *parent = 0);
    ~Result();
    void GetData(int *data,int count)
    {
        Count=count;
        Data=new int[count];
        for(int i=0;i<Count;i++)
        {
            Data[i]=data[i];
        }
        findURL();
    }
    int GetHashValue(QString url)
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
        return Position%1000;
    }
    void QuickSort(EachURL * &ResultURL,int * &Data,const int low,const int high);
    void findURL();
private:
    Ui::Result *ui;
    int *Data;
    int Count;
};

#endif // RESULT_H
