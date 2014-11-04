#ifndef _H_RAW_MATERIAL_TYPE
#define _H_RAW_MATERIAL_TYPE

class QString;

enum class RawMaterialType {
	Water,
	Food,
	Wood,
	End
};

const QString asText(RawMaterialType value);

#endif	//	 _H_RAW_MATERIAL_TYPE