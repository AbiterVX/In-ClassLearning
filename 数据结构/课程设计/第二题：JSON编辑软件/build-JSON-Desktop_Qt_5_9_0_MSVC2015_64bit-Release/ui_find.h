/********************************************************************************
** Form generated from reading UI file 'find.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIND_H
#define UI_FIND_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Find
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QTextEdit *textEdit;
    QLabel *label;
    QTextEdit *textEdit_2;
    QLabel *label_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Find)
    {
        if (Find->objectName().isEmpty())
            Find->setObjectName(QStringLiteral("Find"));
        Find->resize(510, 436);
        centralwidget = new QWidget(Find);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(390, 310, 91, 41));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(110, 250, 371, 51));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 250, 91, 41));
        textEdit_2 = new QTextEdit(centralwidget);
        textEdit_2->setObjectName(QStringLiteral("textEdit_2"));
        textEdit_2->setGeometry(QRect(110, 10, 371, 201));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(40, 10, 71, 31));
        Find->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Find);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 510, 26));
        Find->setMenuBar(menubar);
        statusbar = new QStatusBar(Find);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        Find->setStatusBar(statusbar);

        retranslateUi(Find);

        QMetaObject::connectSlotsByName(Find);
    } // setupUi

    void retranslateUi(QMainWindow *Find)
    {
        Find->setWindowTitle(QApplication::translate("Find", "MainWindow", Q_NULLPTR));
        pushButton->setText(QApplication::translate("Find", "\347\241\256\350\256\244", Q_NULLPTR));
        label->setText(QApplication::translate("Find", "\346\237\245\350\257\242\345\206\205\345\256\271\357\274\232", Q_NULLPTR));
        label_2->setText(QApplication::translate("Find", "\347\273\223\346\236\234\357\274\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Find: public Ui_Find {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIND_H
