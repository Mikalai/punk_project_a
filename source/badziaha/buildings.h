#ifndef _H_BUILDINGS
#define _H_BUILDINGS

#include "entity.h"

class City;

class Construction : public Entity {
	Q_OBJECT
public:
	Construction(GlobalField* field, QObject* parent = nullptr);

	City* city() { return m_city; }

//private:
	//	assigns a city to wich this building is subordinated
	void setCity(City* city) { m_city = city; }

private:
	City* m_city{ nullptr };
};


class SawMill : public Construction {
	Q_OBJECT
public:
	SawMill(GlobalField* field, QObject* parent = nullptr);
	void update() override;
private:
	float m_wood_per_second{ 1 };
	float m_wood{ 0 };
};

#endif	//	_H_BUILDINGS