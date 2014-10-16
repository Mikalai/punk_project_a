#ifndef MATERIAL_H
#define MATERIAL_H

#include <memory>
#include <QString>
#include "ui_text.h"

class Material
{
public:
    Material();
    ~Material();

    void save();
    void remove();

    void setName(QString value);
    QString name() const;

    int id() {
        return m_id;
    }

    static Material* load(int id);
    static void remove(int id);
    static void removeTrash();

private:
    int m_id{-1};
    std::unique_ptr<UiText> m_name;
};

#endif // MATERIAL_H
