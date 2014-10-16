#ifndef EDITWALLMATERIALS_H
#define EDITWALLMATERIALS_H

#include <QDialog>
#include <QModelIndex>
namespace Ui {
    class EditNames;
}

class EditNames : public QDialog
{
    Q_OBJECT

public:
    explicit EditNames(QString title, QString table, QWidget *parent = 0);
    ~EditNames();

public slots:
    void editMaterial(QModelIndex index);
    void addMaterial();
    void removeMaterial();
    void setMaterialType(int index);

private:
    Ui::EditNames*ui;
    QString m_table;
};

#endif // EDITWALLMATERIALS_H
