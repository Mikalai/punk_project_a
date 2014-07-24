#include <system/factory/module.h>
#include <config.h>
#include <core/object.h>
#include <core/iserializable.h>
#include <string/buffer.h>
#include <math/bounding_box.h>
#include <math/tuple.h>
#include <math/tbn_space.h>
#include <graphics/module.h>
#include <attributes/selection/iselectable.h>
#include "icomponent_bone_weight.h"
#include "icomponent_color.h"
#include "icomponent_normal.h"
#include "icomponent_position.h"
#include "icomponent_texture.h"
#include "icomponent_index.h"
#include "icomponent_texture_face.h"
#include "igeometry.h"
#include "igeometry_cooker.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{	
	class PUNK_ENGINE_LOCAL GeometryBase : public IGeometry
		, public IVertexPositionStream
		, public IVertexColorStream
		, public IVertexNormalStream
		, public IVertexTextureCoordinateStream
		, public IVertexBoneWeightStream
		, public IFaceIndexStream
		, public IFaceTextureStream		
	{
	public:
		GeometryBase() {}
		virtual ~GeometryBase() {}

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override {
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
			else if (type == IID_IVertexBoneWeightStream) {
				*object = (void*)(IVertexBoneWeightStream*)this;
				AddRef();
			}
			else if (type == IID_IVertexColorStream) {
				*object = (void*)(IVertexColorStream*)this;
				AddRef();
			}
			else if (type == IID_IVertexNormalStream) {
				*object = (void*)(IVertexNormalStream*)this;
				AddRef();
			}
			else if (type == IID_IVertexPositionStream) {
				*object = (void*)(IVertexPositionStream*)this;
				AddRef();
			}
			else if (type == IID_IVertexTextureCoordinateStream) {
				*object = (void*)(IVertexTextureCoordinateStream*)this;
				AddRef();
			}
			else if (type == IID_IFaceIndexStream) {
				*object = (void*)(IFaceIndexStream*)this;
				AddRef();
			}
			else if (type == IID_IFaceTextureStream) {
				*object = (void*)(IFaceTextureStream*)this;
				AddRef();
			}			
			else
				*object = nullptr;
		}
		
		std::uint32_t AddRef() override {
			return m_ref_count.fetch_add(1);
		}

		std::uint32_t Release() override {
			auto v = m_ref_count.fetch_sub(1) - 1;
			if (!v) {
				delete this;
			}
			return v;
		}


		//	position
		const Math::point3d* GetVertexPosition(std::uint32_t index) const override {
			return &m_position[index];
		}

		void SetVertexPosition(std::uint32_t index, const Math::point3d& value) override {
			m_position[index] = value;			
		}

		void SetVertexPositions(const Math::point3dv& value) override {
			m_position = value;
		}

		bool HasVertexPositions() const override {
			return !m_position.empty();
		}

		//	normal
		const Math::vec3* GetVertexNormal(std::uint32_t index) const override {
			return &m_normals[index];
		}

		void SetVertexNormal(std::uint32_t index, const Math::vec3& value) override {
			m_normals[index] = value;
		}

		void SetVertexNormals(const Math::vec3v& value) override {
			m_normals = value;
		}

		bool HasVertexNormals() const override {
			return !m_normals.empty();
		}

		//	color
		const Math::vec4* GetVertexColor(std::uint32_t index) const override {
			return &m_colors[index];
		}

		void SetVertexColor(std::uint32_t index, const Math::vec4& value) override {
			m_colors[index] = value;
		}

		void SetVertexColors(const Math::vec4v& value) override {
			m_colors = value;
		}

		bool HasVertexColors() const override {
			return !m_colors.empty();
		}

		//	texture
		std::uint32_t GetVertexTextureCoordinatesSetCount() const override {
			return m_textures.size();
		}

		std::uint32_t GetVertexTextureCoordinatesCount(std::uint32_t set_index) const override {
			return m_textures[set_index].size();
		}

		const Math::vec4* GetVertexTextureCoordinate(std::uint32_t set_index, std::uint32_t vertex_index) const override {
			return &m_textures[set_index][vertex_index];
		}

		void SetVertexTextureCoordinatesSetCount(std::uint32_t value) override {
			m_textures.resize(value);
		}

		void SetVertexTextureCoordinate(std::uint32_t set_index, std::uint32_t vertex_index, const Math::vec4& value) override {
			m_textures[set_index][vertex_index] = value;
		}

		void SetVertexTextureCoordinates(std::uint32_t set_index, const Math::vec4v& value) override {
			m_textures[set_index] = value;
		}

		bool HasVertexTextureCoordinates() const override {
			return !m_textures.empty();
		}

		bool HasVertexTextureCoordinateSet(std::uint32_t set_index) const override {
			return m_textures.size() > set_index;
		}

		//	texture_face
		std::uint32_t GetFaceTextureCoordinatesSlotsCount() const override {
			return m_texture_faces.size();
		}

		void SetFaceTextureCoordinates(const std::vector<std::vector<std::array<Math::point2d, 3>>>& value) override {
			m_texture_faces = value;
		}

		void SetFaceTextureCoordinates(std::uint32_t slot, const std::vector<std::array<Math::point2d, 3>>& value) override {
			if (m_texture_faces.size() <= slot)
				m_texture_faces.resize(slot + 1);
			m_texture_faces[slot] = value;
		}

		void SetFaceTextureCoordinate(std::uint32_t slot, std::uint32_t triangle_index, std::uint32_t vertex_index, const Math::point2d& t) override {
			if (m_texture_faces.size() <= slot)
				m_texture_faces.resize(slot + 1);
			if (m_texture_faces[slot].size() <= triangle_index)
				m_texture_faces[slot].resize(triangle_index + 1);
			m_texture_faces[slot][triangle_index][vertex_index] = t;
		}

		const Math::point2d* GetFaceTextureCoordinate(std::uint32_t slot, std::uint32_t triangle_index, int vertex_index) const override {
			return &m_texture_faces.at(slot).at(triangle_index).at(vertex_index);
		}

		bool HasFaceTextureCoordinates() const override {
			return !m_texture_faces.empty();
		}

		//	bone weights
		const Math::vec4* GetVertexBoneWeights(std::uint32_t index) const override {
			return &m_weights[index];
		}

		const Math::ivec4* GetVertexBonesIndecies(std::uint32_t index) const override {
			return &m_bones[index];
		}

		void SetVertexBonesWeight(std::uint32_t index, const Math::vec4& weights, const Math::ivec4& bones) override {
			m_weights[index] = weights;
			m_bones[index] = bones;
		}

		void SetVertexBonesWeights(const std::vector<std::vector<std::pair<int, float>>>& b) override {
			m_weights.resize(b.size());
			m_bones.resize(b.size());
			for (int vertex_index = 0, max_vertex_index = b.size(); vertex_index < max_vertex_index; ++vertex_index) {
				for (int bone_index = 0, max_bone_index = b[vertex_index].size(); bone_index < max_bone_index; ++bone_index) {
					m_bones[vertex_index][bone_index] = b[vertex_index][bone_index].first;
					m_weights[vertex_index][bone_index] = b[vertex_index][bone_index].second;
				}
			}
		}

		bool HasVertexBoneWeights() const override {
			return !m_weights.empty() && !m_bones.empty();
		}

		const Core::String& GetArmatureSchema() const override {
			return m_armature_schema;
		}

		void SetArmatureSchema(Core::String& value) override {
			m_armature_schema = value;
		}

		void SetArmatureOffset(const Math::mat4& value) override {
			m_armature_offset = value;
		}

		const Math::mat4& GetArmatureOffset() const override {
			return m_armature_offset;
		}

		std::uint32_t GetTrianglesCount() const override {
			return m_triangles.size();
		}

		const Math::ivec3* GetTriangle(std::uint32_t index) const override {
			return &m_triangles[index];
		}

		void SetTriangle(std::uint32_t index, const Math::ivec3& value) override {
			m_triangles[index] = value;
		}

		void SetTriangles(const Math::ivec3v& value) override {
			m_triangles = value;
		}

		bool IsIndexed() const override {
			return !m_triangles.empty();
		}

		//	geometry
		bool Validate() override {
			return true;
		}

		std::uint32_t GetVertexCount() override {
			return m_position.size();
		}

		void SetName(const Core::String& value) override {
			m_name = value;
		}

		const Core::String& GetName() const override {
			return m_name;
		}		

	protected:
		GeometryBase(const GeometryBase&) = delete;
		GeometryBase& operator = (const GeometryBase&) = delete;

		std::atomic<std::uint32_t> m_ref_count{ 0 };
		Math::point3dv m_position;
		Math::vec3v m_normals;
		Math::vec4v m_colors;
		std::vector<Math::vec4v> m_textures;
		Math::vec4v m_weights;
		Math::ivec4v m_bones;
		std::vector<std::vector<std::array<Math::point2d, 3>>> m_texture_faces;
		Math::ivec3v m_triangles;
		Core::String m_armature_schema;
		Core::String m_name;
		Math::mat4 m_armature_offset;
		bool m_need_update{ true };		
	};
	
	class PUNK_ENGINE_LOCAL Geometry3D : public GeometryBase
		, public Math::IBoundingBox
		, public Math::IBoundingSphere
		, public Core::ISerializable
	{
	public:
		Geometry3D() {}
		virtual ~Geometry3D() {}

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override {
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
			else if (type == IID_IVertexBoneWeightStream) {
				*object = (void*)(IVertexBoneWeightStream*)this;
				AddRef();
			}
			else if (type == IID_IVertexColorStream) {
				*object = (void*)(IVertexColorStream*)this;
				AddRef();
			}
			else if (type == IID_IVertexNormalStream) {
				*object = (void*)(IVertexNormalStream*)this;
				AddRef();
			}
			else if (type == IID_IVertexPositionStream) {
				*object = (void*)(IVertexPositionStream*)this;
				AddRef();
			}
			else if (type == IID_IVertexTextureCoordinateStream) {
				*object = (void*)(IVertexTextureCoordinateStream*)this;
				AddRef();
			}
			else if (type == IID_IFaceIndexStream) {
				*object = (void*)(IFaceIndexStream*)this;
				AddRef();
			}
			else if (type == IID_IFaceTextureStream) {
				*object = (void*)(IFaceTextureStream*)this;
				AddRef();
			}
			else if (type == Core::IID_ISerializable) {
				*object = (void*)(Core::ISerializable*)this;
				AddRef();
			}
			else
				*object = nullptr;
		}

		std::uint32_t AddRef() override {
			return m_ref_count.fetch_add(1);
		}

		std::uint32_t Release() override {
			auto v = m_ref_count.fetch_sub(1) - 1;
			if (!v) {
				delete this;
			}
			return v;
		}

		//	IVertexPositionStream
		void SetVertexPosition(std::uint32_t index, const Math::point3d& value) override {
			m_position[index] = value;
			m_bbox.Create(m_position);
			m_sphere.Create(m_position);
		}

		//	IBoundingVolume3D
		bool IsPointInside(const Math::point3d& value) override {
			auto res = m_sphere.ClassifyPoint(value);
			return res == Math::Relation::INSIDE;
		}

		bool IsPointInside(const Math::point3d& value, Math::IntersectionHint& hint) override {
			hint = Math::IntersectionHint::No;
			auto res = m_sphere.ClassifyPoint(value);
			if (res == Math::Relation::INSIDE)
				hint = hint | Math::IntersectionHint::BoundingSphere;
			res = m_bbox.ClassifyPoint(value);
			if (res == Math::Relation::INSIDE)
				hint = hint | Math::IntersectionHint::BoundingBox;
			return hint != Math::IntersectionHint::No;
		}

		Core::Pointer<Math::IIntersectionResult> CrossLine(const Math::Line3D& line) override {
			auto result = System::CreateInstancePtr<Math::IIntersectionResult>(Math::CLSID_IntersectionResult, Math::IID_IIntersectionResult);
			Math::point3d p1, p2;
			auto res = m_sphere.CrossLine(line, p1, p2);
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
			res = m_bbox.CrossLine(line, p1);
			if (res == Math::Relation::INTERSECT)
				result->AddIntersectionPoint(p1, Math::IntersectionHint::BoundingBox);
			return result;
		}

		bool CrossFrustum(const Core::Pointer<Math::IFrustum> frust, const Math::mat4& to_frustum_space) override {
			auto sphere = to_frustum_space * m_sphere;
			if (frust->GetClipSpace().ClassifyBoudingSphere(m_sphere) == Math::Relation::NOT_VISIBLE)
				return false;

			auto bbox = to_frustum_space * m_bbox;
			return frust->GetClipSpace().ClassifyBoudingBox(bbox) == Math::Relation::VISIBLE;
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

		//	ISerializable
		void Serialize(Core::Buffer& buffer) override {
			buffer.WriteBuffer(CLSID_Geometry3D.ToPointer(), sizeof(CLSID_Geometry3D));

			//	GeometryBase
			buffer.WriteStdVector(m_position);			
			buffer.WriteStdVector(m_normals);
			buffer.WriteStdVector(m_colors);
			buffer.WriteStdVector(m_textures);
			buffer.WriteStdVector(m_weights);
			buffer.WriteStdVector(m_bones);
			buffer.WriteStdVector(m_texture_faces);
			buffer.WriteStdVector(m_triangles);
			buffer.WriteString(m_armature_schema);
			buffer.WriteString(m_name);
			buffer.WritePod(m_armature_offset);
			buffer.WritePod(m_bbox);
			buffer.WritePod(m_sphere);
		}

		void Deserialize(Core::Buffer& buffer) override {
			buffer.ReadStdVector(m_position);
			buffer.ReadStdVector(m_normals);
			buffer.ReadStdVector(m_colors);
			buffer.ReadStdVector(m_textures);
			buffer.ReadStdVector(m_weights);
			buffer.ReadStdVector(m_bones);
			buffer.ReadStdVector(m_texture_faces);
			buffer.ReadStdVector(m_triangles);
			m_armature_schema = buffer.ReadString();
			m_name = buffer.ReadString();
			buffer.ReadPod(m_armature_offset);
			buffer.ReadPod(m_bbox);
			buffer.ReadPod(m_sphere);
		}

	protected:
		Math::BoundingBox m_bbox;
		Math::BoundingSphere m_sphere;
	};

	

	PUNK_REGISTER_CREATOR(CLSID_Geometry3D, (System::CreateInstance<Geometry3D, IGeometry>));
}
PUNK_ENGINE_END
