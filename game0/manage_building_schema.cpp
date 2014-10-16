#include <QMessageBox>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlRelationalTableModel>
#include <QSqlQuery>
#include "db.h"
#include "manage_building_schema.h"
#include "ui_manage_building_schema.h"

ManageBuildingSchema::ManageBuildingSchema(QWidget *parent, int schema_index) :
    QDialog(parent),
    ui(new Ui::ManageBuildingSchema)
{
    ui->setupUi(this);

    auto model = new QSqlQueryModel(this);
    model->setQuery("SELECT wall_materials.id, ui_strings.value, ui_strings.id FROM ui_strings, wall_materials WHERE wall_materials.name_id = ui_strings.id", GetDb());
    ui->m_wall_material->setModel(model);
    ui->m_wall_material->setModelColumn(1);

    model = new QSqlQueryModel(this);
    model->setQuery("SELECT roof_materials.id, ui_strings.value, ui_strings.id FROM ui_strings, roof_materials WHERE roof_materials.name_id = ui_strings.id", GetDb());
    ui->m_roof_material->setModel(model);
    ui->m_roof_material->setModelColumn(1);

    model = new QSqlQueryModel(this);
    model->setQuery("SELECT building_schemas.id, ui_strings.value, ui_strings.id FROM ui_strings, building_schemas WHERE building_schemas.name_id = ui_strings.id", GetDb());
    model->query();
    ui->m_schemas->setModel(model);
    ui->m_schemas->setModelColumn(1);
}

ManageBuildingSchema::~ManageBuildingSchema()
{
    delete ui;
}

void ManageBuildingSchema::setSchemaName(QString value) {
    if (m_current_schema) {
        m_current_schema->name()->setValue(value);
    }
}


void ManageBuildingSchema::setFloorsCount(QString value) {
    if (m_current_schema) {
        bool ok;
        int count = value.toInt(&ok);
        if (ok) {
            m_current_schema->setFloorsCount(count);
            ui->m_current_floor->clear();
            for (int i = 0; i < count; ++i) {
                ui->m_current_floor->addItem(QString::number(i));
            }
        }
    }
}

void ManageBuildingSchema::setExistingSchema(int index) {        
    if (index >= 0 && ui->m_edit_schema->isChecked()) {
        auto model = ui->m_schemas->model();
        bool ok;
        auto schema_index = model->data(model->index(index, 0)).toInt(&ok);
        if (ok) {
            emit schemaChanged(nullptr);
            qDebug("Found existed schema %d", schema_index);
            m_current_schema.reset(BuildingSchema::load(schema_index));
            emit schemaChanged(m_current_schema.get());
        } else {
            qDebug("No existed schema");
        }
    }
}

void ManageBuildingSchema::setExistingSchema() {
    auto row = ui->m_schemas->currentIndex();
    auto model = ui->m_schemas->model();
    bool ok;
    int schema_index = model->data(model->index(row, 0)).toInt(&ok);
    if (ok) {
        qDebug("Existing schema found %d", schema_index);
        emit schemaChanged(nullptr);
        m_current_schema.reset(BuildingSchema::load(schema_index));
        emit schemaChanged(m_current_schema.get());
    } else {
        qDebug("No existed schema found. Use new schema");
    }
}

void ManageBuildingSchema::setNewSchema() {    
    emit schemaChanged(nullptr);
    m_current_schema.reset(new BuildingSchema);
    qDebug("New schema created");
    emit schemaChanged(m_current_schema.get());
}

