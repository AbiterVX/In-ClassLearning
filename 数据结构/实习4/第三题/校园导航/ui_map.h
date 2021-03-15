/********************************************************************************
** Form generated from reading UI file 'map.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAP_H
#define UI_MAP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include <view.h>

QT_BEGIN_NAMESPACE

class Ui_Map
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    View *graphicsView;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QDockWidget *dockWidget_3;
    QWidget *dockWidgetContents_3;
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QLabel *label_2;
    QComboBox *comboBox;
    QLabel *label;
    QComboBox *comboBox_2;
    QPushButton *pushButton;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QLabel *label_3;
    QTextEdit *textEdit;

    void setupUi(QMainWindow *Map)
    {
        if (Map->objectName().isEmpty())
            Map->setObjectName(QStringLiteral("Map"));
        Map->resize(1288, 745);
        centralwidget = new QWidget(Map);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        graphicsView = new View(centralwidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        gridLayout->addWidget(graphicsView, 0, 0, 1, 1);

        Map->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Map);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1288, 26));
        Map->setMenuBar(menubar);
        statusbar = new QStatusBar(Map);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        Map->setStatusBar(statusbar);
        dockWidget_3 = new QDockWidget(Map);
        dockWidget_3->setObjectName(QStringLiteral("dockWidget_3"));
        dockWidgetContents_3 = new QWidget();
        dockWidgetContents_3->setObjectName(QStringLiteral("dockWidgetContents_3"));
        gridLayout_2 = new QGridLayout(dockWidgetContents_3);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        groupBox = new QGroupBox(dockWidgetContents_3);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_3->addWidget(label_2, 0, 0, 1, 1);

        comboBox = new QComboBox(groupBox);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        gridLayout_3->addWidget(comboBox, 0, 1, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_3->addWidget(label, 1, 0, 1, 1);

        comboBox_2 = new QComboBox(groupBox);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));

        gridLayout_3->addWidget(comboBox_2, 1, 1, 1, 1);

        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout_3->addWidget(pushButton, 2, 0, 1, 2);

        checkBox = new QCheckBox(groupBox);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        gridLayout_3->addWidget(checkBox, 3, 0, 1, 2);

        checkBox_2 = new QCheckBox(groupBox);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));

        gridLayout_3->addWidget(checkBox_2, 4, 0, 1, 2);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_3->addWidget(label_3, 5, 0, 1, 2);

        textEdit = new QTextEdit(groupBox);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        gridLayout_3->addWidget(textEdit, 6, 0, 1, 2);


        gridLayout_2->addWidget(groupBox, 0, 0, 1, 1);

        dockWidget_3->setWidget(dockWidgetContents_3);
        Map->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget_3);

        retranslateUi(Map);

        QMetaObject::connectSlotsByName(Map);
    } // setupUi

    void retranslateUi(QMainWindow *Map)
    {
        Map->setWindowTitle(QApplication::translate("Map", "\345\234\260\345\244\247\346\240\241\345\233\255\345\257\274\350\210\252", Q_NULLPTR));
        groupBox->setTitle(QString());
        label_2->setText(QApplication::translate("Map", "\347\273\210\347\202\271\357\274\232", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("Map", "\350\245\277\345\214\272\345\244\247\351\227\250", Q_NULLPTR)
         << QApplication::translate("Map", "\346\225\231\344\272\214\346\245\274", Q_NULLPTR)
         << QApplication::translate("Map", "\346\225\231\344\270\211\346\245\274", Q_NULLPTR)
         << QApplication::translate("Map", "\345\255\246\344\270\200\351\243\237\345\240\202", Q_NULLPTR)
         << QApplication::translate("Map", "\345\255\246\344\270\211\351\243\237\345\240\202", Q_NULLPTR)
         << QApplication::translate("Map", "52\346\240\213", Q_NULLPTR)
         << QApplication::translate("Map", "\344\270\273\346\245\274", Q_NULLPTR)
         << QApplication::translate("Map", "\344\277\241\346\201\257\346\245\274", Q_NULLPTR)
         << QApplication::translate("Map", "\345\233\276\344\271\246\351\246\206", Q_NULLPTR)
         << QApplication::translate("Map", "\345\274\230\346\257\205\345\240\202", Q_NULLPTR)
         << QApplication::translate("Map", "\344\275\223\350\202\262\351\246\206", Q_NULLPTR)
         << QApplication::translate("Map", "\345\214\273\351\231\242", Q_NULLPTR)
         << QApplication::translate("Map", "\345\244\247\346\264\273", Q_NULLPTR)
        );
        label->setText(QApplication::translate("Map", "\350\265\267\347\202\271\357\274\232", Q_NULLPTR));
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("Map", "\350\245\277\345\214\272\345\244\247\351\227\250", Q_NULLPTR)
         << QApplication::translate("Map", "\346\225\231\344\272\214\346\245\274", Q_NULLPTR)
         << QApplication::translate("Map", "\346\225\231\344\270\211\346\245\274", Q_NULLPTR)
         << QApplication::translate("Map", "\345\255\246\344\270\200\351\243\237\345\240\202", Q_NULLPTR)
         << QApplication::translate("Map", "\345\255\246\344\270\211\351\243\237\345\240\202", Q_NULLPTR)
         << QApplication::translate("Map", "52\346\240\213", Q_NULLPTR)
         << QApplication::translate("Map", "\344\270\273\346\245\274", Q_NULLPTR)
         << QApplication::translate("Map", "\344\277\241\346\201\257\346\245\274", Q_NULLPTR)
         << QApplication::translate("Map", "\345\233\276\344\271\246\351\246\206", Q_NULLPTR)
         << QApplication::translate("Map", "\345\274\230\346\257\205\345\240\202", Q_NULLPTR)
         << QApplication::translate("Map", "\344\275\223\350\202\262\351\246\206", Q_NULLPTR)
         << QApplication::translate("Map", "\345\214\273\351\231\242", Q_NULLPTR)
         << QApplication::translate("Map", "\345\244\247\346\264\273", Q_NULLPTR)
        );
        pushButton->setText(QApplication::translate("Map", "\346\220\234\347\264\242\350\267\257\345\276\204", Q_NULLPTR));
        checkBox->setText(QApplication::translate("Map", "\346\230\276\347\244\272\345\205\250\351\203\250\350\267\257\347\272\277", Q_NULLPTR));
        checkBox_2->setText(QApplication::translate("Map", "\346\230\276\347\244\272\345\273\272\347\255\221", Q_NULLPTR));
        label_3->setText(QApplication::translate("Map", "\350\257\246\347\273\206\344\277\241\346\201\257\357\274\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Map: public Ui_Map {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAP_H
