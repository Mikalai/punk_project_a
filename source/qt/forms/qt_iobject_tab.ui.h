/********************************************************************************
** Form generated from reading UI file 'qt_iobject_tab.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef QT_IOBJECT_TAB_H
#define QT_IOBJECT_TAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IObjectTab
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLabel *m_address;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *IObjectTab)
    {
        if (IObjectTab->objectName().isEmpty())
            IObjectTab->setObjectName(QStringLiteral("IObjectTab"));
        IObjectTab->resize(549, 262);
        horizontalLayout = new QHBoxLayout(IObjectTab);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(IObjectTab);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        m_address = new QLabel(IObjectTab);
        m_address->setObjectName(QStringLiteral("m_address"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(m_address->sizePolicy().hasHeightForWidth());
        m_address->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(m_address);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(IObjectTab);

        QMetaObject::connectSlotsByName(IObjectTab);
    } // setupUi

    void retranslateUi(QWidget *IObjectTab)
    {
        IObjectTab->setWindowTitle(QApplication::translate("IObjectTab", "Form", 0));
        label_2->setText(QApplication::translate("IObjectTab", "Address:", 0));
        m_address->setText(QApplication::translate("IObjectTab", "[value]", 0));
    } // retranslateUi

};

namespace Ui {
    class IObjectTab: public Ui_IObjectTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // QT_IOBJECT_TAB_H
