/********************************************************************************
** Form generated from reading UI file 'qt_icollection_tab.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef QT_ICOLLECTION_TAB_H
#define QT_ICOLLECTION_TAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CollectionWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QListWidget *m_objects;

    void setupUi(QWidget *CollectionWidget)
    {
        if (CollectionWidget->objectName().isEmpty())
            CollectionWidget->setObjectName(QStringLiteral("CollectionWidget"));
        CollectionWidget->resize(802, 733);
        horizontalLayout = new QHBoxLayout(CollectionWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        m_objects = new QListWidget(CollectionWidget);
        m_objects->setObjectName(QStringLiteral("m_objects"));

        horizontalLayout->addWidget(m_objects);


        retranslateUi(CollectionWidget);
        QObject::connect(m_objects, SIGNAL(itemDoubleClicked(QListWidgetItem*)), CollectionWidget, SLOT(itemClicked(QListWidgetItem*)));

        QMetaObject::connectSlotsByName(CollectionWidget);
    } // setupUi

    void retranslateUi(QWidget *CollectionWidget)
    {
        CollectionWidget->setWindowTitle(QApplication::translate("CollectionWidget", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class CollectionWidget: public Ui_CollectionWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // QT_ICOLLECTION_TAB_H
