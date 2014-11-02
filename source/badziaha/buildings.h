#ifndef _H_BUILDINGS
#define _H_BUILDINGS

#include "entity.h"

class Construction : public Entity {
	Q_OBJECT
public:
	Construction(GlobalField* field, QObject* parent = nullptr);
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