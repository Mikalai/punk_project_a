#include "resources.h"
#include "global_field.h"
#include "model_type.h"

Resources::Resources() {
	m_global_field_cell_ground.push_back(std::unique_ptr < QImage > {new QImage{ ":/images/grass.png" }});
	m_global_field_cell_ground.push_back(std::unique_ptr < QImage > {new QImage{ ":/images/water.png" }});
	m_global_field_cell_ground.push_back(std::unique_ptr < QImage > {new QImage{ ":/images/sand.png" }});
	m_global_field_cell_ground.push_back(std::unique_ptr < QImage > {new QImage{ ":/images/dirt.png" }});
	m_global_field_cell_ground.push_back(std::unique_ptr < QImage > {new QImage{ ":/images/forest.png" }});
	m_global_field_cell_ground.push_back(std::unique_ptr < QImage > {new QImage{ ":/images/rocks.png" }});
	m_squad_image.reset(new QImage{ ":/images/ranger.png" });
	m_city_image.reset(new QImage{ ":/images/city.png" });

	m_models.resize((int)ModelType::End);
	m_models[(int)ModelType::City].reset(new QImage{ ":/images/city.png" });
	m_models[(int)ModelType::Squad].reset(new QImage{ ":/images/ranger.png" });
	m_models[(int)ModelType::Warrior].reset(new QImage{ ":/images/warrior.png" });
	m_models[(int)ModelType::Worker].reset(new QImage{ ":/images/worker.png" });
	m_models[(int)ModelType::SawMill].reset(new QImage{ ":/images/sawmill.png" });
	m_models[(int)ModelType::Construction].reset(new QImage{ ":/images/construction.png" });
}

QImage* Resources::getImage(const GlobalFieldCellGround& value) {
	return m_global_field_cell_ground.at((int)value).get();
}

std::unique_ptr<Resources> Resources::m_instance;

void Resources::destroy() {
	m_instance.reset(nullptr);
}

Resources* Resources::instance() {
	if (!m_instance.get())
		m_instance.reset(new Resources);
	return m_instance.get();
}

QImage* Resources::getSquadImage() {
	return m_squad_image.get();
}

QImage* Resources::getCityImage() {
	return m_city_image.get();
}

QImage* Resources::getModelImage(const ModelType& value) {
	int index = (int)value;
	return m_models.at(index).get();
}