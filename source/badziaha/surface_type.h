#ifndef _H_SURFACE_TYPE
#define _H_SURFACE_TYPE

#include <qtcore/qstring.h>
#include <QtGui/qimage.h>

class SurfaceTypeClass {
public:

	SurfaceTypeClass() {}

	const QString name() const { return m_name; }
	QImage icon() const;
	const QString iconPath() const { return m_icon_path; }
	float movePenalty() const { return m_ground_move_penalty; }
	bool isLand() const { return m_land; }
	bool isWater() const { return !m_land; }

	void setName(const QString& value) { m_name = value; }
	void setIcon(QImage value) { m_icon = value; }
	void setIcon(const QString& value) { m_icon_path = value; }
	void setMovePenalty(float value) { m_ground_move_penalty = value; }
	void setIsLand(bool value) { m_land = value; }
private:
	QString m_name;
	QString m_icon_path;
	mutable QImage m_icon;
	float m_ground_move_penalty;
	bool m_land;
};

#endif	//	_H_SURFACE_TYPE