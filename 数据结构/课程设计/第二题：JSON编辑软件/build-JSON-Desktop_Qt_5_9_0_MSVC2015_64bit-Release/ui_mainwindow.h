/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_2;
    QAction *action_3;
    QAction *action_4;
    QAction *action_6;
    QAction *action_7;
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout;
    QTreeWidget *treeWidget;
    QWidget *tab_2;
    QGridLayout *gridLayout_3;
    QTextEdit *textEdit_3;
    QMenuBar *menuBar;
    QMenu *menu_3;
    QMenu *menu;
    QMenu *menu_2;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QGridLayout *gridLayout_4;
    QLabel *label;
    QComboBox *comboBox;
    QLabel *label_3;
    QTextEdit *textEdit;
    QLabel *label_2;
    QTextEdit *textEdit_2;
    QSpacerItem *verticalSpacer;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(809, 671);
        action_2 = new QAction(MainWindow);
        action_2->setObjectName(QStringLiteral("action_2"));
        action_3 = new QAction(MainWindow);
        action_3->setObjectName(QStringLiteral("action_3"));
        action_4 = new QAction(MainWindow);
        action_4->setObjectName(QStringLiteral("action_4"));
        action_6 = new QAction(MainWindow);
        action_6->setObjectName(QStringLiteral("action_6"));
        action_7 = new QAction(MainWindow);
        action_7->setObjectName(QStringLiteral("action_7"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout = new QGridLayout(tab);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        treeWidget = new QTreeWidget(tab);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));

        gridLayout->addWidget(treeWidget, 0, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        gridLayout_3 = new QGridLayout(tab_2);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        textEdit_3 = new QTextEdit(tab_2);
        textEdit_3->setObjectName(QStringLiteral("textEdit_3"));

        gridLayout_3->addWidget(textEdit_3, 0, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());

        gridLayout_2->addWidget(tabWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 809, 26));
        menu_3 = new QMenu(menuBar);
        menu_3->setObjectName(QStringLiteral("menu_3"));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        dockWidget = new QDockWidget(MainWindow);
        dockWidget->setObjectName(QStringLiteral("dockWidget"));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        gridLayout_4 = new QGridLayout(dockWidgetContents);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        label = new QLabel(dockWidgetContents);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_4->addWidget(label, 0, 0, 1, 1);

        comboBox = new QComboBox(dockWidgetContents);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        gridLayout_4->addWidget(comboBox, 1, 0, 1, 1);

        label_3 = new QLabel(dockWidgetContents);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_4->addWidget(label_3, 2, 0, 1, 1);

        textEdit = new QTextEdit(dockWidgetContents);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        gridLayout_4->addWidget(textEdit, 3, 0, 1, 1);

        label_2 = new QLabel(dockWidgetContents);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_4->addWidget(label_2, 4, 0, 1, 1);

        textEdit_2 = new QTextEdit(dockWidgetContents);
        textEdit_2->setObjectName(QStringLiteral("textEdit_2"));

        gridLayout_4->addWidget(textEdit_2, 5, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 317, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer, 6, 0, 1, 1);

        dockWidget->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menu_3->menuAction());
        menu_3->addAction(action_2);
        menu->addAction(action_3);
        menu->addAction(action_4);
        menu_2->addAction(action_6);
        menu_2->addAction(action_7);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "JSON\347\274\226\350\276\221\350\275\257\344\273\266", Q_NULLPTR));
        action_2->setText(QApplication::translate("MainWindow", "\346\237\245\346\211\276", Q_NULLPTR));
        action_3->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200", Q_NULLPTR));
        action_4->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230", Q_NULLPTR));
        action_6->setText(QApplication::translate("MainWindow", "\345\216\213\347\274\251", Q_NULLPTR));
        action_7->setText(QApplication::translate("MainWindow", "\346\240\274\345\274\217\345\214\226", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "\350\247\206\345\233\276", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "\346\226\207\346\234\254", Q_NULLPTR));
        menu_3->setTitle(QApplication::translate("MainWindow", "\346\237\245\350\257\242", Q_NULLPTR));
        menu->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266", Q_NULLPTR));
        menu_2->setTitle(QApplication::translate("MainWindow", "\346\226\207\346\234\254\346\240\274\345\274\217", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\347\261\273\345\236\213\357\274\232", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "\345\255\227\347\254\246\344\270\262", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\346\225\260\345\255\227", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\345\257\271\350\261\241", Q_NULLPTR)
        );
        label_3->setText(QApplication::translate("MainWindow", "\345\220\215\347\247\260\357\274\232", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "\345\200\274\357\274\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
