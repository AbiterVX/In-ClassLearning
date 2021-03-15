#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<analyse.h>
#include<QTreeWidget>
#include"find.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



private:
    Ui::MainWindow *ui;

    Find *find;

private slots:
    void on_tabWidget_currentChanged(int index);    
    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);



    void on_action_6_triggered();
    void on_action_7_triggered();
    void on_action_3_triggered();
    void on_action_4_triggered();

    void on_action_2_triggered();
};

#endif // MAINWINDOW_H
