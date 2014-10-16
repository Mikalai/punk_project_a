#ifndef NAME_H
#define NAME_H

#include <QString>

class UiText
{
public:
    UiText();
    ~UiText();

    void save();
    void remove();

    void setValue(QString value) {
        m_value = value;
    }

    const QString& value() const {
        return m_value;
    }

    int id() const {
        return m_id;
    }

    static UiText* load(int id);
    static void remove(int id);
    static void removeTrash();

private:
    int m_id{-1};
    QString m_value;
};

#endif // NAME_H
