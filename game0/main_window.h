#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class World;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    World* GetWorl() { return m_world; }

public slots:
    void createBuildingSchema();
    void editRoofMaterials();
    void editWallMaterials();
    void editMaterials();

private:
    Ui::MainWindow *ui;
    World* m_world;
};

#endif // MAIN_WINDOW_H
