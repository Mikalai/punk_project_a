#include <system/factory/module.h>
#include <graphics/module.h>
#include <math/tbn_space.h>
#include "igeometry_cooker.h"
#include "igeometry.h"
#include "icomponent_position.h"
#include "icomponent_bone_weight.h"
#include "icomponent_color.h"
#include "icomponent_normal.h"
#include "icomponent_texture.h"
#include "icomponent_texture_face.h"
#include "icomponent_index.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	class PUNK_ENGINE_LOCAL GeometryCooker : public IGeometryCooker {
	public:

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override {
			Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_IGeometryCooker });
		}

		std::uint32_t AddRef() override {
			return m_ref_count.fetch_add(1);
		}

		std::uint32_t Release() override {
			std::uint32_t v = (m_ref_count.fetch_sub(1) - 1);
			if (!v) {
				delete this;
			}
			return v;
		}

		//	IGeometryCooker
		void EnableTangetBitangentGeneration(bool flag) override {
			m_enable_tbn_generation = flag;
		}

		bool IsEnabledTangentBitangentGeneration() const override {
			return m_enable_tbn_generation;
		}

		void Cook(
			Core::Pointer<IGeometry> geometry,
			Core::Pointer<Graphics::IVertexArray>& va,
			Core::Pointer<Graphics::IIndexArray>& ia) override {

			auto position_stream = Core::QueryInterfacePtr<IVertexPositionStream>(geometry, IID_IVertexPositionStream);
			auto normal_stream = Core::QueryInterfacePtr<IVertexNormalStream>(geometry, IID_IVertexNormalStream);
			auto texture_stream = Core::QueryInterfacePtr<IVertexTextureCoordinateStream>(geometry, IID_IVertexTextureCoordinateStream);
			auto color_stream = Core::QueryInterfacePtr<IVertexColorStream>(geometry, IID_IVertexColorStream);
			auto index_stream = Core::QueryInterfacePtr<IFaceIndexStream>(geometry, IID_IFaceIndexStream);
			auto face_texture_stream = Core::QueryInterfacePtr<IFaceTextureStream>(geometry, IID_IFaceTextureStream);
			auto bone_stream = Core::QueryInterfacePtr<IVertexBoneWeightStream>(geometry, IID_IVertexBoneWeightStream);

			va.reset(nullptr);
			ia.reset(nullptr);

			if (position_stream && position_stream->HasVertexPositions() ) {
				if (normal_stream && normal_stream->HasVertexNormals()) {
					if (face_texture_stream && face_texture_stream->HasFaceTextureCoordinates()) {
						if (bone_stream && bone_stream->HasVertexBoneWeights()) {
							if (m_enable_tbn_generation) {

								CookPositionNormalTangentBitangentTexture0BoneIDBoneWeight(
									position_stream,
									normal_stream,
									texture_stream,
									bone_stream,
									index_stream,
									face_texture_stream,
									va, ia);
								return;
							}
							else {
								CookPositionNormalBonesWeights(
									position_stream,
									normal_stream,
									bone_stream,
									index_stream,
									va, ia);
								System::GetDefaultLogger()->Warning("Position|Normal|Texture|Bone not implemented, use Position|Normal|Bone");
								return;
							}
						}
						else {
							if (m_enable_tbn_generation) {
								CookPositionNormalTangentBitangentTexture0(
									position_stream,
									normal_stream,
									texture_stream,
									index_stream,
									face_texture_stream,
									va, ia);
								return;
							}
							else {
								CookPositionNormalTexture0(
									position_stream,
									normal_stream,
									texture_stream,
									index_stream,
									face_texture_stream, va, ia);
								return;
							}
						}
					}
					else {
						if (bone_stream && bone_stream->HasVertexBoneWeights()) {
							CookPositionNormalBonesWeights(
								position_stream,
								normal_stream,
								bone_stream,
								index_stream,
								va, ia);
							return;
						}
						else {
							CookPositionNormal(
								position_stream,
								normal_stream,
								index_stream,
								va, ia);
							return;
						}
					}
				}
				else { //	Position !Normal
					if (face_texture_stream && face_texture_stream->HasFaceTextureCoordinates()) {	//Position !Normal Texture
						CookPositionTexture0(
							position_stream,
							texture_stream,
							index_stream,
							face_texture_stream,
							va, ia);
						return;
					}
					else {	//	Position !Normal !Texture
						CookPosition(
							position_stream,
							index_stream,
							va, ia);
						return;
					}
				}
			}
			throw System::Error::SystemException("Can't cook vertex buffers from specified data");
		}

	private:

		void CookPositionNormalTangentBitangentTexture0(
			Core::Pointer<IVertexPositionStream> position_stream,
			Core::Pointer<IVertexNormalStream> normal_stream,
			Core::Pointer<IVertexTextureCoordinateStream> texture_stream,
			Core::Pointer<IFaceIndexStream> index_stream,
			Core::Pointer<IFaceTextureStream> face_texture_stream,
			Core::Pointer<Graphics::IVertexArray>& va,
			Core::Pointer<Graphics::IIndexArray>& ia) {

			using namespace Graphics;

			using CurrentVertex = Vertex < VertexComponent::Position,
				VertexComponent::Normal,
				VertexComponent::Tangent,
				VertexComponent::Bitangent,
				VertexComponent::Texture0 > ;

			if (!position_stream->HasVertexPositions())
				throw System::Error::SystemException(L"Can't create static mesh from empty vertex list in mesh descriptor");
			if (!texture_stream->HasVertexTextureCoordinates())
				throw System::Error::SystemException(L"Can't create static mesh from empty texture list in mesh descriptor");
			if (!face_texture_stream->HasFaceTextureCoordinates())
				throw System::Error::SystemException(L"Can't create static mesh from mesh descriptor with empty texture coordinates list");
			if (!normal_stream->HasVertexNormals())
				throw System::Error::SystemException(L"Can't create static mesh from mesh descriptor with empty normals list");
			if (!index_stream)
				throw System::Error::SystemException(L"Can't create vertex buffer because information about faces is not available");

			std::vector<unsigned> ib;
			if (index_stream->IsIndexed()) {
				int index = 0;
				ib.resize(index_stream->GetTrianglesCount() * 3);
				for (unsigned i = 0; i < index_stream->GetTrianglesCount(); i++) {
					const Math::ivec3* t = index_stream->GetTriangle(i);
					ib[3 * i + 0] = index++;
					ib[3 * i + 1] = index++;
					ib[3 * i + 2] = index++;
				}
			}

			std::vector<CurrentVertex> vb(index_stream->GetTrianglesCount() * 3);

			std::vector<int> base_index;		/// contains vertex index in the source array
			int index = 0;
			for (unsigned i = 0, max_i = index_stream->GetTrianglesCount(); i < max_i; i++)
			{
				const Math::ivec3* f = index_stream->GetTriangle(i);
				const Math::point3d* position[3] = { position_stream->GetVertexPosition(f->X()), position_stream->GetVertexPosition(f->Y()), position_stream->GetVertexPosition(f->Z()) };
				const Math::point2d* texture[3] = { face_texture_stream->GetFaceTextureCoordinate(0, i, 0), face_texture_stream->GetFaceTextureCoordinate(0, i, 1), face_texture_stream->GetFaceTextureCoordinate(0, i, 2) };
				const Math::vec3* normal[3] = { normal_stream->GetVertexNormal(f->X()), normal_stream->GetVertexNormal(f->Y()), normal_stream->GetVertexNormal(f->Z()) };

				Math::vec3 tgn;
				Math::vec3 nrm;
				Math::vec3 btn;
				float det;

				for (int j = 0; j < 3; ++j)
				{
					int index_0 = j;
					int index_1 = (j + 1) % 3;
					int index_2 = (j + 2) % 3;

					Math::CalculateTBN(*position[index_0], *position[index_1], *position[index_2], *texture[index_0], *texture[index_1], *texture[index_2], tgn, btn, nrm, det);

					det = (det < 0) ? -1.0f : 1.0f;

					vb[index].m_position = *position[index_0];
					vb[index].m_normal = *normal[index_0];
					vb[index].m_texture0.Set(texture[index_0]->X(), texture[index_0]->Y(), 0, 0);
					vb[index].m_tangent.Set(tgn.X(), tgn.Y(), tgn.Z(), det);
					vb[index].m_bitangent.Set(btn.X(), btn.Y(), btn.Z(), 0);
					base_index.push_back((*f)[j]);
					index++;
				}
			}

			/// Smooth TBN
			std::vector<int> mask(vb.size());
			for (int i = 0; i < (int)vb.size(); i++)
			{
				Math::vec3 norm;
				Math::vec3 tang;
				Math::vec3 btan;
				for (int j = 0; j < (int)vb.size(); j++)
				{
					CurrentVertex* v = &vb[j];
					if (base_index[j] == i)
					{
						norm += v->m_normal.XYZ();
						tang += v->m_tangent.XYZ();
						btan += v->m_bitangent.XYZ();
					}
				}

				norm.Normalize();
				tang.Normalize();
				btan.Normalize();
				tang = (tang - norm.Dot(tang)*norm).Normalized();
				btan = (btan - norm.Dot(btan)*norm - tang.Dot(btan)*tang).Normalized();

				Math::mat3 m;
				m.at(0, 0) = tang[0]; m.at(0, 1) = tang[1]; m.at(0, 2) = tang[2];
				m.at(1, 0) = btan[0]; m.at(1, 1) = btan[1]; m.at(1, 2) = btan[2];
				m.at(2, 0) = norm[0]; m.at(2, 1) = norm[1]; m.at(2, 2) = norm[2];
				float w = m.Determinant();

				for (int j = 0; j < (int)vb.size(); j++)
				{
					CurrentVertex* v = &vb[j];
					if (base_index[j] == i)
					{
						v->m_normal = norm;
						v->m_tangent.Set(tang[0], tang[1], tang[2], w);
						v->m_bitangent = btan;
					}
				}
			}

			va.reset(new VertexArray<CurrentVertex>(vb));
			if (index_stream->IsIndexed())
				ia.reset(new IndexArray<unsigned>(ib));
		}

		void CookPositionNormal(
			Core::Pointer<IVertexPositionStream> position_stream,
			Core::Pointer<IVertexNormalStream> normal_stream,
			Core::Pointer<IFaceIndexStream> index_stream,
			Core::Pointer<Graphics::IVertexArray>& _vb, Core::Pointer<Graphics::IIndexArray>& _ib) {
			using namespace Graphics;
			using CurrentVertex = Vertex < VertexComponent::Position, VertexComponent::Normal > ;

			if (!position_stream->HasVertexPositions())
				throw System::Error::SystemException(L"Can't create static mesh from empty vertex list in mesh descriptor");
			if (!normal_stream->HasVertexNormals())
				throw System::Error::SystemException(L"Can't create static mesh from mesh descriptor with empty normals list");

			std::vector<unsigned> ib;
			if (index_stream->IsIndexed()) {
				int index = 0;
				ib.resize(index_stream->GetTrianglesCount() * 3);
				for (unsigned i = 0; i < index_stream->GetTrianglesCount(); i++) {
					const Math::ivec3* t = index_stream->GetTriangle(i);
					ib[3 * i + 0] = index++;
					ib[3 * i + 1] = index++;
					ib[3 * i + 2] = index++;
				}
			}

			std::vector<CurrentVertex> vb(index_stream->GetTrianglesCount() * 3);

			std::vector<int> base_index;		/// contains vertex index in the source array
			int index = 0;
			for (unsigned i = 0, max_i = index_stream->GetTrianglesCount(); i < max_i; i++)
			{
				const Math::ivec3* f = index_stream->GetTriangle(i);
				const Math::point3d* position[3] = { position_stream->GetVertexPosition(f->X()), position_stream->GetVertexPosition(f->Y()), position_stream->GetVertexPosition(f->Z()) };
				const Math::vec3* normal[3] = { normal_stream->GetVertexNormal(f->X()), normal_stream->GetVertexNormal(f->Y()), normal_stream->GetVertexNormal(f->Z()) };

				for (int j = 0; j < 3; ++j)
				{
					vb[index].m_position = *position[j];
					vb[index].m_normal = *normal[j];
					base_index.push_back((*f)[j]);
					index++;
				}
			}

			/// Smooth TBN
			std::vector<int> mask(vb.size());
			for (int i = 0; i < (int)vb.size(); i++)
			{
				Math::vec3 norm;
				for (int j = 0; j < (int)vb.size(); j++)
				{
					CurrentVertex* v = &vb[j];
					if (base_index[j] == i)
					{
						norm += v->m_normal.XYZ();
					}
				}

				norm.Normalize();

				for (int j = 0; j < (int)vb.size(); j++)
				{
					CurrentVertex* v = &vb[j];
					if (base_index[j] == i)
					{
						v->m_normal = norm;
					}
				}
			}

			_vb.reset(new VertexArray<CurrentVertex>(vb));
			if (index_stream->IsIndexed())
				_ib.reset(new IndexArray<unsigned>(ib));
		}

		void CookPosition(
			Core::Pointer<IVertexPositionStream> position_stream,
			Core::Pointer<IFaceIndexStream> index_stream,
			Core::Pointer<Graphics::IVertexArray>& _vb, Core::Pointer<Graphics::IIndexArray>& _ib) {
			using namespace Graphics;
			using CurrentVertex = Vertex < VertexComponent::Position > ;

			if (!position_stream->HasVertexPositions())
				throw System::Error::SystemException(L"Can't create static mesh from empty vertex list in mesh descriptor");

			std::vector<unsigned> ib;
			if (index_stream->IsIndexed()) {
				int index = 0;
				ib.resize(index_stream->GetTrianglesCount() * 3);
				for (unsigned i = 0; i < index_stream->GetTrianglesCount(); i++) {
					const Math::ivec3* t = index_stream->GetTriangle(i);
					ib[3 * i + 0] = index++;
					ib[3 * i + 1] = index++;
					ib[3 * i + 2] = index++;
				}
			}

			std::vector<CurrentVertex> vb(index_stream->GetTrianglesCount() * 3);

			std::vector<int> base_index;		/// contains vertex index in the source array
			int index = 0;
			for (unsigned i = 0, max_i = index_stream->GetTrianglesCount(); i < max_i; i++)
			{
				const Math::ivec3* f = index_stream->GetTriangle(i);
				const Math::point3d* position[3] = { position_stream->GetVertexPosition(f->X()), position_stream->GetVertexPosition(f->Y()), position_stream->GetVertexPosition(f->Z()) };

				for (int j = 0; j < 3; ++j)
				{
					vb[index].m_position = *position[j];
					base_index.push_back((*f)[j]);
					index++;
				}
			}

			_vb.reset(new VertexArray<CurrentVertex>(vb));
			if (index_stream->IsIndexed())
				_ib.reset(new IndexArray<unsigned>(ib));
		}

		void CookPositionTexture0(
			Core::Pointer<IVertexPositionStream> position_stream,			
			Core::Pointer<IVertexTextureCoordinateStream> texture_stream,
			Core::Pointer<IFaceIndexStream> index_stream,
			Core::Pointer<IFaceTextureStream> face_texture_stream,
			Core::Pointer<Graphics::IVertexArray>& _vb, Core::Pointer<Graphics::IIndexArray>& _ib) {
			using namespace Graphics;
			using CurrentVertex = Vertex < VertexComponent::Position, VertexComponent::Texture0 > ;

			if (!position_stream->HasVertexPositions())
				throw System::Error::SystemException(L"Can't create static mesh from empty vertex list in mesh descriptor");
			if (!face_texture_stream->HasFaceTextureCoordinates())
				throw System::Error::SystemException(L"Can't create static mesh from mesh descriptor with empty texture coordinates list");

			std::vector<unsigned> ib;
			if (index_stream->IsIndexed()) {
				int index = 0;
				ib.resize(index_stream->GetTrianglesCount() * 3);
				for (unsigned i = 0; i < index_stream->GetTrianglesCount(); i++) {
					const Math::ivec3* t = index_stream->GetTriangle(i);
					ib[3 * i + 0] = index++;
					ib[3 * i + 1] = index++;
					ib[3 * i + 2] = index++;
				}
			}

			std::vector<CurrentVertex> vb(index_stream->GetTrianglesCount());

			std::vector<int> base_index;		/// contains vertex index in the source array
			int index = 0;
			for (unsigned i = 0, max_i = index_stream->GetTrianglesCount(); i < max_i; i++)
			{
				const Math::ivec3* f = index_stream->GetTriangle(i);
				const Math::point3d* position[3] = { position_stream->GetVertexPosition(f->X()), position_stream->GetVertexPosition(f->Y()), position_stream->GetVertexPosition(f->Z()) };
				const Math::point2d* texture[3] = { face_texture_stream->GetFaceTextureCoordinate(0, i, 0), face_texture_stream->GetFaceTextureCoordinate(0, i, 1), face_texture_stream->GetFaceTextureCoordinate(0, i, 2) };


				for (int j = 0; j < 3; ++j)
				{
					vb[index].m_position = *position[j];
					vb[index].m_texture0.Set(texture[j]->X(), texture[j]->Y(), 0, 0);
					base_index.push_back((*f)[j]);
					index++;
				}
			}

			_vb.reset(new VertexArray<CurrentVertex>(vb));
			if (index_stream->IsIndexed())
				_ib.reset(new IndexArray<unsigned>(ib));
		}


		void CookPositionNormalTexture0(
			Core::Pointer<IVertexPositionStream> position_stream,
			Core::Pointer<IVertexNormalStream> normal_stream,
			Core::Pointer<IVertexTextureCoordinateStream> texture_stream,
			Core::Pointer<IFaceIndexStream> index_stream,
			Core::Pointer<IFaceTextureStream> face_texture_stream,
			Core::Pointer<Graphics::IVertexArray>& _vb, Core::Pointer<Graphics::IIndexArray>& _ib) {

			using namespace Graphics;
			using CurrentVertex = Vertex < VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0 > ;

			if (!position_stream->HasVertexPositions())
				throw System::Error::SystemException(L"Can't create static mesh from empty vertex list in mesh descriptor");
			if (!face_texture_stream->HasFaceTextureCoordinates())
				throw System::Error::SystemException(L"Can't create static mesh from mesh descriptor with empty texture coordinates list");
			if (!normal_stream->HasVertexNormals())
				throw System::Error::SystemException(L"Can't create static mesh from mesh descriptor with empty normals list");


			std::vector<unsigned> ib;
			if (index_stream->IsIndexed()) {
				int index = 0;
				ib.resize(index_stream->GetTrianglesCount() * 3);
				for (unsigned i = 0; i < index_stream->GetTrianglesCount(); i++) {
					const Math::ivec3* t = index_stream->GetTriangle(i);
					ib[3 * i + 0] = index++;
					ib[3 * i + 1] = index++;
					ib[3 * i + 2] = index++;
				}
			}

			std::vector<CurrentVertex> vb(index_stream->GetTrianglesCount() * 3);

			std::vector<int> base_index;		/// contains vertex index in the source array
			int index = 0;
			for (unsigned i = 0, max_i = index_stream->GetTrianglesCount(); i < max_i; i++)
			{
				const Math::ivec3* f = index_stream->GetTriangle(i);
				const Math::point3d* position[3] = { position_stream->GetVertexPosition(f->X()), position_stream->GetVertexPosition(f->Y()), position_stream->GetVertexPosition(f->Z()) };
				const Math::point2d* texture[3] = { face_texture_stream->GetFaceTextureCoordinate(0, i, 0), face_texture_stream->GetFaceTextureCoordinate(0, i, 1), face_texture_stream->GetFaceTextureCoordinate(0, i, 2) };
				const Math::vec3* normal[3] = { normal_stream->GetVertexNormal(f->X()), normal_stream->GetVertexNormal(f->Y()), normal_stream->GetVertexNormal(f->Z()) };

				for (int j = 0; j < 3; ++j)
				{
					vb[index].m_position = *position[j];
					vb[index].m_normal = *normal[j];
					vb[index].m_texture0.Set(texture[j]->X(), texture[j]->Y(), 0, 0);
					base_index.push_back((*f)[j]);
					index++;
				}
			}

			/// Smooth TBN
			std::vector<int> mask(vb.size());
			for (int i = 0; i < (int)vb.size(); i++)
			{
				Math::vec3 norm;
				for (int j = 0; j < (int)vb.size(); j++)
				{
					CurrentVertex* v = &vb[j];
					if (base_index[j] == i)
					{
						norm += v->m_normal.XYZ();
					}
				}

				norm.Normalize();

				for (int j = 0; j < (int)vb.size(); j++)
				{
					CurrentVertex* v = &vb[j];
					if (base_index[j] == i)
					{
						v->m_normal = norm;
					}
				}
			}

			_vb.reset(new VertexArray<CurrentVertex>(vb));
			if (index_stream->IsIndexed())
				_ib.reset(new IndexArray<unsigned>(ib));
		}

		void CookPositionNormalBonesWeights(
			Core::Pointer<IVertexPositionStream> position_stream,
			Core::Pointer<IVertexNormalStream> normal_stream,
			Core::Pointer<IVertexBoneWeightStream> bone_weight_stream,
			Core::Pointer<IFaceIndexStream> index_stream,
			Core::Pointer<Graphics::IVertexArray>& _vb, Core::Pointer<Graphics::IIndexArray>& _ib) {
			using namespace Graphics;
			using CurrentVertex = Vertex < VertexComponent::Position,
				VertexComponent::Normal,
				VertexComponent::BoneID,
				VertexComponent::BoneWeight > ;

			if (!position_stream->HasVertexPositions())
				throw System::Error::SystemException(L"Can't create skinned mesh from empty vertex list in mesh descriptor");
			if (!normal_stream->HasVertexNormals())
				throw System::Error::SystemException(L"Can't create skinned mesh from mesh descriptor with empty normals list");
			if (!bone_weight_stream->HasVertexBoneWeights())
				throw System::Error::SystemException(L"Can't create skinned mesh from mesh descriptor with empty bones weights list");

			std::vector<unsigned> ib;
			if (index_stream->IsIndexed()) {
				int index = 0;
				ib.resize(index_stream->GetTrianglesCount() * 3);
				for (unsigned i = 0; i < index_stream->GetTrianglesCount(); i++) {
					const Math::ivec3* t = index_stream->GetTriangle(i);
					ib[3 * i + 0] = index++;
					ib[3 * i + 1] = index++;
					ib[3 * i + 2] = index++;
				}
			}

			std::vector<CurrentVertex> vb(index_stream->GetTrianglesCount() * 3);

			std::vector<int> base_index;		/// contains vertex index in the source array
			int index = 0;
			for (unsigned i = 0, max_i = index_stream->GetTrianglesCount(); i < max_i; i++)
			{
				const Math::ivec3* f = index_stream->GetTriangle(i);
				const Math::point3d* position[3] = { position_stream->GetVertexPosition(f->X()), position_stream->GetVertexPosition(f->Y()), position_stream->GetVertexPosition(f->Z()) };
				const Math::vec3* normal[3] = { normal_stream->GetVertexNormal(f->X()), normal_stream->GetVertexNormal(f->Y()), normal_stream->GetVertexNormal(f->Z()) };

				Math::vec3 tgn;
				Math::vec3 nrm;
				Math::vec3 btn;
				float det;

				//	for each vertex in the triangle
				for (int j = 0; j < 3; ++j)
				{
					int index_0 = j;
					int index_1 = (j + 1) % 3;
					int index_2 = (j + 2) % 3;

					vb[index].m_position = *position[index_0];
					vb[index].m_normal = *normal[index_0];

					CookOneVertexWithBone(bone_weight_stream, (*f)[j], vb[index].m_bone_id, vb[index].m_bone_weight);

					base_index.push_back((*f)[j]);
					index++;
				}
			}

			/// Smooth TBN
			std::vector<int> mask(vb.size());
			for (int i = 0; i < (int)vb.size(); i++)
			{
				Math::vec3 norm;
				Math::vec3 tang;
				Math::vec3 btan;
				for (int j = 0; j < (int)vb.size(); j++)
				{
					CurrentVertex* v = &vb[j];
					if (base_index[j] == i)
					{
						norm += v->m_normal.XYZ();
					}
				}

				norm.Normalize();

				for (int j = 0; j < (int)vb.size(); j++)
				{
					CurrentVertex* v = &vb[j];
					if (base_index[j] == i)
					{
						v->m_normal = norm;
					}
				}
			}

			_vb.reset(new VertexArray<CurrentVertex>(vb));
			if (index_stream->IsIndexed())
				_ib.reset(new IndexArray<unsigned>(ib));

		}

		void CookPositionNormalTangentBitangentTexture0BoneIDBoneWeight(
			Core::Pointer<IVertexPositionStream> position_stream,
			Core::Pointer<IVertexNormalStream> normal_stream,
			Core::Pointer<IVertexTextureCoordinateStream> texture_stream,
			Core::Pointer<IVertexBoneWeightStream> bone_weight_stream,
			Core::Pointer<IFaceIndexStream> index_stream,
			Core::Pointer<IFaceTextureStream> face_texture_stream,
			Core::Pointer<Graphics::IVertexArray>& _vb, Core::Pointer<Graphics::IIndexArray>& _ib) {
			using namespace Graphics;
			using CurrentVertex = Vertex < VertexComponent::Position,
				VertexComponent::Normal,
				VertexComponent::Tangent,
				VertexComponent::Bitangent,
				VertexComponent::Texture0,
				VertexComponent::BoneID,
				VertexComponent::BoneWeight > ;

			if (!position_stream->HasVertexPositions())
				throw System::Error::SystemException(L"Can't create skinned mesh from empty vertex list in mesh descriptor");
			if (!face_texture_stream->HasFaceTextureCoordinates())
				throw System::Error::SystemException(L"Can't create skinned mesh from mesh descriptor with empty texture coordinates list");
			if (!normal_stream->HasVertexNormals())
				throw System::Error::SystemException(L"Can't create skinned mesh from mesh descriptor with empty normals list");
			if (!bone_weight_stream->HasVertexBoneWeights())
				throw System::Error::SystemException(L"Can't create skinned mesh from mesh descriptor with empty bones weights list");

			std::vector<unsigned> ib;
			if (index_stream->IsIndexed()) {
				int index = 0;
				ib.resize(index_stream->GetTrianglesCount() * 3);
				for (unsigned i = 0; i < index_stream->GetTrianglesCount(); i++) {
					const Math::ivec3* t = index_stream->GetTriangle(i);
					ib[3 * i + 0] = index++;
					ib[3 * i + 1] = index++;
					ib[3 * i + 2] = index++;
				}
			}

			std::vector<CurrentVertex> vb(index_stream->GetTrianglesCount() * 3);

			std::vector<int> base_index;		/// contains vertex index in the source array
			int index = 0;
			for (unsigned i = 0, max_i = index_stream->GetTrianglesCount(); i < max_i; i++)
			{
				const Math::ivec3* f = index_stream->GetTriangle(i);
				const Math::point3d* position[3] = { position_stream->GetVertexPosition(f->X()), position_stream->GetVertexPosition(f->Y()), position_stream->GetVertexPosition(f->Z()) };
				const Math::point2d* texture[3] = { face_texture_stream->GetFaceTextureCoordinate(0, i, 0), face_texture_stream->GetFaceTextureCoordinate(0, i, 1), face_texture_stream->GetFaceTextureCoordinate(0, i, 2) };
				const Math::vec3* normal[3] = { normal_stream->GetVertexNormal(f->X()), normal_stream->GetVertexNormal(f->Y()), normal_stream->GetVertexNormal(f->Z()) };

				Math::vec3 tgn;
				Math::vec3 nrm;
				Math::vec3 btn;
				float det;

				//	for each vertex in the triangle
				for (int j = 0; j < 3; ++j)
				{
					int index_0 = j;
					int index_1 = (j + 1) % 3;
					int index_2 = (j + 2) % 3;

					Math::CalculateTBN(*position[index_0], *position[index_1], *position[index_2], *texture[index_0], *texture[index_1], *texture[index_2], tgn, btn, nrm, det);
					det = (det < 0) ? -1.0f : 1.0f;

					vb[index].m_position = *position[index_0];
					vb[index].m_normal = *normal[index_0];
					vb[index].m_texture0.Set(texture[index_0]->X(), texture[index_0]->Y(), 0, 0);
					vb[index].m_tangent.Set(tgn[0], tgn[1], tgn[2], det);
					vb[index].m_bitangent.Set(btn[0], btn[1], btn[2], 0);

					CookOneVertexWithBone(bone_weight_stream, (*f)[j], vb[index].m_bone_id, vb[index].m_bone_weight);

					base_index.push_back((*f)[j]);
					index++;
				}
			}

			/// Smooth TBN
			std::vector<int> mask(vb.size());
			for (int i = 0; i < (int)vb.size(); i++)
			{
				Math::vec3 norm;
				Math::vec3 tang;
				Math::vec3 btan;
				for (int j = 0; j < (int)vb.size(); j++)
				{
					CurrentVertex* v = &vb[j];
					if (base_index[j] == i)
					{
						norm += v->m_normal.XYZ();
						tang += v->m_tangent.XYZ();
						btan += v->m_bitangent.XYZ();
					}
				}

				norm.Normalize();
				tang.Normalize();
				btan.Normalize();
				tang = (tang - norm.Dot(tang)*norm).Normalized();
				btan = (btan - norm.Dot(btan)*norm - tang.Dot(btan)*tang).Normalized();

				Math::mat3 m;
				m.at(0, 0) = tang[0]; m.at(0, 1) = tang[1]; m.at(0, 2) = tang[2];
				m.at(1, 0) = btan[0]; m.at(1, 1) = btan[1]; m.at(1, 2) = btan[2];
				m.at(2, 0) = norm[0]; m.at(2, 1) = norm[1]; m.at(2, 2) = norm[2];
				float w = m.Determinant();

				for (int j = 0; j < (int)vb.size(); j++)
				{
					CurrentVertex* v = &vb[j];
					if (base_index[j] == i)
					{
						v->m_normal = norm;
						v->m_tangent.Set(tang[0], tang[1], tang[2], w);
						v->m_bitangent = btan;
					}
				}
			}

			_vb.reset(new VertexArray<CurrentVertex>(vb));
			if (index_stream->IsIndexed())
				_ib.reset(new IndexArray<unsigned>(ib));

		}


		//	skinning
		void CookOneVertexWithBone(const Core::Pointer<IVertexBoneWeightStream> bone_stream, int index, Math::vec4& bone, Math::vec4& weight) {
			Math::vec4 bone_weights = *bone_stream->GetVertexBoneWeights(index);
			Math::ivec4 bone_indecies = *bone_stream->GetVertexBonesIndecies(index);
			//	normalize
			bone_weights.Normalize();
			weight = bone_weights;
			bone.Set((float)bone_indecies[0], (float)bone_indecies[1], (float)bone_indecies[2], (float)bone_indecies[3]);
		}


	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		bool m_enable_tbn_generation{ false };
	};

	PUNK_REGISTER_CREATOR(CLSID_GeometryCooker, (System::CreateInstance<GeometryCooker, IGeometryCooker>));
}
PUNK_ENGINE_END
