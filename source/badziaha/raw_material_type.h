#ifndef _H_RAW_MATERIAL_TYPE
#define _H_RAW_MATERIAL_TYPE

enum class RawMaterialType {
	Water,
	Food,
	Wood,
	End
};

constexpr int getIndex(const RawMaterialType value) {
	return (int)value;
}

#endif	//	 _H_RAW_MATERIAL_TYPE