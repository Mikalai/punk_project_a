/********************************************************************************
** Form generated from reading UI file 'inventory_form.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef INVENTORY_FORM_H
#define INVENTORY_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InventoryForm
{
public:
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QTabWidget *m_tabs;
    QWidget *m_clothes_tab;
    QVBoxLayout *verticalLayout_2;
    QTableView *m_clothes_view;
    QWidget *m_weapons_tab;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_close;

    void setupUi(QWidget *InventoryForm)
    {
        if (InventoryForm->objectName().isEmpty())
            InventoryForm->setObjectName(QStringLiteral("InventoryForm"));
        InventoryForm->resize(430, 612);
        verticalLayout_3 = new QVBoxLayout(InventoryForm);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        m_tabs = new QTabWidget(InventoryForm);
        m_tabs->setObjectName(QStringLiteral("m_tabs"));
        m_tabs->setTabPosition(QTabWidget::West);
        m_clothes_tab = new QWidget();
        m_clothes_tab->setObjectName(QStringLiteral("m_clothes_tab"));
        verticalLayout_2 = new QVBoxLayout(m_clothes_tab);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        m_clothes_view = new QTableView(m_clothes_tab);
        m_clothes_view->setObjectName(QStringLiteral("m_clothes_view"));
        m_clothes_view->setAcceptDrops(true);
        m_clothes_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
        m_clothes_view->setDragEnabled(true);
        m_clothes_view->setDragDropMode(QAbstractItemView::DragDrop);
        m_clothes_view->setDefaultDropAction(Qt::MoveAction);
        m_clothes_view->setIconSize(QSize(64, 64));
        m_clothes_view->horizontalHeader()->setDefaultSectionSize(64);
        m_clothes_view->horizontalHeader()->setMinimumSectionSize(64);
        m_clothes_view->verticalHeader()->setDefaultSectionSize(64);
        m_clothes_view->verticalHeader()->setMinimumSectionSize(64);

        verticalLayout_2->addWidget(m_clothes_view);

        m_tabs->addTab(m_clothes_tab, QString());
        m_weapons_tab = new QWidget();
        m_weapons_tab->setObjectName(QStringLiteral("m_weapons_tab"));
        m_tabs->addTab(m_weapons_tab, QString());

        verticalLayout->addWidget(m_tabs);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        m_close = new QPushButton(InventoryForm);
        m_close->setObjectName(QStringLiteral("m_close"));

        horizontalLayout->addWidget(m_close);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_3->addLayout(verticalLayout);


        retranslateUi(InventoryForm);
        QObject::connect(m_close, SIGNAL(clicked()), InventoryForm, SLOT(hide()));

        m_tabs->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(InventoryForm);
    } // setupUi

    void retranslateUi(QWidget *InventoryForm)
    {
        InventoryForm->setWindowTitle(QApplication::translate("InventoryForm", "Form", 0));
        m_tabs->setTabText(m_tabs->indexOf(m_clothes_tab), QApplication::translate("InventoryForm", "Clothes", 0));
        m_tabs->setTabText(m_tabs->indexOf(m_weapons_tab), QApplication::translate("InventoryForm", "Weapons", 0));
        m_close->setText(QApplication::translate("InventoryForm", "Close", 0));
    } // retranslateUi

};

namespace Ui {
    class InventoryForm: public Ui_InventoryForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // INVENTORY_FORM_H
