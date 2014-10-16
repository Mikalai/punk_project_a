#ifndef CREATE_BUILDING_SCHEMA_H
#define CREATE_BUILDING_SCHEMA_H

#include <QDialog>
#include "building_schema.h"

namespace Ui {
    class ManageBuildingSchema;
}

class ManageBuildingSchema : public QDialog
{
    Q_OBJECT

public:
    explicit ManageBuildingSchema(QWidget *parent = 0, int schema_index = -1);
    ~ManageBuildingSchema();

signals:
    void schemaChanged(BuildingSchema*);

public slots:
    void setSchemaName(QString value);
    void setFloorsCount(QString value);
    void setExistingSchema(int index);
    void setExistingSchema();
    void setNewSchema();
    void setCurrentSchema(BuildingSchema* schema);
    void setWallsMaterial(int index);
    void setRoofMaterial(int index);
    void commitChanges();
    void removeCurrentSchema();
private:

    Ui::ManageBuildingSchema *ui;
    std::unique_ptr<BuildingSchema> m_current_schema;
    int m_schema_index{-1};
    int m_schema_name_index{-1};

};

#endif // CREATE_BUILDING_SCHEMA_H
