#ifndef SWAPDIALOG_H
#define SWAPDIALOG_H

#include <QDialog>
#include"rebuilddialog.h"

namespace Ui {
class SwapDialog;
}

class SwapDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SwapDialog(QWidget *parent = 0);
    ~SwapDialog();

    TheBinaryTree<char> *TreeSwap;
private:
    Ui::SwapDialog *ui;

public slots:
   void ConnectSwapTree(TheBinaryTree<char>* treeswap);

private slots:
   void on_pushButton_clicked();


};

#endif // SWAPDIALOG_H
