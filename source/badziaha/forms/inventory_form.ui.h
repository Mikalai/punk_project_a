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
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InventoryForm
{
public:
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QTabWidget *m_tabs;
    QWidget *m_equipped_tab;
    QVBoxLayout *verticalLayout_4;
    QTreeView *m_equipped_view;
    QWidget *m_clothes_tab;
    QVBoxLayout *verticalLayout_2;
    QTreeView *m_clothes_view;
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
        m_equipped_tab = new QWidget();
        m_equipped_tab->setObjectName(QStringLiteral("m_equipped_tab"));
        verticalLayout_4 = new QVBoxLayout(m_equipped_tab);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        m_equipped_view = new QTreeView(m_equipped_tab);
        m_equipped_view->setObjectName(QStringLiteral("m_equipped_view"));
        m_equipped_view->setMouseTracking(true);
        m_equipped_view->setContextMenuPolicy(Qt::CustomContextMenu);
        m_equipped_view->setAcceptDrops(true);
        m_equipped_view->setMidLineWidth(1);
        m_equipped_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
        m_equipped_view->setDragEnabled(true);
        m_equipped_view->setDragDropMode(QAbstractItemView::DragDrop);
        m_equipped_view->setDefaultDropAction(Qt::MoveAction);
        m_equipped_view->setAlternatingRowColors(true);
        m_equipped_view->setSelectionBehavior(QAbstractItemView::SelectItems);
        m_equipped_view->setIconSize(QSize(64, 64));
        m_equipped_view->setTextElideMode(Qt::ElideMiddle);
        m_equipped_view->setIndentation(0);
        m_equipped_view->setRootIsDecorated(false);
        m_equipped_view->setItemsExpandable(false);
        m_equipped_view->setAllColumnsShowFocus(false);
        m_equipped_view->header()->setVisible(false);
        m_equipped_view->header()->setDefaultSectionSize(64);
        m_equipped_view->header()->setMinimumSectionSize(64);
        m_equipped_view->header()->setStretchLastSection(false);

        verticalLayout_4->addWidget(m_equipped_view);

        m_tabs->addTab(m_equipped_tab, QString());
        m_clothes_tab = new QWidget();
        m_clothes_tab->setObjectName(QStringLiteral("m_clothes_tab"));
        verticalLayout_2 = new QVBoxLayout(m_clothes_tab);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        m_clothes_view = new QTreeView(m_clothes_tab);
        m_clothes_view->setObjectName(QStringLiteral("m_clothes_view"));
        m_clothes_view->setContextMenuPolicy(Qt::CustomContextMenu);
        m_clothes_view->setAcceptDrops(true);
        m_clothes_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
        m_clothes_view->setDragEnabled(true);
        m_clothes_view->setDragDropMode(QAbstractItemView::DragDrop);
        m_clothes_view->setDefaultDropAction(Qt::MoveAction);
        m_clothes_view->setSelectionBehavior(QAbstractItemView::SelectItems);
        m_clothes_view->setIconSize(QSize(64, 64));
        m_clothes_view->setIndentation(0);
        m_clothes_view->setRootIsDecorated(false);
        m_clothes_view->setUniformRowHeights(false);
        m_clothes_view->setItemsExpandable(false);
        m_clothes_view->header()->setVisible(false);
        m_clothes_view->header()->setDefaultSectionSize(64);
        m_clothes_view->header()->setMinimumSectionSize(64);
        m_clothes_view->header()->setStretchLastSection(false);

        verticalLayout_2->addWidget(m_clothes_view);

        m_tabs->addTab(m_clothes_tab, QString());

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
        QObject::connect(m_equipped_view, SIGNAL(customContextMenuRequested(QPoint)), InventoryForm, SLOT(equippedCustomMenuRequested(QPoint)));
        QObject::connect(m_clothes_view, SIGNAL(customContextMenuRequested(QPoint)), InventoryForm, SLOT(customMenuRequested(QPoint)));

        m_tabs->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(InventoryForm);
    } // setupUi

    void retranslateUi(QWidget *InventoryForm)
    {
        InventoryForm->setWindowTitle(QApplication::translate("InventoryForm", "Form", 0));
        m_tabs->setTabText(m_tabs->indexOf(m_equipped_tab), QApplication::translate("InventoryForm", "Equiped", 0));
        m_tabs->setTabText(m_tabs->indexOf(m_clothes_tab), QApplication::translate("InventoryForm", "Inventory", 0));
        m_close->setText(QApplication::translate("InventoryForm", "Close", 0));
    } // retranslateUi

};

namespace Ui {
    class InventoryForm: public Ui_InventoryForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // INVENTORY_FORM_H
