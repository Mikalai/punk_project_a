#include "geometry.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
	Core::Rtti GeometryType{ "Attributes.Geometry", typeid(Geometry).hash_code(), { Core::Object::Type() } };

	Core::Rtti* Geometry::Type() {
		return &GeometryType;
	}

	Geometry::Geometry()
	{}

	Geometry::~Geometry()
	{}

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
	void Geometry::SetFaceTextureCoordinates(const std::vector	<std::array<Math::vec2, 3>>& value) {
		m_texture_faces = value;
	}
	
	void Geometry::SetFaceTextureCoordinate(std::uint32_t triangle_index, std::uint32_t vertex_index, const Math::vec2& t) {
		m_texture_faces[triangle_index][vertex_index] = t;
	}

	const Math::vec2* Geometry::GetFaceTextureCoordinate(std::uint32_t triangle_index, int vertex_index) const {
		return &m_texture_faces[triangle_index][vertex_index];
	}

	bool Geometry::HasFaceTextureCoordinates() const {
		return !m_texture_faces.empty();
	}

	//	bone weights
	const Math::vec4* Geometry::GetWeights(std::uint32_t index) const {
		return &m_weights[index];
	}

	const Math::ivec4* Geometry::GetBonesIndex(std::uint32_t index) const {
		return &m_bones[index];
	}

	void Geometry::SetVertexBonesWeight(std::uint32_t index, const Math::vec4& weights, const Math::ivec4& bones) {
		m_weights[index] = weights;
		m_bones[index] = bones;
	}

	void Geometry::SetVertexBonesWeights(const Math::vec4v& weights, const Math::ivec4v& bones) {
		m_weights = weights;
		m_bones = bones;
	}

	const IArmatureSchema* Geometry::GetArmatureSchema() const {
		return m_armature_schema;
	}

	void Geometry::SetArmatureSchema(IArmatureSchema* value) {
		m_armature_schema = value;
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
}
PUNK_ENGINE_END
