#ifndef EDITSTRING_H
#define EDITSTRING_H

#include <QDialog>

namespace Ui {
    class EditString;
}

class EditString : public QDialog
{
    Q_OBJECT

public:
    explicit EditString(int id, QString title, QWidget *parent = 0);
    ~EditString();

    void accept() override;

    int getId() { return m_id; }

private:
    Ui::EditString *ui;
    int m_id;
};

#endif // EDITSTRING_H
