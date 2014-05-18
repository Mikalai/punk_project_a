#include <core/ifactory.h>
#include "geometry.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
	void CreateGeometry(void** object) {
		if (!object)
			return;
		*object = (void*)(new Geometry);
	}

	PUNK_REGISTER_CREATOR(IID_IGeometry, CreateGeometry);

	Geometry::Geometry()
	{}

	Geometry::~Geometry()
	{}

	void Geometry::QueryInterface(const Core::Guid& type, void** object) {
		if (!object)
			return;
		if (type == Core::IID_IObject ||
			type == IID_IGeometry) {
			*object = (void*)this;
			AddRef();
		}
		else
			*object = nullptr;
	}

	//	position
	const Math::vec3* Geometry::GetVertexPosition(std::uint32_t index) const {
		return &m_position[index];
	}

	void Geometry::SetVertexPosition(std::uint32_t index, const Math::vec3& value) {
		m_position[index] = value;
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
}
PUNK_ENGINE_END
