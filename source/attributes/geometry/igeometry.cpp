#include <system/factory/module.h>
#include <config.h>
#include <core/object.h>
#include <math/module.h>
#include <graphics/module.h>
#include "igeometry.h"
#include "igeometry_cooker.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{	
	class PUNK_ENGINE_LOCAL Geometry : public IGeometry, public Math::IBoundingBox, public Math::IBoundingSphere
	{
	public:
		Geometry();
		virtual ~Geometry();

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override;
		std::uint32_t AddRef() override;
		std::uint32_t Release() override;

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
		const Math::vec4* GetVertexBoneWeights(std::uint32_t index) const override;
		const Math::ivec4* GetVertexBonesIndecies(std::uint32_t index) const override;
		void SetVertexBonesWeight(std::uint32_t index, const Math::vec4& weights, const Math::ivec4& bones) override;
		void SetVertexBonesWeights(const std::vector<std::vector<std::pair<int, float>>>& b) override;
		bool HasVertexBoneWeights() const override;
		const Core::String& GetArmatureSchema() const override;
		void SetArmatureSchema(Core::String& value) override;
		void SetArmatureOffset(const Math::mat4& value) override;
		const Math::mat4& GetArmatureOffset() const override;

		//	triangles
		std::uint32_t GetTrianglesCount() const override;
		const Math::ivec3* GetTriangle(std::uint32_t index) const override;
		void SetTriangle(std::uint32_t index, const Math::ivec3& value) override;
		void SetTriangles(const Math::ivec3v& value) override;
		bool IsIndexed() const override;

		//	texture_face
		std::uint32_t GetFaceTextureCoordinatesSlotsCount() const override;
		void SetFaceTextureCoordinates(const std::vector<std::vector<std::array<Math::vec2, 3>>>& value) override;
		void SetFaceTextureCoordinates(std::uint32_t slot, const std::vector<std::array<Math::vec2, 3>>& value) override;
		void SetFaceTextureCoordinate(std::uint32_t slot, std::uint32_t triangle_index, std::uint32_t vertex_index, const Math::vec2& t) override;
		const Math::vec2* GetFaceTextureCoordinate(std::uint32_t slot, std::uint32_t triangle_index, int vertex_index) const override;
		bool HasFaceTextureCoordinates() const override;

		//	geometry
		bool Validate() override;
		const Math::BoundingBox* GetBoundingBox() const override;
		const Math::BoundingSphere* GetBoundingSphere() const override;
		std::uint32_t GetVertexCount() override;
		void SetName(const Core::String& name) override;
		const Core::String& GetName() const override;

		//	IBoundingVolume3D
		bool IsPointInside(const Math::vec3& value) override {
			auto res = Math::ClassifyPoint(value, m_sphere);
			return res == Math::Relation::INSIDE;
		}

		bool IsPointInside(const Math::vec3& value, Math::IntersectionHint& hint) override {
			hint = Math::IntersectionHint::No;
			auto res = Math::ClassifyPoint(value, m_sphere);
			if (res == Math::Relation::INSIDE)
				hint = hint | Math::IntersectionHint::BoundingSphere;
			res = Math::ClassifyPoint(value, m_bbox);
			if (res == Math::Relation::INSIDE)
				hint = hint | Math::IntersectionHint::BoundingBox;
			return hint != Math::IntersectionHint::No;
		}

		Core::Pointer<Math::IIntersectionResult> CrossLine(const Math::Line3D& line) override {
			auto result = System::CreateInstancePtr<Math::IIntersectionResult>(Math::IID_IIntersectionResult);
			Math::vec3 p1, p2;
			auto res = Math::CrossLineSphere(line, m_sphere, p1, p2);
			switch (res)
			{
			case Punk::Engine::Math::Relation::INTERSECT_1:
				result->AddIntersectionPoint(p1, Math::IntersectionHint::BoundingSphere);				
				break;
			case Punk::Engine::Math::Relation::INTERSECT_2:
				result->AddIntersectionPoint(p1, Math::IntersectionHint::BoundingSphere);
				result->AddIntersectionPoint(p2, Math::IntersectionHint::BoundingSphere);
				break;
			}
			res = Math::CrossLineBoundingBox(line, m_bbox, p1);
			if (res == Math::Relation::INTERSECT)
				result->AddIntersectionPoint(p1, Math::IntersectionHint::BoundingBox);
			return result;
		}

		bool CrossFrustum(const Math::Frustum& frust, const Math::mat4& to_frustum_space) override {
			auto sphere = to_frustum_space * m_sphere;
			if (Math::ClassifyBoudingSphere(m_sphere, frust.GetClipSpace()) == Math::Relation::NOT_VISIBLE)
				return false;

			auto bbox = to_frustum_space * m_bbox;
			return Math::ClassifyBoudingBox(bbox, frust.GetClipSpace()) == Math::Relation::VISIBLE;
		}

		//	IBoundingBox
		const Math::BoundingBox& GetBox() const override {
			return m_bbox;
		}

		void SetBox(const Math::BoundingBox& value) override {
			m_bbox = value;
		}

		//	IBoundingSphere
		const Math::BoundingSphere& GetSphere() const override {
			return m_sphere;
		}

		void SetSphere(const Math::BoundingSphere& value) override {
			m_sphere = value;
		}

	protected:
		Geometry(const Geometry&) = delete;
		Geometry& operator = (const Geometry&) = delete;

		std::atomic<std::uint32_t> m_ref_count{ 0 };
		Math::vec3v m_position;
		Math::vec3v m_normals;
		Math::vec4v m_colors;
		std::vector<Math::vec4v> m_textures;
		Math::vec4v m_weights;
		Math::ivec4v m_bones;
		std::vector<std::vector<std::array<Math::vec2, 3>>> m_texture_faces;
		Math::BoundingBox m_bbox;
		Math::BoundingSphere m_sphere;
		Math::ivec3v m_triangles;
		Core::String m_armature_schema;
		Core::String m_name;
		Math::mat4 m_armature_offset;
		bool m_need_update{ true };
	};

	Geometry::Geometry()
	{}

	Geometry::~Geometry()
	{}

	void Geometry::QueryInterface(const Core::Guid& type, void** object) {
		if (!object)
			return;
		if (type == Core::IID_IObject) {
			*object = (void*)(IGeometry*)this;
			AddRef();
		}
		else if (type == IID_IGeometry) {
			*object = (void*)(IGeometry*)this;
			AddRef();
		}
		else if (type == Math::IID_IBoundingBox) {
			*object = (void*)(Math::IBoundingBox*)this;
			AddRef();
		}
		else if (type == Math::IID_IBoundingSphere) {
			*object = (void*)(Math::IBoundingSphere*)this;
			AddRef();
		}
		else
			*object = nullptr;
	}

	std::uint32_t Geometry::AddRef() {
		return m_ref_count.fetch_add(1);
	}

	std::uint32_t Geometry::Release() {
		auto v = m_ref_count.fetch_sub(1) - 1;
		if (!v) {
			delete this;
		}
		return v;
	}

	//	position
	const Math::vec3* Geometry::GetVertexPosition(std::uint32_t index) const {
		return &m_position[index];
	}

	void Geometry::SetVertexPosition(std::uint32_t index, const Math::vec3& value) {
		m_position[index] = value;
		m_bbox.Create(m_position.data(), m_position.size());
	}

	void Geometry::SetVertexPositions(const Math::vec3v& value) {
		m_position = value;
	}

	bool Geometry::HasVertexPositions() const {
		return !m_position.empty();
	}

	//	normal
	const Math::vec3* Geometry::GetVertexNormal(std::uint32_t index) const {
		return &m_normals[index];
	}

	void Geometry::SetVertexNormal(std::uint32_t index, const Math::vec3& value) {
		m_normals[index] = value;
	}

	void Geometry::SetVertexNormals(const Math::vec3v& value) {
		m_normals = value;
	}

	bool Geometry::HasVertexNormals() const {
		return !m_normals.empty();
	}

	//	color
	const Math::vec4* Geometry::GetVertexColor(std::uint32_t index) const {
		return &m_colors[index];
	}

	void Geometry::SetVertexColor(std::uint32_t index, const Math::vec4& value) {
		m_colors[index] = value;
	}

	void Geometry::SetVertexColors(const Math::vec4v& value) {
		m_colors = value;
	}

	bool Geometry::HasVertexColors() const {
		return !m_colors.empty();
	}

	//	texture
	std::uint32_t Geometry::GetVertexTextureCoordinatesSetCount() const {
		return m_textures.size();
	}

	std::uint32_t Geometry::GetVertexTextureCoordinatesCount(std::uint32_t set_index) const {
		return m_textures[set_index].size();
	}

	const Math::vec4* Geometry::GetVertexTextureCoordinate(std::uint32_t set_index, std::uint32_t vertex_index) const {
		return &m_textures[set_index][vertex_index];
	}

	void Geometry::SetVertexTextureCoordinatesSetCount(std::uint32_t value) {
		m_textures.resize(value);
	}

	void Geometry::SetVertexTextureCoordinate(std::uint32_t set_index, std::uint32_t vertex_index, const Math::vec4& value) {
		m_textures[set_index][vertex_index] = value;
	}

	void Geometry::SetVertexTextureCoordinates(std::uint32_t set_index, const Math::vec4v& value) {
		m_textures[set_index] = value;
	}

	bool Geometry::HasVertexTextureCoordinates() const {
		return !m_textures.empty();
	}

	bool Geometry::HasVertexTextureCoordinateSet(std::uint32_t set_index) const {
		return m_textures.size() > set_index;
	}

	//	texture_face
	std::uint32_t Geometry::GetFaceTextureCoordinatesSlotsCount() const {
		return m_texture_faces.size();
	}

	void Geometry::SetFaceTextureCoordinates(const std::vector<std::vector<std::array<Math::vec2, 3>>>& value) {
		m_texture_faces = value;
	}

	void Geometry::SetFaceTextureCoordinates(std::uint32_t slot, const std::vector	<std::array<Math::vec2, 3>>& value) {
		if (m_texture_faces.size() <= slot)
			m_texture_faces.resize(slot+1);
		m_texture_faces[slot] = value;
	}
	
	void Geometry::SetFaceTextureCoordinate(std::uint32_t slot, std::uint32_t triangle_index, std::uint32_t vertex_index, const Math::vec2& t) {
		if (m_texture_faces.size() <= slot)
			m_texture_faces.resize(slot + 1);
		if (m_texture_faces[slot].size() <= triangle_index)
			m_texture_faces[slot].resize(triangle_index + 1);
		m_texture_faces[slot][triangle_index][vertex_index] = t;
	}

	const Math::vec2* Geometry::GetFaceTextureCoordinate(std::uint32_t slot, std::uint32_t triangle_index, int vertex_index) const {		
		return &m_texture_faces.at(slot).at(triangle_index).at(vertex_index);
	}

	bool Geometry::HasFaceTextureCoordinates() const {
		return !m_texture_faces.empty();
	}

	//	bone weights
	const Math::vec4* Geometry::GetVertexBoneWeights(std::uint32_t index) const {
		return &m_weights[index];
	}

	const Math::ivec4* Geometry::GetVertexBonesIndecies(std::uint32_t index) const {
		return &m_bones[index];
	}

	void Geometry::SetVertexBonesWeight(std::uint32_t index, const Math::vec4& weights, const Math::ivec4& bones) {
		m_weights[index] = weights;
		m_bones[index] = bones;
	}

	void Geometry::SetVertexBonesWeights(const std::vector<std::vector<std::pair<int, float>>>& b) {		
		m_weights.resize(b.size());
		m_bones.resize(b.size());
		for (int vertex_index = 0, max_vertex_index = b.size(); vertex_index < max_vertex_index; ++vertex_index) {
			for (int bone_index = 0, max_bone_index = b[vertex_index].size(); bone_index < max_bone_index; ++bone_index) {
				m_bones[vertex_index][bone_index] = b[vertex_index][bone_index].first;
				m_weights[vertex_index][bone_index] = b[vertex_index][bone_index].second;
			}
		}
	}

	bool Geometry::HasVertexBoneWeights() const {
		return !m_weights.empty() && !m_bones.empty();
	}

	const Core::String& Geometry::GetArmatureSchema() const {
		return m_armature_schema;
	}

	void Geometry::SetArmatureSchema(Core::String& value) {
		m_armature_schema = value;
	}

	void Geometry::SetArmatureOffset(const Math::mat4& value) {
		m_armature_offset = value;
	}
	
	const Math::mat4& Geometry::GetArmatureOffset() const {
		return m_armature_offset;
	}

	std::uint32_t Geometry::GetTrianglesCount() const {
		return m_triangles.size();
	}

	const Math::ivec3* Geometry::GetTriangle(std::uint32_t index) const {
		return &m_triangles[index];
	}

	void Geometry::SetTriangle(std::uint32_t index, const Math::ivec3& value) {
		m_triangles[index] = value;
	}

	void Geometry::SetTriangles(const Math::ivec3v& value) {
		m_triangles = value;
	}

	bool Geometry::IsIndexed() const {
		return !m_triangles.empty();
	}

	//	geometry
	bool Geometry::Validate() {
		return true;
	}

	const Math::BoundingBox* Geometry::GetBoundingBox() const {
		return &m_bbox;
	}

	const Math::BoundingSphere* Geometry::GetBoundingSphere() const {
		return &m_sphere;
	}

	std::uint32_t Geometry::GetVertexCount() {
		return m_position.size();
	}

	void Geometry::SetName(const Core::String& value) {
		m_name = value;
	}

	const Core::String& Geometry::GetName() const {
		return m_name;
	}

	PUNK_REGISTER_CREATOR(IID_IGeometry, (System::CreateInstance<Geometry, IGeometry>));
}
PUNK_ENGINE_END
