#include "find.h"
#include "ui_find.h"

#include<QQueue>
Find::Find(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Find)
{
    ui->setupUi(this);
}

Find::~Find()
{
    delete ui;
}

void Find::on_pushButton_clicked()
{   
    QString Data=ui->textEdit->toPlainText();
    QString Result=FindNode(Data);
    ui->textEdit_2->clear();
    ui->textEdit_2->append(Result);

}


QString Find::FindNode(QString FindData)
{
    QString Result;
    QTreeWidgetItem *CurrentNode=Tree->currentItem();
    int Length=FindData.length();
    bool Read=0;
    bool All=0;
    bool Mutiple=0;
    QString CurrentData="";
    QQueue<QTreeWidgetItem*> ItemS;
    if(FindData[0]=='$')
    {
        for(int i=1;i<Length;i++)
        {
            if(FindData[i]=='.')
            {
                if(Read==0)
                {
                    Read=1;
                    if(FindData[i+1]!='.')
                    {
                        All=0;
                    }
                    else
                    {
                        All=1;
                        i++;
                    }
                }
                else
                {
                    Read=0;
                    int ChildNumber=CurrentNode->childCount();
                    QString data;
                    if(All==0)
                    {
                        for(int j=0;j<ChildNumber;j++)
                        {
                            data=CurrentNode->child(j)->text(0).mid(0,CurrentNode->child(j)->text(0).indexOf(':'));
                            if(data==CurrentData)
                            {
                                CurrentNode=CurrentNode->child(j);
                                break;
                            }
                        }
                    }
                    else
                    {
                        Mutiple=1;
                        for(int j=0;j<ChildNumber;j++)
                        {
                            data=CurrentNode->child(j)->text(0).mid(0,CurrentNode->child(j)->text(0).indexOf(':'));
                            if(data==CurrentData)
                            {
                                ItemS.push_back(CurrentNode->child(j));
                            }
                        }
                    }
                }
                CurrentData="";
            }
            else if(FindData[i]=='[')
            {
                if(Read==1)
                {
                    Read=0;
                    int ChildNumber=CurrentNode->childCount();
                    QString data;
                    if(All==0)
                    {
                        for(int j=0;j<ChildNumber;j++)
                        {
                            data=CurrentNode->child(j)->text(0).mid(0,CurrentNode->child(j)->text(0).indexOf(':'));
                            if(data==CurrentData)
                            {
                                CurrentNode=CurrentNode->child(j);
                                break;
                            }
                        }
                    }
                    else
                    {
                        for(int j=0;j<ChildNumber;j++)
                        {
                            data=CurrentNode->child(j)->text(0).mid(0,CurrentNode->child(j)->text(0).indexOf(':'));
                            if(data==CurrentData)
                            {
                                ItemS.push_back(CurrentNode->child(j));
                            }
                        }
                    }
                    CurrentData="";
                    i++;

                    for(;FindData[i]==']';i++)
                    {
                        CurrentData+=FindData[i];
                    }
                }
            }
            else
            {
                if(FindData[i]=='*')
                {
                    if(All==0)
                    {
                        int length=CurrentNode->childCount();
                        for(int k=0;k<length;k++)
                        {
                            Result+=CurrentNode->child(k)->text(0)+"\n";
                        }
                    }
                    else
                    {
                        int Count=ItemS.length();
                        int length=0;
                        for(int k=0;k<Count;k++)
                        {
                            CurrentNode=ItemS.head();
                            length=CurrentNode->childCount();
                            ItemS.pop_front();
                            for(int j=0;j<length;j++)
                            {
                                Result+=CurrentNode->child(j)->text(0)+"\n";
                            }
                        }
                    }
                }
                else
                {
                    if(Read==1)
                    {
                        CurrentData+=FindData[i];
                        if(Length==i+1)
                        {
                            Result=find(CurrentNode,CurrentData);
                        }
                    }
                }
            }
        }
    }

    return Result;
}

QString Find::find(QTreeWidgetItem *CurrentNode, QString Data)
{
    QString Result;
    QQueue<QTreeWidgetItem *> queue;
    QTreeWidgetItem *Current=CurrentNode;

    if(Current->text(0)==Data)
    {
        return Current->text(0);
    }
    else
    {
        QString data=Current->text(0).mid(0,Current->text(0).indexOf(':'));
        if(data==Data)
        {
            return Current->text(0);
        }
        for(int i=0;i<Current->childCount();i++)
        {
            queue.push_back(Current->child(i));
        }
        while(!queue.empty())
        {
            Current=queue.first();
            queue.pop_front();
            if(Current->text(0)==Data)
            {
                Result+=Current->text(0)+"\n";
            }
            else
            {
                QString data=Current->text(0).mid(0,Current->text(0).indexOf(':'));
                if(data==Data)
                {
                    Result+=Current->text(0)+"\n";
                }
                for(int i=0;i<Current->childCount();i++)
                {
                    queue.push_back(Current->child(i));
                }
            }
        }
    }

    return Result;
}

/*
if(Current->text(0)==Data)
{
    return Current;
}
else
{
    QString data=Current->text(0).mid(0,Current->text(0).indexOf(':'));
    if(data==Data)
    {
        return Current;
    }
    for(int i=0;i<Current->childCount();i++)
    {
        queue.push_back(Current->child(i));
    }
    while(!queue.empty())
    {
        Current=queue.first();
        queue.pop_front();
        if(Current->text(0)==Data)
        {
            return Current;
        }
        else
        {
            QString data=Current->text(0).mid(0,Current->text(0).indexOf(':'));
            if(data==Data)
            {
                return Current;
            }
            for(int i=0;i<Current->childCount();i++)
            {
                queue.push_back(Current->child(i));
            }
        }

    }
}

QTreeWidgetItem *NULLNode=new QTreeWidgetItem();
NULLNode->setText(0,"NULL");*/





















