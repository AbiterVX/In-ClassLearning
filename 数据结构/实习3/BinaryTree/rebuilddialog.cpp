#include "rebuilddialog.h"
#include "ui_rebuilddialog.h"

RebuildDialog::RebuildDialog(QWidget *parent) :QDialog(parent),ui(new Ui::RebuildDialog)
{
    ui->setupUi(this);
    ui->textEdit->append("ABDHLEKCFG");
    ui->textEdit_2->append("HLDBEKAFCG");
}

RebuildDialog::~RebuildDialog()
{
    delete ui;
}





void RebuildDialog::on_pushButton_clicked()
{
    QString PreOrder;
    PreOrder= ui->textEdit->toPlainText();
    QString InOrder;
    InOrder=ui->textEdit_2->toPlainText();

    char *preOrder;
    char *inOrder;

    QByteArray transform;
    transform=PreOrder.toLatin1();
    preOrder=transform.data();

    QByteArray transform1;
    transform1=InOrder.toLatin1();
    inOrder=transform1.data();

    int length=PreOrder.length();
    TreeRebuild->ConfirmBinaryTree(preOrder,inOrder,length);

}


void RebuildDialog::ConnectRebuildTree(TheBinaryTree<char>* treerebuild)
{
     TreeRebuild=treerebuild;
}



