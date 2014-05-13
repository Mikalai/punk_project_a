#ifndef _H_PUNK_VIRTUAL_GEOMETRY
#define _H_PUNK_VIRTUAL_GEOMETRY

#include <config.h>
#include <core/object.h>
#include <math/module.h>
#include <graphics/module.h>
#include "igeometry.h"
#include "igeometry_cooker.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

    class PUNK_ENGINE_LOCAL Geometry : public Core::Object, public IGeometry
	{	
	public:
        Geometry();
		virtual ~Geometry();	

		//	position
		const Math::vec3* GetVertexPosition(std::uint32_t index) const override;
		void SetVertexPosition(std::uint32_t index, const Math::vec3& value) override;
		void SetVertexPositions(const Math::vec3v& value) override;
		bool HasVertexPositions() const override;

		//	normal
		const Math::vec3* GetVertexNormal(std::uint32_t index) const override;
		void SetVertexNormal(std::uint32_t index, const Math::vec3& value) override;
		void SetVertexNormals(const Math::vec3v& value) override;
		bool HasVertexNormals() const override;

		//	color
		const Math::vec4* GetVertexColor(std::uint32_t index) const override;
		void SetVertexColor(std::uint32_t index, const Math::vec4& value) override;
		void SetVertexColors(const Math::vec4v& value) override;
		bool HasVertexColors() const override;

		//	texture
		std::uint32_t GetVertexTextureCoordinatesSetCount() const override;
		std::uint32_t GetVertexTextureCoordinatesCount(std::uint32_t set_index) const override;
		const Math::vec4* GetVertexTextureCoordinate(std::uint32_t set_index, std::uint32_t vertex_index) const override;
		void SetVertexTextureCoordinatesSetCount(std::uint32_t value) override;
		void SetVertexTextureCoordinate(std::uint32_t set_index, std::uint32_t vertex_index, const Math::vec4& value) override;
		void SetVertexTextureCoordinates(std::uint32_t set_index, const Math::vec4v& value) override;
		bool HasVertexTextureCoordinates() const override;
		bool HasVertexTextureCoordinateSet(std::uint32_t set_index) const override;

		//	bone weights
		const Math::vec4* GetWeights(std::uint32_t index) const override;
		const Math::ivec4* GetBonesIndex(std::uint32_t index) const override;
		void SetVertexBonesWeight(std::uint32_t index, const Math::vec4& weights, const Math::ivec4& bones) override;
		void SetVertexBonesWeights(const Math::vec4v& weights, const Math::ivec4v& bones) override;
		bool HasVertexBoneWeights() const override;
		const IArmatureSchema* GetArmatureSchema() const override;
		void SetArmatureSchema(IArmatureSchema* value) override;

		//	triangles
		std::uint32_t GetTrianglesCount() const override;
		const Math::ivec3* GetTriangle(std::uint32_t index) const override;
		void SetTriangle(std::uint32_t index, const Math::ivec3& value) override;
		void SetTriangles(const Math::ivec3v& value) override;
		bool IsIndexed() const override;

		//	texture_face
		void SetFaceTextureCoordinates(const std::vector<std::array<Math::vec2, 3>>& value) override;
		void SetFaceTextureCoordinate(std::uint32_t triangle_index, std::uint32_t vertex_index, const Math::vec2& t) override;
		const Math::vec2* GetFaceTextureCoordinate(std::uint32_t triangle_index, int vertex_index) const override;
		bool HasFaceTextureCoordinates() const override;

		//	geometry
		bool Validate() override;
		const Math::BoundingBox* GetBoundingBox() const override;
		const Math::BoundingSphere* GetBoundingSphere() const override;
		std::uint32_t GetVertexCount() override;

    protected:
		Geometry(const Geometry&) = delete;
		Geometry& operator = (const Geometry&) = delete;

		Math::vec3v m_position;
		Math::vec3v m_normals;
		Math::vec4v m_colors;
		std::vector<Math::vec4v> m_textures;
		Math::vec4v m_weights;
		Math::ivec4v m_bones;
		std::vector<std::array<Math::vec2, 3>> m_texture_faces;
        Math::BoundingBox m_bbox;
        Math::BoundingSphere m_sphere;    
		Math::ivec3v m_triangles;
		IArmatureSchema* m_armature_schema{ nullptr };
			
		bool m_need_update{ true };

        PUNK_OBJECT(Geometry)
	};    
}
PUNK_ENGINE_END

#endif // _H_PUNK_VIRTUAL_GEOMETRY
