/********************************************************************************
** Form generated from reading UI file 'records_window.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef RECORDS_WINDOW_H
#define RECORDS_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_RecordsWindow
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_5;
    QLabel *label_4;
    QLabel *label_3;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QLabel *m_easy;
    QLabel *m_easy_name;
    QLabel *m_easy_time;
    QLabel *m_easy_saves;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QLabel *m_medium_name;
    QLabel *m_medium_time;
    QLabel *m_medium_saves;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_8;
    QLabel *m_hard_name;
    QLabel *m_hard_time;
    QLabel *m_hard_saves;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_12;
    QLabel *m_hardcore_name;
    QLabel *m_hardcore_time;
    QLabel *m_hardcore_saves;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_ok_btn;

    void setupUi(QDialog *RecordsWindow)
    {
        if (RecordsWindow->objectName().isEmpty())
            RecordsWindow->setObjectName(QStringLiteral("RecordsWindow"));
        RecordsWindow->resize(591, 502);
        QIcon icon;
        icon.addFile(QStringLiteral(":/resources/icons/icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        RecordsWindow->setWindowIcon(icon);
        verticalLayout_2 = new QVBoxLayout(RecordsWindow);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_5 = new QLabel(RecordsWindow);
        label_5->setObjectName(QStringLiteral("label_5"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_5->setFont(font);

        horizontalLayout_6->addWidget(label_5);

        label_4 = new QLabel(RecordsWindow);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font);

        horizontalLayout_6->addWidget(label_4);

        label_3 = new QLabel(RecordsWindow);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font);

        horizontalLayout_6->addWidget(label_3);

        label = new QLabel(RecordsWindow);
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font);

        horizontalLayout_6->addWidget(label);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        m_easy = new QLabel(RecordsWindow);
        m_easy->setObjectName(QStringLiteral("m_easy"));

        horizontalLayout_2->addWidget(m_easy);

        m_easy_name = new QLabel(RecordsWindow);
        m_easy_name->setObjectName(QStringLiteral("m_easy_name"));

        horizontalLayout_2->addWidget(m_easy_name);

        m_easy_time = new QLabel(RecordsWindow);
        m_easy_time->setObjectName(QStringLiteral("m_easy_time"));

        horizontalLayout_2->addWidget(m_easy_time);

        m_easy_saves = new QLabel(RecordsWindow);
        m_easy_saves->setObjectName(QStringLiteral("m_easy_saves"));

        horizontalLayout_2->addWidget(m_easy_saves);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_2 = new QLabel(RecordsWindow);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_4->addWidget(label_2);

        m_medium_name = new QLabel(RecordsWindow);
        m_medium_name->setObjectName(QStringLiteral("m_medium_name"));

        horizontalLayout_4->addWidget(m_medium_name);

        m_medium_time = new QLabel(RecordsWindow);
        m_medium_time->setObjectName(QStringLiteral("m_medium_time"));

        horizontalLayout_4->addWidget(m_medium_time);

        m_medium_saves = new QLabel(RecordsWindow);
        m_medium_saves->setObjectName(QStringLiteral("m_medium_saves"));

        horizontalLayout_4->addWidget(m_medium_saves);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_8 = new QLabel(RecordsWindow);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_3->addWidget(label_8);

        m_hard_name = new QLabel(RecordsWindow);
        m_hard_name->setObjectName(QStringLiteral("m_hard_name"));

        horizontalLayout_3->addWidget(m_hard_name);

        m_hard_time = new QLabel(RecordsWindow);
        m_hard_time->setObjectName(QStringLiteral("m_hard_time"));

        horizontalLayout_3->addWidget(m_hard_time);

        m_hard_saves = new QLabel(RecordsWindow);
        m_hard_saves->setObjectName(QStringLiteral("m_hard_saves"));

        horizontalLayout_3->addWidget(m_hard_saves);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_12 = new QLabel(RecordsWindow);
        label_12->setObjectName(QStringLiteral("label_12"));

        horizontalLayout_5->addWidget(label_12);

        m_hardcore_name = new QLabel(RecordsWindow);
        m_hardcore_name->setObjectName(QStringLiteral("m_hardcore_name"));

        horizontalLayout_5->addWidget(m_hardcore_name);

        m_hardcore_time = new QLabel(RecordsWindow);
        m_hardcore_time->setObjectName(QStringLiteral("m_hardcore_time"));

        horizontalLayout_5->addWidget(m_hardcore_time);

        m_hardcore_saves = new QLabel(RecordsWindow);
        m_hardcore_saves->setObjectName(QStringLiteral("m_hardcore_saves"));

        horizontalLayout_5->addWidget(m_hardcore_saves);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        m_ok_btn = new QPushButton(RecordsWindow);
        m_ok_btn->setObjectName(QStringLiteral("m_ok_btn"));

        horizontalLayout->addWidget(m_ok_btn);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(RecordsWindow);
        QObject::connect(m_ok_btn, SIGNAL(clicked()), RecordsWindow, SLOT(accept()));

        QMetaObject::connectSlotsByName(RecordsWindow);
    } // setupUi

    void retranslateUi(QDialog *RecordsWindow)
    {
        RecordsWindow->setWindowTitle(QApplication::translate("RecordsWindow", "Table of records", 0));
        label_5->setText(QApplication::translate("RecordsWindow", "Level", 0));
        label_4->setText(QApplication::translate("RecordsWindow", "Name", 0));
        label_3->setText(QApplication::translate("RecordsWindow", "Time", 0));
        label->setText(QApplication::translate("RecordsWindow", "Saves", 0));
        m_easy->setText(QApplication::translate("RecordsWindow", "Easy:", 0));
        m_easy_name->setText(QApplication::translate("RecordsWindow", "[Name]", 0));
        m_easy_time->setText(QApplication::translate("RecordsWindow", "[Time]", 0));
        m_easy_saves->setText(QApplication::translate("RecordsWindow", "[Saves]", 0));
        label_2->setText(QApplication::translate("RecordsWindow", "Medium:", 0));
        m_medium_name->setText(QApplication::translate("RecordsWindow", "[Name]", 0));
        m_medium_time->setText(QApplication::translate("RecordsWindow", "[Time]", 0));
        m_medium_saves->setText(QApplication::translate("RecordsWindow", "[Saves]", 0));
        label_8->setText(QApplication::translate("RecordsWindow", "Hard:", 0));
        m_hard_name->setText(QApplication::translate("RecordsWindow", "[Name]", 0));
        m_hard_time->setText(QApplication::translate("RecordsWindow", "[Time]", 0));
        m_hard_saves->setText(QApplication::translate("RecordsWindow", "[Saves]", 0));
        label_12->setText(QApplication::translate("RecordsWindow", "Hardcore:", 0));
        m_hardcore_name->setText(QApplication::translate("RecordsWindow", "[Name]", 0));
        m_hardcore_time->setText(QApplication::translate("RecordsWindow", "[Time]", 0));
        m_hardcore_saves->setText(QApplication::translate("RecordsWindow", "[Saves]", 0));
        m_ok_btn->setText(QApplication::translate("RecordsWindow", "Ok", 0));
    } // retranslateUi

};

namespace Ui {
    class RecordsWindow: public Ui_RecordsWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // RECORDS_WINDOW_H
