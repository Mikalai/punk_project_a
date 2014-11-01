/********************************************************************************
** Form generated from reading UI file 'name_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef NAME_DIALOG_H
#define NAME_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_NameDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLineEdit *m_name;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *NameDialog)
    {
        if (NameDialog->objectName().isEmpty())
            NameDialog->setObjectName(QStringLiteral("NameDialog"));
        NameDialog->resize(400, 94);
        verticalLayout = new QVBoxLayout(NameDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        m_name = new QLineEdit(NameDialog);
        m_name->setObjectName(QStringLiteral("m_name"));

        verticalLayout->addWidget(m_name);

        buttonBox = new QDialogButtonBox(NameDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(NameDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), NameDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), NameDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(NameDialog);
    } // setupUi

    void retranslateUi(QDialog *NameDialog)
    {
        NameDialog->setWindowTitle(QApplication::translate("NameDialog", "Enter your name...", 0));
    } // retranslateUi

};

namespace Ui {
    class NameDialog: public Ui_NameDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // NAME_DIALOG_H
