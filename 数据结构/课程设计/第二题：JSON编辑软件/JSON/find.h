#ifndef FIND_H
#define FIND_H

#include <QMainWindow>
#include<QTreeWidget>


namespace Ui {
class Find;
}

class Find : public QMainWindow
{
    Q_OBJECT

public:
    explicit Find(QWidget *parent = 0);
    ~Find();

    void SetTree(QTreeWidget *tree)
    {
        Tree=tree;
    }

    QString FindNode(QString FindData);
    QString find(QTreeWidgetItem *CurrentNode, QString Data);
private slots:
    void on_pushButton_clicked();

private:
    Ui::Find *ui;
    QTreeWidget * Tree;
};

#endif // FIND_H
