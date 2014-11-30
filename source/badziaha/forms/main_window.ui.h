/********************************************************************************
** Form generated from reading UI file 'main_window.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "city_widget.h"
#include "inventory_form.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSave;
    QAction *actionLoad;
    QAction *actionQuit;
    QAction *actionQuick_save;
    QAction *actionQuick_load;
    QAction *actionNew;
    QAction *actionEnter_location;
    QAction *actionLeave_location;
    QAction *action1_1;
    QAction *action1_10;
    QAction *action1_100;
    QAction *action1s_1000;
    QAction *actionCreate_character;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QGraphicsView *m_render_view;
    InventoryForm *m_inventory;
    CityWidget *m_city_widget;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuAction;
    QMenu *menuTime;
    QStatusBar *statusbar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QDateTimeEdit *m_time;
    QSlider *m_time_scale;
    QLabel *m_weather;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1024, 768);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionLoad = new QAction(MainWindow);
        actionLoad->setObjectName(QStringLiteral("actionLoad"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        actionQuick_save = new QAction(MainWindow);
        actionQuick_save->setObjectName(QStringLiteral("actionQuick_save"));
        actionQuick_load = new QAction(MainWindow);
        actionQuick_load->setObjectName(QStringLiteral("actionQuick_load"));
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionEnter_location = new QAction(MainWindow);
        actionEnter_location->setObjectName(QStringLiteral("actionEnter_location"));
        actionLeave_location = new QAction(MainWindow);
        actionLeave_location->setObjectName(QStringLiteral("actionLeave_location"));
        action1_1 = new QAction(MainWindow);
        action1_1->setObjectName(QStringLiteral("action1_1"));
        action1_10 = new QAction(MainWindow);
        action1_10->setObjectName(QStringLiteral("action1_10"));
        action1_100 = new QAction(MainWindow);
        action1_100->setObjectName(QStringLiteral("action1_100"));
        action1s_1000 = new QAction(MainWindow);
        action1s_1000->setObjectName(QStringLiteral("action1s_1000"));
        actionCreate_character = new QAction(MainWindow);
        actionCreate_character->setObjectName(QStringLiteral("actionCreate_character"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        m_render_view = new QGraphicsView(centralwidget);
        m_render_view->setObjectName(QStringLiteral("m_render_view"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(4);
        sizePolicy.setVerticalStretch(4);
        sizePolicy.setHeightForWidth(m_render_view->sizePolicy().hasHeightForWidth());
        m_render_view->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(m_render_view);

        m_inventory = new InventoryForm(centralwidget);
        m_inventory->setObjectName(QStringLiteral("m_inventory"));
        m_inventory->setMinimumSize(QSize(300, 0));

        horizontalLayout->addWidget(m_inventory);

        m_city_widget = new CityWidget(centralwidget);
        m_city_widget->setObjectName(QStringLiteral("m_city_widget"));
        m_city_widget->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(m_city_widget->sizePolicy().hasHeightForWidth());
        m_city_widget->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(m_city_widget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1024, 31));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuAction = new QMenu(menubar);
        menuAction->setObjectName(QStringLiteral("menuAction"));
        menuTime = new QMenu(menubar);
        menuTime->setObjectName(QStringLiteral("menuTime"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);
        dockWidget = new QDockWidget(MainWindow);
        dockWidget->setObjectName(QStringLiteral("dockWidget"));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        verticalLayout = new QVBoxLayout(dockWidgetContents);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));

        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        m_time = new QDateTimeEdit(dockWidgetContents);
        m_time->setObjectName(QStringLiteral("m_time"));

        horizontalLayout_4->addWidget(m_time);

        m_time_scale = new QSlider(dockWidgetContents);
        m_time_scale->setObjectName(QStringLiteral("m_time_scale"));
        m_time_scale->setMinimum(1);
        m_time_scale->setMaximum(1000);
        m_time_scale->setOrientation(Qt::Horizontal);
        m_time_scale->setTickPosition(QSlider::TicksBelow);

        horizontalLayout_4->addWidget(m_time_scale);


        verticalLayout->addLayout(horizontalLayout_4);

        m_weather = new QLabel(dockWidgetContents);
        m_weather->setObjectName(QStringLiteral("m_weather"));

        verticalLayout->addWidget(m_weather);

        dockWidget->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(4), dockWidget);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuAction->menuAction());
        menubar->addAction(menuTime->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionQuick_save);
        menuFile->addAction(actionQuick_load);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionLoad);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);
        menuAction->addAction(actionEnter_location);
        menuAction->addAction(actionLeave_location);
        menuAction->addAction(actionCreate_character);
        menuTime->addAction(action1_1);
        menuTime->addAction(action1_10);
        menuTime->addAction(action1_100);
        menuTime->addAction(action1s_1000);

        retranslateUi(MainWindow);
        QObject::connect(actionQuit, SIGNAL(triggered()), MainWindow, SLOT(close()));
        QObject::connect(actionQuick_save, SIGNAL(triggered()), MainWindow, SLOT(quickSave()));
        QObject::connect(actionQuick_load, SIGNAL(triggered()), MainWindow, SLOT(quickLoad()));
        QObject::connect(actionLoad, SIGNAL(triggered()), MainWindow, SLOT(load()));
        QObject::connect(actionSave, SIGNAL(triggered()), MainWindow, SLOT(save()));
        QObject::connect(actionNew, SIGNAL(triggered()), MainWindow, SLOT(newGame()));
        QObject::connect(actionEnter_location, SIGNAL(triggered()), MainWindow, SLOT(enterLocation()));
        QObject::connect(actionLeave_location, SIGNAL(triggered()), MainWindow, SLOT(leaveLocation()));
        QObject::connect(m_time_scale, SIGNAL(valueChanged(int)), MainWindow, SLOT(setTimeScale(int)));
        QObject::connect(actionCreate_character, SIGNAL(triggered()), MainWindow, SLOT(createCharacter()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Badziaha", 0));
        actionSave->setText(QApplication::translate("MainWindow", "Save", 0));
        actionLoad->setText(QApplication::translate("MainWindow", "Load", 0));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", 0));
        actionQuit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0));
        actionQuick_save->setText(QApplication::translate("MainWindow", "Quick save", 0));
        actionQuick_save->setShortcut(QApplication::translate("MainWindow", "F5", 0));
        actionQuick_load->setText(QApplication::translate("MainWindow", "Quick load", 0));
        actionQuick_load->setShortcut(QApplication::translate("MainWindow", "F9", 0));
        actionNew->setText(QApplication::translate("MainWindow", "New", 0));
        actionNew->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", 0));
        actionEnter_location->setText(QApplication::translate("MainWindow", "Enter location", 0));
        actionEnter_location->setShortcut(QApplication::translate("MainWindow", "Return", 0));
        actionLeave_location->setText(QApplication::translate("MainWindow", "Leave location", 0));
        actionLeave_location->setShortcut(QApplication::translate("MainWindow", "Esc", 0));
        action1_1->setText(QApplication::translate("MainWindow", "1s:1s", 0));
        action1_10->setText(QApplication::translate("MainWindow", "1s:10s", 0));
        action1_100->setText(QApplication::translate("MainWindow", "1s:100s", 0));
        action1s_1000->setText(QApplication::translate("MainWindow", "1s:1000s", 0));
        actionCreate_character->setText(QApplication::translate("MainWindow", "Create character", 0));
        actionCreate_character->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+C", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuAction->setTitle(QApplication::translate("MainWindow", "Action", 0));
        menuTime->setTitle(QApplication::translate("MainWindow", "Time", 0));
        dockWidget->setWindowTitle(QApplication::translate("MainWindow", "Time", 0));
        m_time->setDisplayFormat(QApplication::translate("MainWindow", "M/d/yyyy hh:mm:ss", 0));
        m_weather->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAIN_WINDOW_H
