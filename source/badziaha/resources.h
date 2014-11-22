#ifndef _H_RESOURCES
#define _H_RESOURCES

#include <QtCore/qstring.h>
#include <map>
#include <memory>
#include <vector>
#include "item_class_type.h"
#include "fwd_items.h"


class QImage;
enum class SurfaceType;
enum class ModelType;

class Resources {
public:

	using ItemClasses = std::vector < const ItemClass* > ;
	using ClothesClasses = std::vector < const ClothesClass* > ;
	Resources();

	QImage* getImage(const SurfaceType& value);
	QImage* getSquadImage();
	QImage* getCityImage();
	QImage* modelImage(const ModelType& value);	
	QImage* loadImage(const QString& value);

	static void destroy();
	static Resources* instance();

	const ItemClasses& items() const { return m_items_cache; }
	const ClothesClasses& clothes() const { return m_clothes_cache; }

private:
	void readItems();

private:
	static std::unique_ptr<Resources> m_instance;
	std::vector<std::unique_ptr<QImage>> m_global_field_cell_ground;
	std::unique_ptr<QImage> m_squad_image;
	std::unique_ptr<QImage> m_city_image;
	std::vector<std::unique_ptr<QImage>> m_models;
	std::map<QString, std::unique_ptr<QImage>> m_images;
	std::vector<ItemClassPtr> m_items;
	ItemClasses m_items_cache;
	ClothesClasses m_clothes_cache;
};

#endif	//	_H_RESOURCES