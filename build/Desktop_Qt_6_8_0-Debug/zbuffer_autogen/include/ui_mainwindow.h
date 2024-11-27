/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <zbuffer.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    zbuffer *labelZbuffer;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButtonRotateX;
    QPushButton *pushButtonRotateY;
    QPushButton *pushButtonRotatez;
    QCheckBox *autoRotate;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(680, 326);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        labelZbuffer = new zbuffer(centralwidget);
        labelZbuffer->setObjectName("labelZbuffer");
        labelZbuffer->setGeometry(QRect(10, 10, 451, 271));
        labelZbuffer->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(470, 10, 160, 92));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButtonRotateX = new QPushButton(verticalLayoutWidget);
        pushButtonRotateX->setObjectName("pushButtonRotateX");

        verticalLayout->addWidget(pushButtonRotateX);

        pushButtonRotateY = new QPushButton(verticalLayoutWidget);
        pushButtonRotateY->setObjectName("pushButtonRotateY");

        verticalLayout->addWidget(pushButtonRotateY);

        pushButtonRotatez = new QPushButton(verticalLayoutWidget);
        pushButtonRotatez->setObjectName("pushButtonRotatez");

        verticalLayout->addWidget(pushButtonRotatez);

        autoRotate = new QCheckBox(centralwidget);
        autoRotate->setObjectName("autoRotate");
        autoRotate->setGeometry(QRect(470, 110, 161, 24));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 680, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        labelZbuffer->setText(QString());
        pushButtonRotateX->setText(QCoreApplication::translate("MainWindow", "Rotacionar em X", nullptr));
        pushButtonRotateY->setText(QCoreApplication::translate("MainWindow", "Rotacionar em Y", nullptr));
        pushButtonRotatez->setText(QCoreApplication::translate("MainWindow", "Rotacionar em Z", nullptr));
        autoRotate->setText(QCoreApplication::translate("MainWindow", "Rotacionar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
