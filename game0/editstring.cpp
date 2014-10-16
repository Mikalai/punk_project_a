#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQuery>
#include "editstring.h"
#include "ui_editstring.h"
#include "db.h"

EditString::EditString(int id, QString title, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditString),
    m_id(id)
{
    ui->setupUi(this);
    setWindowTitle(title);

    if (id != -1) {
        QSqlQuery q(GetDb());
        q.prepare("SELECT value FROM ui_strings WHERE id = :id");
        q.bindValue(":id", m_id);
        if (q.exec()) {
            while (q.next()) {
                QString value = q.value(0).toString();
                ui->m_string->setText(value);
            }
        }
    }
}

void EditString::accept() {
    if (m_id == -1)
    {
        QString value = ui->m_string->text();
        QSqlQuery q(GetDb());
        q.prepare("INSERT INTO ui_strings (value) VALUES (:value)");
        q.bindValue(":value", value);
        q.exec();
        m_id = q.lastInsertId().toInt();
    }
    else
    {
        QString value = ui->m_string->text();

        QSqlQuery q(GetDb());
        q.prepare("UPDATE ui_strings SET value = :value WHERE id = :id");
        q.bindValue(":id", m_id);
        q.bindValue(":value", value);
        q.exec();
    }
    close();
}

EditString::~EditString()
{
    delete ui;
}
