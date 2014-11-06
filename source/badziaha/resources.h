#ifndef _H_RESOURCES
#define _H_RESOURCES

#include <memory>
#include <vector>

class QImage;
enum class GlobalFieldCellGround;
enum class ModelType;

class Resources {
public:

	Resources();

	QImage* getImage(const GlobalFieldCellGround& value);
	QImage* getSquadImage();
	QImage* getCityImage();
	QImage* modelImage(const ModelType& value);
	
	static void destroy();
	static Resources* instance();

private:
	static std::unique_ptr<Resources> m_instance;
	std::vector<std::unique_ptr<QImage>> m_global_field_cell_ground;
	std::unique_ptr<QImage> m_squad_image;
	std::unique_ptr<QImage> m_city_image;
	std::vector<std::unique_ptr<QImage>> m_models;
};

#endif	//	_H_RESOURCES