#include <QVariant>
#include <QSqlQuery>
#include "db.h"
#include <memory>
#include "ui_text.h"

UiText::UiText()
{
}

UiText::~UiText() {
}

void UiText::remove(int id) {
    QSqlQuery q(GetDb());
    q.prepare("DELETE FROM ui_strings WHERE id=:id");
    q.bindValue(":id", id);
    if (q.exec()) {
        qDebug("Ui string %d has been removed from db", id);
    } else {
        qDebug("Failed to remove ui string %d in db", id);
    }
}

void UiText::remove() {
    QSqlQuery q(GetDb());
    q.prepare("DELETE FROM ui_strings WHERE id=:id");
    q.bindValue(":id", m_id);
    if (q.exec()) {
        qDebug("Ui string %d has been removed from db", m_id);
    } else {
        qDebug("Failed to remove ui string %d in db", m_id);
    }
    m_id = -1;
}

void UiText::removeTrash() {

}

UiText* UiText::load(int id) {
    std::unique_ptr<UiText> result{new UiText};
    QSqlQuery q(GetDb());
    q.prepare("SELECT value FROM ui_strings WHERE id=:id");
    q.bindValue(":id", id);
    if (q.exec()) {
        if (q.next()) {
            auto value = q.value(0).toString();            
            result->setValue(value);
            result->m_id = id;
            qDebug("ui string %s has been fetched from db", value.toStdString().c_str());            
        } else {
            qDebug("Faield to fetch ui string db at %d", id);
            return nullptr;
        }
    } else {
        qDebug("Faield to fetch ui string db at %d", id);
        return nullptr;
    }
    return result.release();
}

void UiText::save() {
    QSqlQuery q(GetDb());
    if (m_id == -1) {
        q.prepare("INSERT INTO ui_strings DEFAULT VALUES");
        if (q.exec()) {
            m_id = q.lastInsertId().toInt();
            qDebug("Temporary ui string %d has been added in db", m_id);
        } else {
            qDebug("Failed to add temporary ui string i db");
        }
    } else {
        q.prepare("UPDATE ui_strings SET value=:value WHERE id=:id");
        q.bindValue(":value", m_value);
        q.bindValue(":id", m_id);
        if (q.exec()) {
            qDebug("Ui string %s has been stored in db %d", m_value.toStdString().c_str(), m_id);
        } else {
            qDebug("Failed to save ui string %s in db %d", m_value.toStdString().c_str(), m_id);
        }
    }
}
