#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<QFileDialog>

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)
{   
    ui->setupUi(this);
    ui->treeWidget->setColumnCount(1);
    ui->treeWidget->setHeaderLabel(tr("树形视图"));

    find=new Find();

}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    int CurrentTab=ui->tabWidget->currentIndex();
    if(CurrentTab==0)
    {
        if(ui->textEdit_3->toPlainText()!="")
        {
            QString Data=ui->textEdit_3->toPlainText();

            JSONAnalyse json;

            Data=json.RegulatePress(Data);/////
            json.Input(Data);
            json.Analyse(ui->treeWidget);

            ui->treeWidget->expandAll();
        }
    }
    else if(CurrentTab==1)
    {
        ui->treeWidget->clear();
    }
}

void MainWindow::on_action_6_triggered()
{
    JSONAnalyse regulate;
    QString Data=ui->textEdit_3->toPlainText();
    Data=regulate.RegulatePress(Data);
    ui->textEdit_3->clear();
    ui->textEdit_3->append(Data);
}

void MainWindow::on_action_7_triggered()
{
    JSONAnalyse regulate;
    QString Data=ui->textEdit_3->toPlainText();
    Data=regulate.RegulatePress(Data);
    Data=regulate.RegulateDePress(Data);
    ui->textEdit_3->clear();
    ui->textEdit_3->append(Data);


}


void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    ui->textEdit->clear();
    ui->textEdit_2->clear();
    QString Data;
    Data=ui->treeWidget->currentItem()->text(0);
    int Position=Data.indexOf(":");
    QString Name=Data.mid(0,Position);
    ui->textEdit->append(Name);

    QString Value;
    if(Position != -1)
    {
        Value=Data.mid(Position+1,Data.length()-Position-1);
        int Length=Value.length();
        while(1)
        {
            if(Value[Length-1]=='\t'||Value[Length-1]==' ')
            {
                Value=Value.left(Value.length()-1);
            }
            else
            {
                break;
            }
            Length=Value.length();
        }
        while(1)
        {
            if(Value[0]=='\t'|| Value[0]==' ')
            {
                Value=Value.right(Value.length()-1);
            }
            else
            {
                break;
            }
        }
    }
    else
    {
        Value=" ";
    }

    if(Value[0]=="\"")
    {

        ui->textEdit_2->append(Value.mid(1,Value.length()-2));
    }
    else
    {
        ui->textEdit_2->append(Value);
    }


    if(Value==" ")
    {
        ui->comboBox->setCurrentIndex(2);
    }
    else
    {
        if(Value[0]=="\"")
        {
            ui->comboBox->setCurrentIndex(0);
        }
        else
        {
            ui->comboBox->setCurrentIndex(1);
        }
    }




}


void MainWindow::on_action_3_triggered()  //打开
{
    QString fileName=QFileDialog::getOpenFileName(this,tr("Open File..."),".",
                                                  tr("DOC Files(*.txt *.doc *.docx )") );
    QFile InPut(fileName);
    InPut.open(QIODevice::ReadOnly);
    QByteArray Data=InPut.readAll();
    QString TextData(Data);

    ui->textEdit_3->clear();
    ui->textEdit_3->append(TextData);
}

void MainWindow::on_action_4_triggered()   //保存
{
    QString fileName=QFileDialog::getSaveFileName(this,tr("Open File..."),".",
                                                  tr("Text files(*.txt);;DOC files( *.doc *.docx )"));
    QFile OutPut(fileName);
    OutPut.open(QIODevice::ReadWrite);

    QTextStream out(&OutPut);
    out<<ui->textEdit_3->toPlainText();
}



void MainWindow::on_action_2_triggered()
{
    find->SetTree(ui->treeWidget);
    find->show();
}









