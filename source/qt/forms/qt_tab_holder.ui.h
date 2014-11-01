/********************************************************************************
** Form generated from reading UI file 'qt_tab_holder.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef QT_TAB_HOLDER_H
#define QT_TAB_HOLDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtTabHolder
{
public:
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;

    void setupUi(QWidget *QtTabHolder)
    {
        if (QtTabHolder->objectName().isEmpty())
            QtTabHolder->setObjectName(QStringLiteral("QtTabHolder"));
        QtTabHolder->resize(902, 736);
        horizontalLayout = new QHBoxLayout(QtTabHolder);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tabWidget = new QTabWidget(QtTabHolder);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));

        horizontalLayout->addWidget(tabWidget);


        retranslateUi(QtTabHolder);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(QtTabHolder);
    } // setupUi

    void retranslateUi(QWidget *QtTabHolder)
    {
        QtTabHolder->setWindowTitle(QApplication::translate("QtTabHolder", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class QtTabHolder: public Ui_QtTabHolder {};
} // namespace Ui

QT_END_NAMESPACE

#endif // QT_TAB_HOLDER_H
