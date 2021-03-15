#include "finddialog.h"
#include "ui_finddialog.h"

FindDialog::FindDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindDialog)
{
    ui->setupUi(this);
}

FindDialog::~FindDialog()
{
    delete ui;
}

void FindDialog::ConnectFindTree(TheBinaryTree<char>* treefind)
{
    TreeFind=treefind;
}



void FindDialog::on_pushButton_clicked()
{
    QString Data=ui->textEdit->toPlainText();
    remove("Tree.txt");
    QByteArray bytearray=Data.toLatin1();
    char *key=bytearray.data();
    TreeFind->Find(key[0],TreeFind->GetRoot());


    QProcess *process =new QProcess();
    QString notepadpath ="notepad.exe Tree.txt";
    process->start(notepadpath);
}
