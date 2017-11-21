/********************************************************************************
** Form generated from reading UI file 'formudp.ui'
**
** Created: Fri Apr 28 11:08:14 2017
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMUDP_H
#define UI_FORMUDP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormUdp
{
public:

    void setupUi(QWidget *FormUdp)
    {
        if (FormUdp->objectName().isEmpty())
            FormUdp->setObjectName(QString::fromUtf8("FormUdp"));
        FormUdp->resize(400, 300);

        retranslateUi(FormUdp);

        QMetaObject::connectSlotsByName(FormUdp);
    } // setupUi

    void retranslateUi(QWidget *FormUdp)
    {
        FormUdp->setWindowTitle(QApplication::translate("FormUdp", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FormUdp: public Ui_FormUdp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMUDP_H
