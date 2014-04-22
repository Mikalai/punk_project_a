#ifndef _H_PUNK_MATH_SHAPE_MESH
#define _H_PUNK_MATH_SHAPE_MESH

#include <cstdint>
#include <config.h>

PUNK_ENGINE_BEGIN
namespace Math {

	namespace __private {
		struct ConvexShapeMeshImpl;
	}

	class vec3;
	class ivec3;
	class BoundingBox;
	class BoundingSphere;

	class PUNK_ENGINE_API ConvexShapeMesh
	{
	public:
		ConvexShapeMesh();
		ConvexShapeMesh(const ConvexShapeMesh& value);
		ConvexShapeMesh& operator = (const ConvexShapeMesh& value);
		~ConvexShapeMesh();

		void SetPoints(const vec3* points, std::size_t count);
		void SetFaces(const ivec3* faces, std::size_t count);
		void SetNormals(const vec3* normals, std::size_t count);

		const vec3& GetPoint(std::size_t index) const;
		const ivec3& GetFace(std::size_t index) const;
		const vec3& GetNormal(std::size_t index) const;

		std::size_t GetFaceCount() const;
		std::size_t GetPointsCount() const;
		std::size_t GetNormalsCount() const;

		void UpdateBoundingVolumes();

		const Math::BoundingBox& GetBoundingBox() const;
		const Math::BoundingSphere& GetBoundingSphere() const;

		__private::ConvexShapeMeshImpl* impl{ nullptr };

	};
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_MATH_SHAPE_MESH
