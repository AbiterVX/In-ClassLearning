/********************************************************************************
** Form generated from reading UI file 'drawdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRAWDIALOG_H
#define UI_DRAWDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DrawDialog
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *DrawDialog)
    {
        if (DrawDialog->objectName().isEmpty())
            DrawDialog->setObjectName(QStringLiteral("DrawDialog"));
        DrawDialog->resize(473, 351);
        centralwidget = new QWidget(DrawDialog);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        DrawDialog->setCentralWidget(centralwidget);
        menubar = new QMenuBar(DrawDialog);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 473, 26));
        DrawDialog->setMenuBar(menubar);
        statusbar = new QStatusBar(DrawDialog);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        DrawDialog->setStatusBar(statusbar);

        retranslateUi(DrawDialog);

        QMetaObject::connectSlotsByName(DrawDialog);
    } // setupUi

    void retranslateUi(QMainWindow *DrawDialog)
    {
        DrawDialog->setWindowTitle(QApplication::translate("DrawDialog", "MainWindow", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DrawDialog: public Ui_DrawDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRAWDIALOG_H
