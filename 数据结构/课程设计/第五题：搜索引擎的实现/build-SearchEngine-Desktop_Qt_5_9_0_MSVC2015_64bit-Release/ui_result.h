/********************************************************************************
** Form generated from reading UI file 'result.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESULT_H
#define UI_RESULT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Result
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QGridLayout *gridLayout_2;
    QListWidget *listWidget;
    QWidget *page_2;
    QGridLayout *gridLayout_3;
    QListWidget *listWidget_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Result)
    {
        if (Result->objectName().isEmpty())
            Result->setObjectName(QStringLiteral("Result"));
        Result->resize(828, 629);
        centralwidget = new QWidget(Result);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        gridLayout_2 = new QGridLayout(page);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        listWidget = new QListWidget(page);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        gridLayout_2->addWidget(listWidget, 0, 0, 1, 1);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        gridLayout_3 = new QGridLayout(page_2);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        listWidget_2 = new QListWidget(page_2);
        listWidget_2->setObjectName(QStringLiteral("listWidget_2"));

        gridLayout_3->addWidget(listWidget_2, 0, 0, 1, 1);

        stackedWidget->addWidget(page_2);

        gridLayout->addWidget(stackedWidget, 0, 0, 1, 1);

        Result->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Result);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 828, 26));
        Result->setMenuBar(menubar);
        statusbar = new QStatusBar(Result);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        Result->setStatusBar(statusbar);

        retranslateUi(Result);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Result);
    } // setupUi

    void retranslateUi(QMainWindow *Result)
    {
        Result->setWindowTitle(QApplication::translate("Result", "\346\220\234\347\264\242\347\273\223\346\236\234", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Result: public Ui_Result {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESULT_H
