/********************************************************************************
** Form generated from reading UI file 'cover.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COVER_H
#define UI_COVER_H

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
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Cover
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QLabel *label;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Cover)
    {
        if (Cover->objectName().isEmpty())
            Cover->setObjectName(QStringLiteral("Cover"));
        Cover->resize(675, 406);
        centralWidget = new QWidget(Cover);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(550, 280, 91, 51));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 0, 671, 341));
        label->setPixmap(QPixmap(QString::fromUtf8("../build-ThePuzzle-Desktop_Qt_5_9_0_MSVC2015_64bit-Debug/2.jpg")));
        Cover->setCentralWidget(centralWidget);
        label->raise();
        pushButton->raise();
        menuBar = new QMenuBar(Cover);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 675, 26));
        Cover->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Cover);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Cover->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Cover);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Cover->setStatusBar(statusBar);

        retranslateUi(Cover);

        QMetaObject::connectSlotsByName(Cover);
    } // setupUi

    void retranslateUi(QMainWindow *Cover)
    {
        Cover->setWindowTitle(QApplication::translate("Cover", "Puzzle", Q_NULLPTR));
        pushButton->setText(QApplication::translate("Cover", "\345\274\200\345\247\213\346\270\270\346\210\217", Q_NULLPTR));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Cover: public Ui_Cover {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COVER_H
