/********************************************************************************
** Form generated from reading UI file 'custom_field.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef CUSTOM_FIELD_H
#define CUSTOM_FIELD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CustomField
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *m_width;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *m_height;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *m_mines;
    QSpacerItem *horizontalSpacer_3;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *CustomField)
    {
        if (CustomField->objectName().isEmpty())
            CustomField->setObjectName(QStringLiteral("CustomField"));
        CustomField->resize(312, 168);
        QIcon icon;
        icon.addFile(QStringLiteral(":/resources/icons/icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        CustomField->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(CustomField);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(CustomField);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label);

        m_width = new QLineEdit(CustomField);
        m_width->setObjectName(QStringLiteral("m_width"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(2);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_width->sizePolicy().hasHeightForWidth());
        m_width->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(m_width);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(CustomField);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(label_2);

        m_height = new QLineEdit(CustomField);
        m_height->setObjectName(QStringLiteral("m_height"));
        sizePolicy1.setHeightForWidth(m_height->sizePolicy().hasHeightForWidth());
        m_height->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(m_height);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(CustomField);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(label_3);

        m_mines = new QLineEdit(CustomField);
        m_mines->setObjectName(QStringLiteral("m_mines"));
        sizePolicy1.setHeightForWidth(m_mines->sizePolicy().hasHeightForWidth());
        m_mines->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(m_mines);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_3);

        buttonBox = new QDialogButtonBox(CustomField);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(CustomField);
        QObject::connect(buttonBox, SIGNAL(accepted()), CustomField, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), CustomField, SLOT(reject()));

        QMetaObject::connectSlotsByName(CustomField);
    } // setupUi

    void retranslateUi(QDialog *CustomField)
    {
        CustomField->setWindowTitle(QApplication::translate("CustomField", "Setup field...", 0));
        label->setText(QApplication::translate("CustomField", "Width:", 0));
        m_width->setText(QApplication::translate("CustomField", "9", 0));
        label_2->setText(QApplication::translate("CustomField", "Height:", 0));
        m_height->setText(QApplication::translate("CustomField", "9", 0));
        label_3->setText(QApplication::translate("CustomField", "Mines:", 0));
        m_mines->setText(QApplication::translate("CustomField", "10", 0));
    } // retranslateUi

};

namespace Ui {
    class CustomField: public Ui_CustomField {};
} // namespace Ui

QT_END_NAMESPACE

#endif // CUSTOM_FIELD_H
