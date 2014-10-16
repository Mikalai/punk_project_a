#ifndef EDIT_MATERIALS_H
#define EDIT_MATERIALS_H

#include <QDialog>
#include <QModelIndex>
#include "material.h"

namespace Ui {
    class EditMaterials;
}

class EditMaterials : public QDialog
{
    Q_OBJECT

public:
    explicit EditMaterials(QWidget *parent = 0);
    ~EditMaterials();

public slots:
    void addMaterial();
    void removeMaterial();
    void materialSelected(QModelIndex index);
private:
    Ui::EditMaterials *ui;
    std::unique_ptr<Material> m_current_material;
};

#endif // EDIT_MATERIALS_H
