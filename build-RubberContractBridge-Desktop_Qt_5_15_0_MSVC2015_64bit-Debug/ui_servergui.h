/********************************************************************************
** Form generated from reading UI file 'servergui.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVERGUI_H
#define UI_SERVERGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_serverGUI
{
public:

    void setupUi(QWidget *serverGUI)
    {
        if (serverGUI->objectName().isEmpty())
            serverGUI->setObjectName(QString::fromUtf8("serverGUI"));
        serverGUI->resize(400, 300);

        retranslateUi(serverGUI);

        QMetaObject::connectSlotsByName(serverGUI);
    } // setupUi

    void retranslateUi(QWidget *serverGUI)
    {
        serverGUI->setWindowTitle(QCoreApplication::translate("serverGUI", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class serverGUI: public Ui_serverGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVERGUI_H
