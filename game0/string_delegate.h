#ifndef STRING_DELEGATE_H
#define STRING_DELEGATE_H

#include <QSqlRelationalDelegate>
#include <QSqlQuery>
#include "db.h"

class QCustomSqlRelationalDelegate: public QItemDelegate
{
public:

    explicit QCustomSqlRelationalDelegate(QString table_name, QObject *aParent = 0)
        : QItemDelegate(aParent)
        , m_table(table_name)
    {}

    ~QCustomSqlRelationalDelegate()
    {}

    QWidget *createEditor(QWidget *aParent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const
    {
        const QSqlRelationalTableModel *sqlModel = qobject_cast<const QSqlRelationalTableModel *>(index.model());
        QSqlTableModel *childModel = sqlModel ? sqlModel->relationModel(index.column()) : 0;
        if (!childModel)
            return QItemDelegate::createEditor(aParent, option, index);

        if (index.column() == 1) {
            int string_id = -1;
            {
                QSqlQuery q(GetDb());
                q.prepare("SELECT name_id FROM " + m_table + " WHERE id = :id");
                //q.bindValue(":table", m_table);
                q.bindValue(":id", index.sibling(index.row(), 0).data());
                if (q.exec()) {
                    if (q.next()) {
                        string_id = q.value(0).toInt();
                    }
                }
            }
            QLineEdit* edit = new QLineEdit(aParent);
            if (string_id > 0) {
                QModelIndex i = index.sibling(index.row(), 1);

                QSqlQuery q(GetDb());
                q.prepare("SELECT value FROM ui_strings WHERE id = :id");
                q.bindValue(":id", string_id);
                if (q.exec()) {
                    while (q.next()) {
                        QString value = q.value(0).toString();
                        edit->setText(value);
                    }
                }

                edit->installEventFilter(const_cast<QCustomSqlRelationalDelegate *>(this));

            }
            return edit;
        }
    }

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
    {
        if (!index.isValid())
            return;

        QSqlRelationalTableModel *sqlModel = qobject_cast<QSqlRelationalTableModel *>(model);
        QSqlTableModel *childModel = sqlModel ? sqlModel->relationModel(index.column()) : 0;

        QLineEdit *edit = qobject_cast<QLineEdit *>(editor);
        if (!sqlModel || !childModel || !edit) {
            QItemDelegate::setModelData(editor, model, index);
            return;
        }
        if (index.column() == 1) {
            QString value = edit->text();
            int string_id = -1;
            {
                QSqlQuery q(GetDb());
                q.prepare("SELECT name_id FROM " + m_table + " WHERE id = :id");
                q.bindValue(":id", index.sibling(index.row(), 0).data());
                if (q.exec()) {
                    if (q.next()) {
                        string_id = q.value(0).toInt();
                    }
                }
            }

            if (string_id > 0) {
                QSqlQuery q(GetDb());
                q.prepare("UPDATE ui_strings SET value = :value WHERE id = :id");
                q.bindValue(":id", string_id);
                q.bindValue(":value",
                            value);
                q.exec();
                sqlModel->select();
            }
        }
    }

    QString m_table;
};

#endif // STRING_DELEGATE_H
