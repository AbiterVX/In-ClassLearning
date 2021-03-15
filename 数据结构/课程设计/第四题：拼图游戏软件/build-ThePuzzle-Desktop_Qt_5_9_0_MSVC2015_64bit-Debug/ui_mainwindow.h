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
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "view.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    View *graphicsView;
    QMenuBar *menubar;
    QMenu *menu;
    QStatusBar *statusbar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QFormLayout *formLayout;
    QLabel *label;
    QGraphicsView *graphicsView_2;
    QLabel *label_2;
    QComboBox *comboBox;
    QPushButton *pushButton;
    QSpacerItem *verticalSpacer;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1302, 765);
        action = new QAction(MainWindow);
        action->setObjectName(QStringLiteral("action"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        graphicsView = new View(centralwidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        gridLayout->addWidget(graphicsView, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1302, 26));
        menu = new QMenu(menubar);
        menu->setObjectName(QStringLiteral("menu"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);
        dockWidget = new QDockWidget(MainWindow);
        dockWidget->setObjectName(QStringLiteral("dockWidget"));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        formLayout = new QFormLayout(dockWidgetContents);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label = new QLabel(dockWidgetContents);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        graphicsView_2 = new QGraphicsView(dockWidgetContents);
        graphicsView_2->setObjectName(QStringLiteral("graphicsView_2"));

        formLayout->setWidget(1, QFormLayout::SpanningRole, graphicsView_2);

        label_2 = new QLabel(dockWidgetContents);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_2);

        comboBox = new QComboBox(dockWidgetContents);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        formLayout->setWidget(2, QFormLayout::FieldRole, comboBox);

        pushButton = new QPushButton(dockWidgetContents);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        formLayout->setWidget(3, QFormLayout::LabelRole, pushButton);

        verticalSpacer = new QSpacerItem(177, 228, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(4, QFormLayout::FieldRole, verticalSpacer);

        dockWidget->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget);

        menubar->addAction(menu->menuAction());
        menu->addAction(action);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\345\274\200\345\247\213\346\270\270\346\210\217", Q_NULLPTR));
        action->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\345\233\276\347\211\207", Q_NULLPTR));
        menu->setTitle(QApplication::translate("MainWindow", "\351\200\211\346\213\251\345\233\276\347\211\207", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\345\217\202\350\200\203\345\233\276\347\211\207\357\274\232", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "\346\213\274\345\233\276\345\235\227\346\225\260\357\274\232", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "9", Q_NULLPTR)
         << QApplication::translate("MainWindow", "16", Q_NULLPTR)
        );
        pushButton->setText(QApplication::translate("MainWindow", "\350\207\252\345\212\250\345\257\273\350\267\257", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
