#include <math/tuple.h>
#include "locationwidget.h"
#include "ui_locationwidget.h"

LocationWidget::LocationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LocationWidget)
{
    ui->setupUi(this);
}

LocationWidget::~LocationWidget()
{
    delete ui;
}

void LocationWidget::moveLeft() {
    qDebug("Move current location left");
    if (!m_location)
        return;
    m_location->Move({-1, 0});
    updateUi();
}

void LocationWidget::moveRight() {
    qDebug("Move current location right");
    m_location->Move({1, 0});
    updateUi();
}

void LocationWidget::moveTop() {
    qDebug("Move current location top");
    m_location->Move({0, 1});
    updateUi();
}

void LocationWidget::moveBottom() {
    qDebug("Move current location bottom");
    m_location->Move({0, -1});
    updateUi();
}

void LocationWidget::rotateRight() {
    qDebug("Rotate current location right");
    m_location->Rotate({-1});
    updateUi();
}

void LocationWidget::rotateLeft() {
    qDebug("Rotate current location left");
    m_location->Rotate({1});
    updateUi();
}

void LocationWidget::setLocation(Punk::Engine::ILocation *value) {
    if (m_location) {
        m_location->Release();
    }
    if (value) {
        value->AddRef();
    }

    m_location = value;
    if (!m_location)
        return;
    updateUi();
}

void LocationWidget::updateUi() {
    ui->m_child_location_count->setText(QString::number(m_location->GetChildLocationsCount()));
    for (int i = 0; i < m_location->GetChildLocationsCount(); ++i) {
        ui->m_child_locations->addItem(QString::number(i));
    }

    ui->m_btn_parent->setEnabled(m_location->GetParentLocation() != nullptr);
    auto g_pos = m_location->GetGlobalPosition();
    ui->m_global_x->setText(QString::number(g_pos.X()));
    ui->m_global_y->setText(QString::number(g_pos.Y()));

    auto l_pos = m_location->GetGlobalPosition();
    ui->m_local_x->setText(QString::number(l_pos.X()));
    ui->m_local_y->setText(QString::number(l_pos.Y()));
}
