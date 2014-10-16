#ifndef CHARACTERMANAGER_H
#define CHARACTERMANAGER_H

#include <QDialog>
#include <core/iobject.h>

namespace Ui {
    class CharacterManager;
}

class World;
class LocationWidget;

class CharacterManager : public QDialog
{
    Q_OBJECT

public:
    explicit CharacterManager(QWidget *parent = 0);
    ~CharacterManager();

public slots:

    void createCharacter();

private:
    Ui::CharacterManager *ui;
    std::vector<Punk::Engine::Core::IObject*> m_characters;
    World* m_world;
    LocationWidget* m_location = nullptr;
};

#endif // CHARACTERMANAGER_H
