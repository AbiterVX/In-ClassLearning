#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include"swapdialog.h"
namespace Ui {
class FindDialog;
}

class FindDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindDialog(QWidget *parent = 0);
    ~FindDialog();


    TheBinaryTree<char> *TreeFind;
public slots:
   void ConnectFindTree(TheBinaryTree<char>* treefind);


private slots:
    void on_pushButton_clicked();

private:
    Ui::FindDialog *ui;
};

#endif // FINDDIALOG_H
