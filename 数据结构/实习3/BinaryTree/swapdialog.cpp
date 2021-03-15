#include "swapdialog.h"
#include "ui_swapdialog.h"

SwapDialog::SwapDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SwapDialog)
{
    ui->setupUi(this);
}

SwapDialog::~SwapDialog()
{
    delete ui;
}
void SwapDialog::ConnectSwapTree(TheBinaryTree<char>* treeswap)
{
    TreeSwap=treeswap;
}


void SwapDialog::on_pushButton_clicked()
{
    TreeSwap->SwapTree(TreeSwap->GetRoot());
}
