/********************************************************************************
** Form generated from reading UI file 'city_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef CITY_WIDGET_H
#define CITY_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CityWidget
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *m_tabs;
    QWidget *tab_4;
    QVBoxLayout *verticalLayout_2;
    QLabel *m_name;
    QLabel *m_subordinated;
    QSpacerItem *verticalSpacer;
    QWidget *tab;
    QPushButton *m_build_saw_mill;
    QPushButton *m_road;
    QWidget *tab_2;
    QWidget *tab_3;

    void setupUi(QWidget *CityWidget)
    {
        if (CityWidget->objectName().isEmpty())
            CityWidget->setObjectName(QStringLiteral("CityWidget"));
        CityWidget->resize(306, 619);
        verticalLayout = new QVBoxLayout(CityWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        m_tabs = new QTabWidget(CityWidget);
        m_tabs->setObjectName(QStringLiteral("m_tabs"));
        m_tabs->setTabPosition(QTabWidget::West);
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        verticalLayout_2 = new QVBoxLayout(tab_4);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        m_name = new QLabel(tab_4);
        m_name->setObjectName(QStringLiteral("m_name"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_name->sizePolicy().hasHeightForWidth());
        m_name->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setUnderline(true);
        font.setWeight(75);
        font.setKerning(true);
        m_name->setFont(font);
        m_name->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(m_name);

        m_subordinated = new QLabel(tab_4);
        m_subordinated->setObjectName(QStringLiteral("m_subordinated"));
        m_subordinated->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(m_subordinated);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        m_tabs->addTab(tab_4, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        m_build_saw_mill = new QPushButton(tab);
        m_build_saw_mill->setObjectName(QStringLiteral("m_build_saw_mill"));
        m_build_saw_mill->setGeometry(QRect(0, 20, 64, 64));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/saw.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_build_saw_mill->setIcon(icon);
        m_build_saw_mill->setIconSize(QSize(64, 64));
        m_road = new QPushButton(tab);
        m_road->setObjectName(QStringLiteral("m_road"));
        m_road->setGeometry(QRect(60, 20, 64, 64));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/road_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_road->setIcon(icon1);
        m_road->setIconSize(QSize(64, 64));
        m_tabs->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        m_tabs->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        m_tabs->addTab(tab_3, QString());

        verticalLayout->addWidget(m_tabs);


        retranslateUi(CityWidget);
        QObject::connect(m_road, SIGNAL(clicked()), CityWidget, SLOT(buildRoad()));
        QObject::connect(m_build_saw_mill, SIGNAL(clicked()), CityWidget, SLOT(buildSawmill()));

        m_tabs->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(CityWidget);
    } // setupUi

    void retranslateUi(QWidget *CityWidget)
    {
        CityWidget->setWindowTitle(QApplication::translate("CityWidget", "Form", 0));
        m_name->setText(QApplication::translate("CityWidget", "[Name]", 0));
        m_subordinated->setText(QApplication::translate("CityWidget", "[Subordinated]", 0));
        m_tabs->setTabText(m_tabs->indexOf(tab_4), QApplication::translate("CityWidget", "Overview", 0));
#ifndef QT_NO_TOOLTIP
        m_build_saw_mill->setToolTip(QApplication::translate("CityWidget", "Build sawmill", 0));
#endif // QT_NO_TOOLTIP
        m_build_saw_mill->setText(QString());
#ifndef QT_NO_TOOLTIP
        m_road->setToolTip(QApplication::translate("CityWidget", "Build road", 0));
#endif // QT_NO_TOOLTIP
        m_road->setText(QString());
        m_tabs->setTabText(m_tabs->indexOf(tab), QApplication::translate("CityWidget", "Expanding", 0));
        m_tabs->setTabText(m_tabs->indexOf(tab_2), QApplication::translate("CityWidget", "Training", 0));
        m_tabs->setTabText(m_tabs->indexOf(tab_3), QApplication::translate("CityWidget", "Managment", 0));
    } // retranslateUi

};

namespace Ui {
    class CityWidget: public Ui_CityWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // CITY_WIDGET_H
