#include "binarytree.h"
#include "ui_binarytree.h"

//#include<QProcess>
#include<QMessageBox>


BinaryTree::BinaryTree(QWidget *parent) :QMainWindow(parent),ui(new Ui::BinaryTree)
{
    ui->setupUi(this);

    ui->textEdit->append("ABC##DE#G##F###");

    tree = new TheBinaryTree<char>;

    RebuildTree = new RebuildDialog();
    OutPutTree  = new OutPutDialog();
    DrawTree    = new DrawDialoge1();
    FindTree =new FindDialog();
    SwapTree =new SwapDialog();

}

BinaryTree::~BinaryTree()
{
    delete ui;
}



void BinaryTree::on_pushButton_clicked()
{


    QString Data;
    Data= ui->textEdit->toPlainText();
    char *data;
    QByteArray transform;
    transform=Data.toLatin1();
    data=transform.data();


    tree->BuildBinaryTree(data);


    connect(this,SIGNAL(TreeConnect(TheBinaryTree<char> *)) ,DrawTree, SLOT(ConnectDrawTree(TheBinaryTree<char> *)) );
    connect(this,SIGNAL(TreeConnect(TheBinaryTree<char> *)) ,OutPutTree, SLOT(ConnectOutPutTree(TheBinaryTree<char> *)) );
    connect(this,SIGNAL(TreeConnect(TheBinaryTree<char> *)) ,RebuildTree,SLOT(ConnectRebuildTree(TheBinaryTree<char> *)) );
    connect(this,SIGNAL(TreeConnect(TheBinaryTree<char> *)) ,FindTree,SLOT(ConnectFindTree(TheBinaryTree<char>*)) );
    connect(this,SIGNAL(TreeConnect(TheBinaryTree<char> *)) ,SwapTree,SLOT(ConnectSwapTree(TheBinaryTree<char> *)) );
    emit TreeConnect(tree);


    //tree->PreOrder(tree->GetRoot());
    remove("Tree.txt");
    fstream file("Tree.txt", ios_base::out|ios_base::app);
    file<<data;
    file.close();



    QProcess *process =new QProcess();
    QString notepadpath ="notepad.exe Tree.txt";
    process->start(notepadpath);
}



void BinaryTree::on_action_triggered()//重构
{
    RebuildTree->show();
}
void BinaryTree::on_action_2_triggered()//输出
{
    OutPutTree->show();
}
void BinaryTree::on_action_3_triggered()//绘制
{
    DrawTree->show();
}
void BinaryTree::on_action_4_triggered()
{
    FindTree->show();
}

void BinaryTree::on_action_5_triggered()
{
    SwapTree->show();
}
