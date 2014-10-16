#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QLineEdit>
#include <QItemDelegate>
#include "edit_materials.h"
#include "ui_edit_materials.h"
#include "db.h"

class NameEditDelegate : public QSqlRelationalDelegate {
public:
    explicit NameEditDelegate(QObject *aParent = 0)
        : QSqlRelationalDelegate(aParent)
    {}

    QWidget *createEditor(QWidget *aParent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const
    {
        const QSqlRelationalTableModel *sqlModel = qobject_cast<const QSqlRelationalTableModel *>(index.model());
        QSqlTableModel *childModel = sqlModel ? sqlModel->relationModel(index.column()) : 0;
        if (!childModel)
            return QItemDelegate::createEditor(aParent, option, index);

        //childModel->fieldIndex()
        QLineEdit* line_edit = new QLineEdit(aParent);
        QSqlQuery q(GetDb());
        bool ok;
        int material_id = index.sibling(index.row(), 0).data().toInt(&ok);
        if (ok) {
            qDebug("Material id %d", material_id);
            q.prepare("SELECT ui_strings.value FROM ui_strings, materials WHERE ui_strings.id = materials.name_id AND materials.id = :id");
            q.bindValue(":id", material_id );
            if (q.exec()) {
                if (q.next()) {
                    line_edit->setText(q.value(0).toString());
                } else {
                    qDebug("No name associted with material %d", material_id);
                }
            } else {
                qDebug("Failed to select material name for %d", material_id);
            }
        }
        else {
            qDebug("Can't get material id");
        }
        line_edit->installEventFilter(const_cast<NameEditDelegate *>(this));

        return line_edit;
    }

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
    {
        if (!index.isValid())
            return;

        QSqlRelationalTableModel *sqlModel = qobject_cast<QSqlRelationalTableModel *>(model);
        QSqlTableModel *childModel = sqlModel ? sqlModel->relationModel(index.column()) : 0;
        QLineEdit *line_edit = qobject_cast<QLineEdit*>(editor);
        if (!sqlModel || !childModel || !line_edit) {
            QItemDelegate::setModelData(editor, model, index);
            return;
        }

        QSqlQuery q(GetDb());
        bool ok;
        int material_id = index.sibling(index.row(), 0).data(Qt::EditRole).toInt(&ok);
        QString material_name = line_edit->text();

        q.prepare("UPDATE ui_strings SET value=:value WHERE ui_strings.id IN ( SELECT materials.name_id FROM materials WHERE materials.id=:id)");
        q.bindValue(":value", material_name);
        q.bindValue(":id", material_id);
        if (q.exec()) {
            qDebug("Material %d name updated with %s", material_id, material_name.toStdString().c_str());
        } else {
            qDebug("Failed to update material %d name with %s", material_id, material_name.toStdString().c_str());
        }
        sqlModel->select();
    }
};

EditMaterials::EditMaterials(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditMaterials)
{
    ui->setupUi(this);

    QSqlRelationalTableModel* model = new QSqlRelationalTableModel(this, GetDb());
    model->setTable("materials");
    model->setRelation(1, QSqlRelation("ui_strings", "id", "value"));
    model->select();

    ui->m_materials->setModel(model);
    ui->m_materials->setItemDelegateForColumn(1, new NameEditDelegate(ui->m_materials));
    ui->m_materials->hideColumn(0);
}

EditMaterials::~EditMaterials()
{
    delete ui;
}

void EditMaterials::addMaterial() {
    m_current_material.reset(new Material);
    m_current_material->save();
    ((QSqlRelationalTableModel*)ui->m_materials->model())->select();
}

void EditMaterials::removeMaterial() {
    if (m_current_material.get()) {
        m_current_material->remove();
        m_current_material.reset(nullptr);
    }
    ((QSqlRelationalTableModel*)ui->m_materials->model())->select();
}

void EditMaterials::materialSelected(QModelIndex index) {
    int material_id = index.sibling(index.row(), 0).data().toInt();
    m_current_material.reset(Material::load(material_id));
    //((QSqlRelationalTableModel*)ui->m_materials->model())->select();
}
