#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QModelIndex>
#include <QLineEdit>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlRelationalTableModel>
#include "editstring.h"
#include "editnames.h"
#include "ui_editnames.h"
#include "db.h"
#include "string_delegate.h"


EditNames::EditNames(QString title, QString table, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditNames),
    m_table(table)
{
    ui->setupUi(this);

    setWindowTitle(title);
    QSqlRelationalTableModel* model = new QSqlRelationalTableModel(this, GetDb());
    model->setTable(m_table);
    model->setRelation(1, QSqlRelation("ui_strings", "id", "value"));
    //   model->setHeaderData(1, Qt::Horizontal, tr("name"));
    model->select();
    model->setHeaderData(1, Qt::Horizontal, tr("Name"));

    ui->m_material_type->addItem("Walls", "wall_materials");
    ui->m_material_type->addItem("Roofs", "roof_materials");

    {
        QSqlQueryModel* model = new QSqlQueryModel(this);
        QSqlQuery q(GetDb());
        q.prepare("SELECT materials.id, materials.name_id, ui_strings.value FROM materials, ui_strings WHERE ui_strings.id = materials.name_id");
        if (q.exec()) {
            qDebug("Fetched all materials");
            model->setQuery(q);
        } else {
            qDebug("Failed to fetch all materials");
        }
        ui->m_all_materials->setModel(model);
        ui->m_all_materials->hideColumn(0);
        ui->m_all_materials->hideColumn(1);
    }

}

EditNames::~EditNames()
{
    delete ui;
}

void EditNames::addMaterial() {
}

void EditNames::removeMaterial() {
}

void EditNames::editMaterial(QModelIndex index) {
}

void EditNames::setMaterialType(int index) {
    auto table_name = ui->m_material_type->itemData(index).toString();
    qDebug("Material table changed to %s", table_name.toStdString().c_str());
    m_table = table_name;
    QSqlQueryModel* model = new QSqlQueryModel(this);
    QSqlQuery q(GetDb());
    q.prepare("SELECT materials.id, materials.name_id, ui_strings.value FROM " + m_table + ", materials, ui_strings WHERE " + table_name + ".material_id=materials.id AND ui_strings.id = materials.name_id");
    if (q.exec()) {
        qDebug("Fetched all %s materials", m_table.toStdString().c_str());
        model->setQuery(q);
    } else {
        qDebug("Failed to fetch all %s materials", m_table.toStdString().c_str());
    }
}
