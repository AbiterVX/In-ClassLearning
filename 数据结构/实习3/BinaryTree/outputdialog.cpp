#include "outputdialog.h"
#include "ui_outputdialog.h"

OutPutDialog::OutPutDialog(QWidget *parent) :QDialog(parent),ui(new Ui::OutPutDialog)
{
    ui->setupUi(this);

    QStringList list;
    list.append("      ");
    list.append("前序输出");
    list.append("中序输出");
    list.append("后序输出");
    list.append("层次输出");
    ui->comboBox->addItems(list);
}

OutPutDialog::~OutPutDialog()
{
    delete ui;
}


void OutPutDialog::ConnectOutPutTree(TheBinaryTree<char>* treeoutput)
{
     TreeOutPut=treeoutput;
}




void OutPutDialog::on_pushButton_clicked()
{
    QString Data=ui->comboBox->currentText();
    remove("Tree.txt");


    if(Data=="前序输出")
    {
        TreeOutPut->PreOrder(TreeOutPut->GetRoot());
    }
    else if(Data=="中序输出")
    {
        TreeOutPut->InOrder(TreeOutPut->GetRoot());
    }
    else if(Data=="后序输出")
    {
        TreeOutPut->PostOrder(TreeOutPut->GetRoot());
    }
    else if(Data=="层次输出")
    {
        TreeOutPut->LevelOrder(TreeOutPut->GetRoot());
    }
    else
    {

    }


    QProcess *process =new QProcess();
    QString notepadpath ="notepad.exe Tree.txt";
    process->start(notepadpath);
}
