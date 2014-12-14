#ifndef _H_ROAD
#define _H_ROAD

#include <QtCore/qobject.h>
#include <QtCore/qstring.h>
#include <QtGui/qimage.h>
#include <list>
#include "fwd_road.h"

class QGraphicsItem;
class GlobalField;
class GlobalFieldCell;

class RoadClass {
public:
	int id() const { return m_id; }
	QString name() const { return m_name; }
	QString description() const { return m_description; }
	QString category() const { return m_category; }
	int lanesCount() const { return m_lanes_count; }
	float laneWidth() const { return m_lane_width; }
	float roadwayWidth() const { return lanesCount() * laneWidth(); }
	float roadsideWidth() const { return m_roadside_width; }
	float fortifiedRoadsideWidth() const { return m_fortified_roadside_width; }
	float fortifiedSeparationWidth() const { return m_fortified_separation_width; }
	float separationWidth() const { return m_separation_width; }
	float subgradeWidth() const { return m_subgrade_width; }
	float speed() const { return m_speed; }
	float crossroadSpeed() const { return m_crossroad_speed; }
	float mountainSpeed() const { return m_mountain_speed; }
	int estimatedTraffic() const { return m_estimate_traffic; }
	QString surfacePath() const { return m_surface_image_path; }
	QImage surface() const;

	void setName(QString value) { m_name = value; }
	void setDescription(QString value) { m_description = value; }
	void setCategory(QString value) { m_category = value; }
	void setLanesCount(int value) { m_lanes_count = value; }
	void setLaneWidth(float value) { m_lane_width = value; }
	void setRoadwayWidth(float value) { m_roadway_width = value; }
	void setRoadsideWidth(float value) { m_roadside_width = value; }
	void setFortifiedRoadsideWidth(float value) { m_fortified_roadside_width = value; }
	void setFortifiedSeparationWidth(float value) { m_fortified_separation_width = value; }
	void setSeparationWidth(float value) { m_separation_width = value; }
	void setSubgradeWidth(float value) { m_subgrade_width = value; }
	void setSpeed(float value) { m_speed = value; }
	void setCrossroadSpeed(float value) { m_crossroad_speed = value; }
	void setMountainSpeed(float value) { m_mountain_speed = value; }
	void setEstimatedTraffic(int value) { m_estimate_traffic = value; }
	void setSurfacePath(QString value) { m_surface_image_path = value; }

	QString ToString() const;

private:
	int m_id;
	QString m_name;
	QString m_description;
	QString m_category;
	int m_lanes_count{ 2 };
	float m_lane_width{ 3.75f };
	float m_roadway_width{ 7 };
	float m_roadside_width{ 3.75f };
	float m_fortified_roadside_width{ 0.75f };
	float m_fortified_separation_width{ 1.0f };
	float m_separation_width{ 5 };
	float m_subgrade_width{ 28.5f };
	float m_speed{ 41.67f };
	float m_crossroad_speed{ 33.33f };
	float m_mountain_speed{ 22.22f };
	int m_estimate_traffic{ 7000 };
	mutable QImage m_surface_image;
	QString m_surface_image_path;
};

class RoadSegment : public QGraphicsItem {
public:
public:

private:
	Road* m_road{ nullptr };
};

class Road : public QObject {
public:
	Road(RoadClass* road_class, GlobalField* field, GlobalFieldCell* start, GlobalFieldCell* end, QObject* parent = nullptr);
	virtual ~Road();

	QGraphicsItem* model() {
		return m_model;
	}

	bool split(GlobalFieldCell* cell, Road** a, Road** b);

	std::list<GlobalFieldCell*>& getPath() {
		return m_path;
	}

	//	can extend current road on one neighbour cell
	void extend(GlobalFieldCell* cell);

	void removeRoad();

	GlobalField* field() { return m_field; }

	int classId() const { return roadClass()->id(); }
	QString name() const { return m_name; }
	QString description() const { return m_description; }
	QString category() const { return roadClass()->category(); }
	int lanesCount() const { return roadClass()->lanesCount(); }
	float laneWidth() const { return roadClass()->laneWidth(); }
	float roadwayWidth() const { return roadClass()->roadwayWidth(); }
	float roadsideWidth() const { return roadClass()->roadsideWidth(); }
	float fortifiedRoadsideWidth() const { return roadClass()->fortifiedRoadsideWidth(); }
	float fortifiedSeparationWidth() const { return roadClass()->fortifiedSeparationWidth(); }
	float separationWidth() const { return roadClass()->separationWidth(); }
	float subgradeWidth() const { return roadClass()->subgradeWidth(); }
	float speed() const { return roadClass()->speed(); }
	float crossroadSpeed() const { return roadClass()->crossroadSpeed(); }
	float mountainSpeed() const { return roadClass()->mountainSpeed(); }
	int estimatedTraffic() const { return roadClass()->estimatedTraffic(); }
	QString surfacePath() const { return roadClass()->surfacePath(); }
	QImage surface() const { return roadClass()->surface(); }

	RoadClass* roadClass() { return m_class; }
	const RoadClass* roadClass() const { return m_class; }

	void setName(QString value) { m_name = value; }
	void setDescription(QString value) { m_description = value; }

private:
	QGraphicsItem* m_model{ nullptr };
	std::list<GlobalFieldCell*> m_path;
	GlobalFieldCell* m_start{ nullptr };
	GlobalFieldCell* m_end{ nullptr };
	GlobalField* m_field{ nullptr };
	RoadClass* m_class{ nullptr };
	QString m_name;
	QString m_description;
};

#endif	//	 _H_ROAD