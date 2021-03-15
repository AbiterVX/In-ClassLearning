#ifndef ANALYSE_H
#define ANALYSE_H

#endif // ANALYSE_H
#include<QString>
#include<QStack>

#include<QTreeWidgetItem>


struct Point
{
    int Type;
    QTreeWidgetItem* Node;
    Point(int type=0,QTreeWidgetItem* node=NULL)
    {        
        Type=type;
        Node=node;
    }
};


class JSONAnalyse
{
private:
    QString Data;
    QStack<Point> ParentStack;
public:
    JSONAnalyse()
    {

    }

    void Input(QString data)
    {
        RegulateString(data);
        Data=data;
    }

    JSONAnalyse(QString data)
    {
        RegulateString(data);
        Data=data;
    }

    void Analyse(QTreeWidget * &widget)
    {

        int Begin=-1;        //截断数据名称
        int End=-1;
        bool HaveBegin=0;
        QString CurrentName;
        CurrentName="Root";

        bool HaveValueBegin=0;
        int ValueBegin=-1;   //截断数据值
        int ValueEnd=-1;

        int Length=Data.length();            //总长
        QTreeWidgetItem *CurrentParent=NULL; //当前节点


        for(int i=0;i<Length;i++)
        {
            if(Data[i]=='{')
            {
                QTreeWidgetItem *NewNode;
                if(CurrentParent==NULL)
                {
                    NewNode=new QTreeWidgetItem(widget,QStringList(CurrentName));
                    widget->setCurrentItem(NewNode);
                }
                else
                {
                    RegulateString(CurrentName);
                    NewNode=new QTreeWidgetItem(CurrentParent,QStringList(CurrentName));
                }
                NewNode->setIcon(0,QIcon("a.png"));
                Point NewPoint(1,NewNode);
                ParentStack.push(NewPoint);
                CurrentParent=NewNode;
            }
            else if(Data[i]=='[')
            {
                RegulateString(CurrentName);
                QTreeWidgetItem *NewNode=new QTreeWidgetItem(CurrentParent,QStringList(CurrentName));
                NewNode->setIcon(0,QIcon("b.png"));
                Point NewPoint(2,NewNode);
                ParentStack.push(NewPoint);
                CurrentParent=NewNode;
            }

            else if(Data[i]=='}')
            {
                if(HaveValueBegin)
                {
                    ValueEnd=i;
                    HaveValueBegin=0;
                    CurrentName=CurrentName+Data.mid(ValueBegin,ValueEnd-ValueBegin);
                    RegulateString(CurrentName);
                    QTreeWidgetItem *NewNode=new QTreeWidgetItem(CurrentParent,QStringList(CurrentName));
                    NewNode->setIcon(0,QIcon("c.png"));
                }
                if(!ParentStack.empty())
                {
                    ParentStack.pop();
                    if(!ParentStack.empty())
                    {
                        CurrentParent=ParentStack.top().Node;
                    }
                }
            }          
            else if(Data[i]==']')
            {
                if(HaveValueBegin)
                {
                    ValueEnd=i;
                    HaveValueBegin=0;
                    CurrentName=CurrentName+Data.mid(ValueBegin,ValueEnd-ValueBegin);
                    RegulateString(CurrentName);
                    QTreeWidgetItem *NewNode=new QTreeWidgetItem(CurrentParent,QStringList(CurrentName));
                    NewNode->setIcon(0,QIcon("c.png"));
                }
                if(!ParentStack.empty())
                {
                    int Count=ParentStack.top().Node->childCount();
                    for(int j=0;j<Count;j++)
                    {
                        QString name="["+QString::number(j,10)+"]";
                        ParentStack.top().Node->child(j)->setText(0,name);
                    }
                    ParentStack.pop();
                    if(!ParentStack.empty())
                    {
                        CurrentParent=ParentStack.top().Node;
                    }
                }
            }

            else if(Data[i]=="\"")
            {
                if(!HaveBegin)
                {
                    Begin=i;
                    HaveBegin=1;
                }
                else
                {
                    End=i;
                    if(i<Length-2 && Data[i+1]==":")
                    {
                        CurrentName=Data.mid(Begin+1,End-Begin-1);
                        RegulateString(CurrentName);
                    }
                    HaveBegin=0;
                }
            }
            else if(Data[i]==":")
            {
                if(Data[i+1]!="{" && Data[i+1] !="[")
                {
                    ValueBegin=i;
                    HaveValueBegin=1;
                }
            }
            else if(Data[i]==",")
            {
                if(HaveValueBegin)
                {
                    ValueEnd=i;
                    HaveValueBegin=0;
                    CurrentName=CurrentName+Data.mid(ValueBegin,ValueEnd-ValueBegin);
                    RegulateString(CurrentName);
                    QTreeWidgetItem *NewNode=new QTreeWidgetItem(CurrentParent,QStringList(CurrentName));
                    NewNode->setIcon(0,QIcon("c.png"));
                }
            }
        }




    }


