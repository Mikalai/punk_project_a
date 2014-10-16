#include "main_window.h"
#include "ui_main_window.h"
#include "manage_building_schema.h"
#include "editnames.h"
#include "edit_materials.h"
#include "world.h"
#include "charactermanager.h"
#include "locationwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_world = new World(this);
    ui->m_visualization_viewport->setScene(m_world);
    m_world->addEllipse(0, 0, 100, 100);
    m_world->addEllipse(2000, 2000, 100, 100);
    //showFullScreen();
    CharacterManager* manager = new CharacterManager(this);
    manager->show();    
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createBuildingSchema() {
    ManageBuildingSchema create_schema(this);
    create_schema.exec();
}

void MainWindow::editRoofMaterials() {
    EditNames dlg("Edit roof materials...", "roof_materials", this);
    dlg.exec();
}

void MainWindow::editWallMaterials() {
    EditNames dlg("Edit wall materials...", "wall_materials", this);
    dlg.exec();
}

void MainWindow::editMaterials() {
    qDebug("Edit materials");
    EditMaterials dlg(this);
    dlg.exec();
}
