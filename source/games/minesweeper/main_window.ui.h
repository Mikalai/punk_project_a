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
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuit;
    QAction *actionAbout;
    QAction *actionSave;
    QAction *actionLoad;
    QAction *actionEasy;
    QAction *actionMedium;
    QAction *actionHard;
    QAction *actionHardcore;
    QAction *actionCustom;
    QAction *actionRecords;
    QAction *actionAbout_Qt;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLCDNumber *m_mines_left;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_start_btn;
    QSpacerItem *horizontalSpacer_2;
    QLCDNumber *m_time;
    QGraphicsView *m_field_view;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QMenu *menuMode;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        QIcon icon;
        icon.addFile(QStringLiteral(":/resources/icons/icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionLoad = new QAction(MainWindow);
        actionLoad->setObjectName(QStringLiteral("actionLoad"));
        actionEasy = new QAction(MainWindow);
        actionEasy->setObjectName(QStringLiteral("actionEasy"));
        actionMedium = new QAction(MainWindow);
        actionMedium->setObjectName(QStringLiteral("actionMedium"));
        actionHard = new QAction(MainWindow);
        actionHard->setObjectName(QStringLiteral("actionHard"));
        actionHardcore = new QAction(MainWindow);
        actionHardcore->setObjectName(QStringLiteral("actionHardcore"));
        actionCustom = new QAction(MainWindow);
        actionCustom->setObjectName(QStringLiteral("actionCustom"));
        actionRecords = new QAction(MainWindow);
        actionRecords->setObjectName(QStringLiteral("actionRecords"));
        actionAbout_Qt = new QAction(MainWindow);
        actionAbout_Qt->setObjectName(QStringLiteral("actionAbout_Qt"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        m_mines_left = new QLCDNumber(centralwidget);
        m_mines_left->setObjectName(QStringLiteral("m_mines_left"));
        m_mines_left->setDigitCount(7);
        m_mines_left->setSegmentStyle(QLCDNumber::Flat);

        horizontalLayout->addWidget(m_mines_left);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        m_start_btn = new QPushButton(centralwidget);
        m_start_btn->setObjectName(QStringLiteral("m_start_btn"));
        m_start_btn->setMinimumSize(QSize(64, 64));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/resources/icons/head.ico"), QSize(), QIcon::Normal, QIcon::Off);
        m_start_btn->setIcon(icon1);
        m_start_btn->setIconSize(QSize(64, 64));

        horizontalLayout->addWidget(m_start_btn);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        m_time = new QLCDNumber(centralwidget);
        m_time->setObjectName(QStringLiteral("m_time"));
        m_time->setDigitCount(7);
        m_time->setSegmentStyle(QLCDNumber::Flat);
        m_time->setProperty("intValue", QVariant(0));

        horizontalLayout->addWidget(m_time);


        verticalLayout->addLayout(horizontalLayout);

        m_field_view = new QGraphicsView(centralwidget);
        m_field_view->setObjectName(QStringLiteral("m_field_view"));
        m_field_view->setMouseTracking(true);
        QBrush brush(QColor(149, 149, 149, 255));
        brush.setStyle(Qt::SolidPattern);
        m_field_view->setBackgroundBrush(brush);

        verticalLayout->addWidget(m_field_view);


        verticalLayout_2->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 31));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuMode = new QMenu(menubar);
        menuMode->setObjectName(QStringLiteral("menuMode"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuMode->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionRecords);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionLoad);
        menuFile->addAction(actionQuit);
        menuHelp->addAction(actionAbout_Qt);
        menuMode->addAction(actionEasy);
        menuMode->addAction(actionMedium);
        menuMode->addAction(actionHard);
        menuMode->addAction(actionHardcore);
        menuMode->addSeparator();
        menuMode->addAction(actionCustom);

        retranslateUi(MainWindow);
        QObject::connect(actionSave, SIGNAL(triggered()), MainWindow, SLOT(save()));
        QObject::connect(actionLoad, SIGNAL(triggered()), MainWindow, SLOT(load()));
        QObject::connect(m_start_btn, SIGNAL(clicked()), MainWindow, SLOT(reset()));
        QObject::connect(actionQuit, SIGNAL(triggered()), MainWindow, SLOT(close()));
        QObject::connect(actionEasy, SIGNAL(triggered()), MainWindow, SLOT(setEasy()));
        QObject::connect(actionMedium, SIGNAL(triggered()), MainWindow, SLOT(setMedium()));
        QObject::connect(actionHard, SIGNAL(triggered()), MainWindow, SLOT(setHard()));
        QObject::connect(actionHardcore, SIGNAL(triggered()), MainWindow, SLOT(setHardcore()));
        QObject::connect(actionCustom, SIGNAL(triggered()), MainWindow, SLOT(setCustom()));
        QObject::connect(actionRecords, SIGNAL(triggered()), MainWindow, SLOT(showRecords()));
        QObject::connect(actionAbout_Qt, SIGNAL(triggered()), MainWindow, SLOT(showAboutQt()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Minesweeper", 0));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", 0));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0));
        actionSave->setText(QApplication::translate("MainWindow", "Save", 0));
        actionLoad->setText(QApplication::translate("MainWindow", "Load", 0));
        actionEasy->setText(QApplication::translate("MainWindow", "Easy", 0));
        actionMedium->setText(QApplication::translate("MainWindow", "Medium", 0));
        actionHard->setText(QApplication::translate("MainWindow", "Hard", 0));
        actionHardcore->setText(QApplication::translate("MainWindow", "Hardcore", 0));
        actionCustom->setText(QApplication::translate("MainWindow", "Custom", 0));
        actionRecords->setText(QApplication::translate("MainWindow", "Records", 0));
        actionAbout_Qt->setText(QApplication::translate("MainWindow", "About Qt", 0));
        m_start_btn->setText(QString());
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0));
        menuMode->setTitle(QApplication::translate("MainWindow", "Mode", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAIN_WINDOW_H