    QString RegulateDePress(QString data)
    {

        QString Result;
        int EmptySize=0;
        QStack<int> DistanceStack;
        int Length=data.length();

        for(int i=0;i<Length;i++)
        {
            if(data[i]=='{')
            {
                Result+=data[i]+"\r";
                DistanceStack.push(EmptySize);
                EmptySize+=3;
                Result+=AddEmpty(EmptySize);
            }
            else if(data[i]=='[')
            {
                Result+=data[i]+"\r";
                DistanceStack.push(EmptySize);
                EmptySize+=3;
                Result+=AddEmpty(EmptySize);
            }
            else if(data[i]=='}')
            {
                EmptySize=DistanceStack.top();
                DistanceStack.pop();
                Result+="\r"+AddEmpty(EmptySize)+data[i];
            }
            else if(data[i]==']')
            {
                EmptySize=DistanceStack.top();
                DistanceStack.pop();
                Result+="\r"+AddEmpty(EmptySize)+data[i];
            }
            else if(data[i]==",")
            {
                Result+=data[i]+"\r"+AddEmpty(EmptySize);
            }
            else
            {
                Result+=data[i];
            }
        }
        return Result;
    }
    QString AddEmpty(int size)
    {
        QString Empty="";
        for(int i=0;i<size;i++)
        {
            Empty+=" ";
        }
        return Empty;
    }

    QString RegulatePress(QString data)
    {
        RegulateString(data);
        QString Result="";

        QString Part="";
        bool HaveBegin=1;
        int Begin=0;
        int End=0;
        int Length=data.length();
        for(int i=0;i<Length;i++)
        {

            if(data[i]=="\"")
            {
                if(HaveBegin)
                {
                    End=i;
                    Part=data.mid(Begin,End-Begin);
                    Result+=DeleteEmpty(Part);
                    HaveBegin=0;
                    Result+=data[i];
                }
                else
                {
                    Begin=i;
                    HaveBegin=1;
                }
            }
            else
            {
                if(!HaveBegin)
                {
                    Result+=data[i];
                }
                else
                {
                    if(i==Length-1)
                    {
                        End=i;
                        Part=data.mid(Begin,End-Begin+1);
                        Result+=DeleteEmpty(Part);
                    }
                    else
                    {
                       // Result+=data[i];
                    }
                }
            }
        }
        return Result;
    }
    QString DeleteEmpty(QString data)
    {
        QString Result="";
        int Length=data.length();

        QString Part;
        for(int i=0;i<Length;i++)
        {
            Part=data[i];
            if(data[i]!='\n')
            {
                if(data[i]!='\t')
                {
                    if(data[i]!='\r')
                    {
                        if(data[i]!=' ')
                        {
                            Result+=data[i];
                        }
                    }
                }
            }
        }
        return Result;
    }

    void RegulateString(QString &Data)
    {
        int Length=Data.length();

        while(1)
        {
            if(Data.right(4)=="\n\t\t ")
            {
                Data=Data.left(Data.length()-3);
                Length=Data.length();
            }
            if(Data[Length-1]=='\t'|| Data[Length-1]=='\r'|| Data[Length-1]=='\n'||Data[Length-1]==' ')
            {
                Data=Data.left(Data.length()-1);
            }
            else
            {
                break;
            }
            Length=Data.length();
        }
        while(1)
        {
            if(Data[0]=='\t'|| Data[0]=='\r'|| Data[0]=='\n' || Data[0]==' ')
            {
                Data=Data.right(Data.length()-1);
            }
            else
            {
                break;
            }
        }
    }

};















