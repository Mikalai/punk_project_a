#ifndef LOCATIONWIDGET_H
#define LOCATIONWIDGET_H

#include <QWidget>
#include <interfaces/location.h>

namespace Ui {
    class LocationWidget;
}

class LocationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LocationWidget(QWidget *parent = 0);
    ~LocationWidget();

public slots:
    void moveLeft();
    void moveRight();
    void moveTop();
    void moveBottom();
    void rotateRight();
    void rotateLeft();
    void setLocation(Punk::Engine::ILocation* value);

private:
    void updateUi();

private:
    Ui::LocationWidget *ui;
    Punk::Engine::ILocation* m_location = nullptr;
};

#endif // LOCATIONWIDGET_H
