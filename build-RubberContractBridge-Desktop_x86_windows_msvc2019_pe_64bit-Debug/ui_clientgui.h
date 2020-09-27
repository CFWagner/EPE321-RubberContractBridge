/********************************************************************************
** Form generated from reading UI file 'clientgui.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENTGUI_H
#define UI_CLIENTGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_clientGUI
{
public:

    void setupUi(QWidget *clientGUI)
    {
        if (clientGUI->objectName().isEmpty())
            clientGUI->setObjectName(QString::fromUtf8("clientGUI"));
        clientGUI->resize(400, 300);

        retranslateUi(clientGUI);

        QMetaObject::connectSlotsByName(clientGUI);
    } // setupUi

    void retranslateUi(QWidget *clientGUI)
    {
        clientGUI->setWindowTitle(QCoreApplication::translate("clientGUI", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class clientGUI: public Ui_clientGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENTGUI_H
