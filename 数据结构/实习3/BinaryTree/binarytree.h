#ifndef BINARYTREE_H
#define BINARYTREE_H


#include <QMainWindow>

#include "finddialog.h"
#include<fstream>
using namespace std;


namespace Ui {
class BinaryTree;
}

class BinaryTree : public QMainWindow
{
    Q_OBJECT
public:
    explicit BinaryTree(QWidget *parent = 0);
    ~BinaryTree();

private slots:
    void on_action_triggered();
    void on_action_2_triggered();
    void on_action_3_triggered();
    void on_action_4_triggered();
    void on_action_5_triggered();

    void on_pushButton_clicked();
private:
    Ui::BinaryTree *ui;

    TheBinaryTree<char> *tree;  //二叉树对象


    RebuildDialog *RebuildTree;
    OutPutDialog  *OutPutTree;
    DrawDialoge1    *DrawTree;
    FindDialog  *FindTree;
    SwapDialog *SwapTree;
signals:
    void TreeConnect(TheBinaryTree<char>* NewTree);



};

#endif // BINARYTREE_H