void ManageBuildingSchema::setCurrentSchema(BuildingSchema* schema) {
    if (m_current_schema.get() != schema)
        m_current_schema.reset(schema);
    if (!m_current_schema)
        return;

    ui->m_schema_name->setText(m_current_schema->name()->value());
    ui->m_floors->setText(QString::number(m_current_schema->floorsCount()));
    if (m_current_schema->wallMaterial()) {
        ui->m_wall_material->setCurrentText(m_current_schema->wallMaterial()->material()->name());
        ui->m_wall_material->setModelColumn(1);
    }
    if (m_current_schema->roofMaterial()) {
        ui->m_roof_material->setCurrentText(m_current_schema->roofMaterial()->material()->name());
        ui->m_roof_material->setModelColumn(1);
    }
    //    m_schema_index = schema;
    //    qDebug("Schema %d selected for editing", m_schema_index);
    //    QSqlQuery q(GetDb());
    //    q.prepare("SELECT floors_count FROM building_schemas WHERE id = :id");
    //    q.bindValue(":id", m_schema_index);
    //    if (q.exec()) {
    //        if (q.next()) {
    //            bool ok;
    //            int count = q.value(0).toInt(&ok);
    //            if (ok) {

    //            } else {
    //                qDebug("Failed to get floors count for schema %d", m_schema_index);
    //            }
    //        } else {
    //            qDebug("No data selected for schema %d when floor count", m_schema_index);
    //        }
    //    } else {
    //        qDebug("Failed to execute floors count select for schema %d", m_schema_index);
    //    }

    //    q.prepare("SELECT ui_strings.value FROM ui_strings, building_schemas, wall_materials WHERE wall_materials.id=building_schemas.walls_material_id AND ui_strings.id=wall_materials.name_id AND building_schemas.id = :id");
    //    q.bindValue(":id", m_schema_index);
    //    if (q.exec()) {
    //        if (q.next()) {
    //            auto value = q.value(0).toString();
    //            qDebug("Schema %d uses %s material for walls", m_schema_index, value.toStdString().c_str());
    //        } else {
    //            qDebug("No wall material selected for schema %d", m_schema_index);
    //        }
    //    } else {
    //        qDebug("Failed to get wall material for schema %d", m_schema_index);
    //    }

    //    q.prepare("SELECT ui_strings.value FROM ui_strings, building_schemas, roof_materials WHERE roof_materials.id=building_schemas.roof_material_id AND ui_strings.id=roof_materials.name_id AND building_schemas.id=:id");
    //    q.bindValue(":id", m_schema_index);
    //    if (q.exec()) {
    //        if (q.next()) {
    //            auto value = q.value(0).toString();
    //            qDebug("Schema %d uses %s material for roofs", m_schema_index, value.toStdString().c_str());
    //        } else {
    //            qDebug("No roof material selected for schema %d", m_schema_index);
    //        }
    //    } else {
    //        qDebug("Failed to get roof material for schema %d", m_schema_index);
    //    }
}

void ManageBuildingSchema::setWallsMaterial(int index) {
    if (m_current_schema) {
        auto model = ui->m_wall_material->model();
        bool ok;
        auto wall_id = model->index(index, 0).data().toInt(&ok);
        if (ok) {
            m_current_schema->setWallMaterial(wall_id);
        }
    }

    //        QSqlQuery q(GetDb());
    //        q.prepare("UPDATE building_schemas SET walls_material_id=:wall_id WHERE building_schemas.id = :id");
    //        q.bindValue(":wall_id", wall_id);
    //        q.bindValue(":id", m_schema_index);
    //        if (q.exec()) {
    //            qDebug("Wall material for schema %d changed to %d", m_schema_index, wall_id);
    //        } else {
    //            qDebug("Failed to update wall material for schema %d with %d", m_schema_index, wall_id);
    //        }
    //    } else {
    //        qDebug("Can't get wall material id");
    //    }
}

void ManageBuildingSchema::setRoofMaterial(int index) {
    if (m_current_schema) {
        auto model = ui->m_roof_material->model();
        bool ok;
        auto roof_id = model->index(index, 0).data().toInt(&ok);
        if (ok) {
            m_current_schema->setRoofMaterial(roof_id);
        }
    }
}/*
        QSqlQuery q(GetDb());
        q.prepare("UPDATE building_schemas SET roof_material_id=:roof_id WHERE building_schemas.id = :id");
        q.bindValue(":roof_id", roof_id);
        q.bindValue(":id", m_schema_index);
        if (q.exec()) {
            qDebug("Roof material for schema %d changed to %d", m_schema_index, roof_id);
        } else {
            qDebug("Failed to update roof material for schema %d with %d", m_schema_index, roof_id);
        }
    } else {
        qDebug("Can't get roof material id");
    }
}*/

void ManageBuildingSchema::commitChanges() {
    if (m_current_schema) {
        if (m_current_schema->name()->value().isEmpty()) {
            QMessageBox::critical(this, "Error", "Bad schema name");
            return;
        }
        //        if (!BuildingSchema::isUniqueName(m_current_schema->name()->value())) {
        //            QMessageBox::critical(this, "Error", "Schema name should be unique");
        //            return;
        //        }
        if (m_current_schema->floorsCount() <= 0) {
            QMessageBox::critical(this, "Error", "Schema should have at least one floor");
            return;
        }
        m_current_schema->save();
        close();
    }
    else {
        QMessageBox::critical(this, "Error", "Invalid schema");
    }
}

void ManageBuildingSchema::removeCurrentSchema() {
    if (m_current_schema) {
        emit setCurrentSchema(nullptr);
        m_current_schema->remove();
        m_current_schema.reset(nullptr);
    }
}
