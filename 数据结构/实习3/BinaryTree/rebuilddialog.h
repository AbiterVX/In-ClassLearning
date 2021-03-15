#ifndef REBUILDDIALOG_H
#define REBUILDDIALOG_H

#include <QDialog>

#include"outputdialog.h"


namespace Ui {
class RebuildDialog;
}

class RebuildDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RebuildDialog(QWidget *parent = 0);
    ~RebuildDialog();


   TheBinaryTree<char> *TreeRebuild;

private slots:
    void on_pushButton_clicked();

private:
    Ui::RebuildDialog *ui;


public slots:
   void ConnectRebuildTree(TheBinaryTree<char>* treerebuild);

};

#endif // REBUILDDIALOG_H
