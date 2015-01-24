#ifndef _H_MATH_FORWARD
#define _H_MATH_FORWARD

#include <config.h>
#include <math/constants.h>
#include <vector>

PUNK_ENGINE_BEGIN

namespace Math {

	struct tagPoint;
	struct tagColor;
	struct tagVector;
	struct tagQuaternion;
	struct tagIndex;
	struct tagGeneral;

	template<class T, int D, typename tag> class Tuple;
	template<class T, int Rows, int Cols> class Matrix;

	using mat4 = Matrix<float, 4, 4>;

	using mat3 = Matrix < float, 3, 3 >;

	using mat2 = Matrix <float, 2, 2 >;
	
	using color3 = Tuple < float, 3, tagColor > ;
	using color4 = Tuple < float, 4, tagColor >;

	using vec3 = Tuple < float, 3, tagVector >;	
	using point3d = Tuple < float, 3, tagPoint >;
	using ivec3 = Tuple < int, 3, tagVector >;
	using ivec3v = std::vector < ivec3 >;
	using vec3v = std::vector < vec3 >;
	using point3dv = std::vector < point3d >;
	
	using quat = Tuple < float, 4, tagQuaternion >;
	
	using point2d = Tuple < float, 2, tagPoint >;	
	using vec2 = Tuple < float, 2, tagVector >;
	using ivec2 = Tuple < int, 2, tagVector >;
	using ivec2v = std::vector < ivec2 >;
	using vec2v = std::vector < vec2 >;

	using point4d = Tuple < float, 4, tagPoint >;
	using vec4 = Tuple < float, 4, tagVector >;
	using ivec4 = Tuple < int, 4, tagVector >;
	using ivec4v = std::vector < ivec4 >;
	using vec4v = std::vector < vec4 >;

	template<class T> class TBoundingBox;
	using BoundingBox = TBoundingBox<float>;

	template<class T> class TBoundingSphere;
	using BoundingSphere = TBoundingSphere < float >;

	template<class T> class TRectangle;
	using Rectangle = TRectangle<float>;

	template<class T, int Dim> class Line;
	using Line3D = Line<float, 3>;

	template<class T> class TClipSpace;
	using ClipSpace = TClipSpace<float>;
}

PUNK_ENGINE_END

#endif	//	_H_MATH_FORWARD