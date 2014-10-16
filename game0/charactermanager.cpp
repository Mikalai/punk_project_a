#include <interfaces/character.h>
#include <QGraphicsItem>
#include "charactermanager.h"
#include "ui_charactermanager.h"
#include "main_window.h"
#include "world.h"
#include "locationwidget.h"

using namespace Punk::Engine;

CharacterManager::CharacterManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CharacterManager)
{
    ui->setupUi(this);

    MainWindow* mw = qobject_cast<MainWindow*>(parent);
    if (mw) {
        m_world = mw->GetWorl();
    }

    m_location = new LocationWidget(this);
    ui->verticalLayout->addWidget(m_location);
    m_location->show();
}

CharacterManager::~CharacterManager()
{
    delete ui;
}

void CharacterManager::createCharacter() {
    qDebug("Create new character request");
    Core::IObject* o = nullptr;
    CharacterFactory factory;
    factory.CreateInstance(CLSID_Character, Core::IID_IObject, (void**)&o);
    if (o) {
        qDebug("Character created");
        m_characters.push_back(o);
        QGraphicsItem* item = dynamic_cast<QGraphicsItem*>(o);
        if (item) {
            qDebug("Character added to world");
            m_world->addItem(item);
        }
    }
    Punk::Engine::ILocation* location = nullptr;
    o->QueryInterface(IID_ILocation, (void**)&location);
    if (location) {
        m_location->setLocation(location);
        location->Release();
    } else {
        qDebug("Location was not retrieved");
    }
}
