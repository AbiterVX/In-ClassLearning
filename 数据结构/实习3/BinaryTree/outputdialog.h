#ifndef OUTPUTDIALOG_H
#define OUTPUTDIALOG_H

#include <QDialog>
#include"drawdialoge1.h"


namespace Ui {
class OutPutDialog;
}

class OutPutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OutPutDialog(QWidget *parent = 0);
    ~OutPutDialog();


    TheBinaryTree<char> *TreeOutPut;

private:
    Ui::OutPutDialog *ui;


public slots:
   void ConnectOutPutTree(TheBinaryTree<char>* treeoutput);


private slots:
   void on_pushButton_clicked();
};

#endif // OUTPUTDIALOG_H
