#include <system/factory/module.h>
#include <graphics/module.h>
#include "geometry_cooker.h"
#include "igeometry.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	void GeometryCooker::QueryInterface(const Core::Guid& type, void** object) {
		Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_IGeometryCooker });
	}

	std::uint32_t GeometryCooker::AddRef() {
		return m_ref_count.fetch_add(1);
	}

	std::uint32_t GeometryCooker::Release() {
		std::uint32_t v = (m_ref_count.fetch_sub(1) - 1);
		if (!v) {
			delete this;
		}
		return v;
	}

	void GeometryCooker::Cook(IGeometry* mesh, 
		Graphics::IVertexArray*& vb, 
		Graphics::IIndexArray*& ib) {

		vb = nullptr;
		ib = nullptr;
		if (mesh->HasVertexPositions() && mesh->HasFaceTextureCoordinates() && mesh->HasVertexNormals())
			CookPositionNormalTangentBitangentTexture0(mesh, vb, ib);
		else if (mesh->HasVertexPositions() && mesh->HasVertexNormals() && mesh->HasVertexBoneWeights())
			CookPositionNormalBonesWeights(mesh, vb, ib);
		else if (mesh->HasVertexPositions() && mesh->HasFaceTextureCoordinates())
			CookPositionTexture0(mesh, vb, ib);
		else if (mesh->HasVertexPositions() && mesh->HasVertexNormals())
			CookPositionNormal(mesh, vb, ib);
		else if (mesh->HasVertexPositions())
			CookPosition(mesh, vb, ib);		
	}

	void GeometryCooker::CookPositionNormalTangentBitangentTexture0(IGeometry* mesh,
		Graphics::IVertexArray*& _vb,
		Graphics::IIndexArray*& _ib)
	{
		using namespace Graphics;

		using CurrentVertex = Vertex < VertexComponent::Position,
			VertexComponent::Normal,
			VertexComponent::Tangent,
			VertexComponent::Bitangent,
			VertexComponent::Texture0 > ;

		if (!mesh->HasVertexPositions())
			throw System::Error::SystemException(L"Can't create static mesh from empty vertex list in mesh descriptor");
		if (!mesh->HasFaceTextureCoordinates())
			throw System::Error::SystemException(L"Can't create static mesh from mesh descriptor with empty texture coordinates list");
		if (!mesh->HasVertexNormals())
			throw System::Error::SystemException(L"Can't create static mesh from mesh descriptor with empty normals list");

		std::vector<unsigned> ib;
		if (mesh->IsIndexed()) {
			int index = 0;
			ib.resize(mesh->GetTrianglesCount() * 3);
			for (unsigned i = 0; i < mesh->GetTrianglesCount(); i++) {
				const Math::ivec3* t = mesh->GetTriangle(i);
				ib[3 * i + 0] = index++;
				ib[3 * i + 1] = index++;
				ib[3 * i + 2] = index++;
			}
		}

		std::vector<CurrentVertex> vb(mesh->GetTrianglesCount() * 3);

		std::vector<int> base_index;		/// contains vertex index in the source array
		int index = 0;
		for (unsigned i = 0, max_i = mesh->GetTrianglesCount(); i < max_i; i++)
		{
			const Math::ivec3* f = mesh->GetTriangle(i);
			const Math::vec3* position[3] = { mesh->GetVertexPosition(f->X()), mesh->GetVertexPosition(f->Y()), mesh->GetVertexPosition(f->Z()) };
			const Math::vec2* texture[3] = { mesh->GetFaceTextureCoordinate(0, i, 0), mesh->GetFaceTextureCoordinate(0, i, 1), mesh->GetFaceTextureCoordinate(0, i, 2) };
			const Math::vec3* normal[3] = { mesh->GetVertexNormal(f->X()), mesh->GetVertexNormal(f->Y()), mesh->GetVertexNormal(f->Z()) };

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

			Math::Matrix<float> m(3, 3);
			m.At(0, 0) = tang[0]; m.At(0, 1) = tang[1]; m.At(0, 2) = tang[2];
			m.At(1, 0) = btan[0]; m.At(1, 1) = btan[1]; m.At(1, 2) = btan[2];
			m.At(2, 0) = norm[0]; m.At(2, 1) = norm[1]; m.At(2, 2) = norm[2];
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

		_vb = new VertexArray<CurrentVertex>(vb);
		if (mesh->IsIndexed())
			_ib = new IndexArray<unsigned>(ib);
	}

	void GeometryCooker::CookPositionNormal(IGeometry* mesh,
		Graphics::IVertexArray*& _vb,
		Graphics::IIndexArray*& _ib)
	{
		using namespace Graphics;
		using CurrentVertex = Vertex<VertexComponent::Position, VertexComponent::Normal>;

		if (!mesh->HasVertexPositions())
			throw System::Error::SystemException(L"Can't create static mesh from empty vertex list in mesh descriptor");
		if (!mesh->HasVertexNormals())
			throw System::Error::SystemException(L"Can't create static mesh from mesh descriptor with empty normals list");

		std::vector<unsigned> ib;
		if (mesh->IsIndexed()) {
			int index = 0;
			ib.resize(mesh->GetTrianglesCount() * 3);
			for (unsigned i = 0; i < mesh->GetTrianglesCount(); i++) {
				const Math::ivec3* t = mesh->GetTriangle(i);
				ib[3 * i + 0] = index++;
				ib[3 * i + 1] = index++;
				ib[3 * i + 2] = index++;
			}
		}

		std::vector<CurrentVertex> vb(mesh->GetTrianglesCount() * 3);

		std::vector<int> base_index;		/// contains vertex index in the source array
		int index = 0;
		for (unsigned i = 0, max_i = mesh->GetTrianglesCount(); i < max_i; i++)
		{
			const Math::ivec3* f = mesh->GetTriangle(i);
			const Math::vec3* position[3] = { mesh->GetVertexPosition(f->X()), mesh->GetVertexPosition(f->Y()), mesh->GetVertexPosition(f->Z()) };
			const Math::vec3* normal[3] = { mesh->GetVertexNormal(f->X()), mesh->GetVertexNormal(f->Y()), mesh->GetVertexNormal(f->Z()) };			

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

		_vb = new VertexArray<CurrentVertex>(vb);
		if (mesh->IsIndexed())
			_ib = new IndexArray<unsigned>(ib);
	}

	void GeometryCooker::CookPosition(IGeometry* mesh,
		Graphics::IVertexArray*& _vb,
		Graphics::IIndexArray*& _ib)
	{
		using namespace Graphics;
		using CurrentVertex = Vertex<VertexComponent::Position>;

		if (!mesh->HasVertexPositions())
			throw System::Error::SystemException(L"Can't create static mesh from empty vertex list in mesh descriptor");

		std::vector<unsigned> ib;
		if (mesh->IsIndexed()) {
			int index = 0;
			ib.resize(mesh->GetTrianglesCount() * 3);
			for (unsigned i = 0; i < mesh->GetTrianglesCount(); i++) {
				const Math::ivec3* t = mesh->GetTriangle(i);
				ib[3 * i + 0] = index++;
				ib[3 * i + 1] = index++;
				ib[3 * i + 2] = index++;
			}
		}

		std::vector<CurrentVertex> vb(mesh->GetTrianglesCount() * 3);

		std::vector<int> base_index;		/// contains vertex index in the source array
		int index = 0;
		for (unsigned i = 0, max_i = mesh->GetTrianglesCount(); i < max_i; i++)
		{
			const Math::ivec3* f = mesh->GetTriangle(i);
			const Math::vec3* position[3] = { mesh->GetVertexPosition(f->X()), mesh->GetVertexPosition(f->Y()), mesh->GetVertexPosition(f->Z()) };

			for (int j = 0; j < 3; ++j)
			{
				vb[index].m_position = *position[j];
				base_index.push_back((*f)[j]);
				index++;
			}
		}

		_vb = new VertexArray<CurrentVertex>(vb);
		if (mesh->IsIndexed())
			_ib = new IndexArray<unsigned>(ib);
	}

	void GeometryCooker::CookPositionTexture0(IGeometry* mesh
		, Graphics::IVertexArray*& _vb
		, Graphics::IIndexArray*& _ib)
	{
		using namespace Graphics;
		using CurrentVertex = Vertex<VertexComponent::Position, VertexComponent::Texture0>;

		if (!mesh->HasVertexPositions())
			throw System::Error::SystemException(L"Can't create static mesh from empty vertex list in mesh descriptor");
		if (!mesh->HasFaceTextureCoordinates())
			throw System::Error::SystemException(L"Can't create static mesh from mesh descriptor with empty texture coordinates list");

		std::vector<unsigned> ib;
		if (mesh->IsIndexed()) {
			int index = 0;
			ib.resize(mesh->GetTrianglesCount() * 3);
			for (unsigned i = 0; i < mesh->GetTrianglesCount(); i++) {
				const Math::ivec3* t = mesh->GetTriangle(i);
				ib[3 * i + 0] = index++;
				ib[3 * i + 1] = index++;
				ib[3 * i + 2] = index++;
			}
		}

		std::vector<CurrentVertex> vb(mesh->GetTrianglesCount());

		std::vector<int> base_index;		/// contains vertex index in the source array
		int index = 0;
		for (unsigned i = 0, max_i = mesh->GetTrianglesCount(); i < max_i; i++)
		{
			const Math::ivec3* f = mesh->GetTriangle(i);
			const Math::vec3* position[3] = { mesh->GetVertexPosition(f->X()), mesh->GetVertexPosition(f->Y()), mesh->GetVertexPosition(f->Z()) };
			const Math::vec2* texture[3] = { mesh->GetFaceTextureCoordinate(0, i, 0), mesh->GetFaceTextureCoordinate(0, i, 1), mesh->GetFaceTextureCoordinate(0, i, 2) };


			for (int j = 0; j < 3; ++j)
			{
				vb[index].m_position = *position[j];
				vb[index].m_texture0.Set(texture[j]->X(), texture[j]->Y(), 0, 0);
				base_index.push_back((*f)[j]);
				index++;
			}
		}

		_vb = new VertexArray<CurrentVertex>(vb);
		if (mesh->IsIndexed())
			_ib = new IndexArray<unsigned>(ib);
	}

	void GeometryCooker::CookPositionNormalTexture0(IGeometry* mesh,
		Graphics::IVertexArray*& _vb,
		Graphics::IIndexArray*& _ib)
	{
		using namespace Graphics;
		using CurrentVertex = Vertex<VertexComponent::Position, VertexComponent::Normal, VertexComponent::Texture0>;

		if (!mesh->HasVertexPositions())
			throw System::Error::SystemException(L"Can't create static mesh from empty vertex list in mesh descriptor");
		if (!mesh->HasFaceTextureCoordinates())
			throw System::Error::SystemException(L"Can't create static mesh from mesh descriptor with empty texture coordinates list");
		if (!mesh->HasVertexNormals())
			throw System::Error::SystemException(L"Can't create static mesh from mesh descriptor with empty normals list");


		std::vector<unsigned> ib;
		if (mesh->IsIndexed()) {
			int index = 0;
			ib.resize(mesh->GetTrianglesCount() * 3);
			for (unsigned i = 0; i < mesh->GetTrianglesCount(); i++) {
				const Math::ivec3* t = mesh->GetTriangle(i);
				ib[3 * i + 0] = index++;
				ib[3 * i + 1] = index++;
				ib[3 * i + 2] = index++;
			}
		}

		std::vector<CurrentVertex> vb(mesh->GetTrianglesCount() * 3);

		std::vector<int> base_index;		/// contains vertex index in the source array
		int index = 0;
		for (unsigned i = 0, max_i = mesh->GetTrianglesCount(); i < max_i; i++)
		{
			const Math::ivec3* f = mesh->GetTriangle(i);
			const Math::vec3* position[3] = { mesh->GetVertexPosition(f->X()), mesh->GetVertexPosition(f->Y()), mesh->GetVertexPosition(f->Z()) };
			const Math::vec2* texture[3] = { mesh->GetFaceTextureCoordinate(0, i, 0), mesh->GetFaceTextureCoordinate(0, i, 1), mesh->GetFaceTextureCoordinate(0, i, 2) };
			const Math::vec3* normal[3] = { mesh->GetVertexNormal(f->X()), mesh->GetVertexNormal(f->Y()), mesh->GetVertexNormal(f->Z()) };

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

		_vb = new VertexArray<CurrentVertex>(vb);
		if (mesh->IsIndexed())
			_ib = new IndexArray<unsigned>(ib);
	}

	void GeometryCooker::CookOneVertexWithBone(const IGeometry* mesh, int index, Math::vec4& bone, Math::vec4& weight)
	{
		Math::vec4 bone_weights = *mesh->GetVertexBoneWeights(index);
		Math::ivec4 bone_indecies = *mesh->GetVertexBonesIndecies(index);		
		//	normalize
		bone_weights.Normalize();						
		weight = bone_weights;
		bone.Set((float)bone_indecies[0], (float)bone_indecies[1], (float)bone_indecies[2], (float)bone_indecies[3]);
	}

	void GeometryCooker::CookPositionNormalTangentBitangentTexture0BoneIDBoneWeight(const IGeometry* mesh,
		Graphics::IVertexArray* _vb,
		Graphics::IIndexArray* _ib)
	{
		using namespace Graphics;
		using CurrentVertex = Vertex<VertexComponent::Position,
			VertexComponent::Normal,
			VertexComponent::Tangent,
			VertexComponent::Bitangent,
			VertexComponent::Texture0,
			VertexComponent::BoneID,
			VertexComponent::BoneWeight>;

		if (!mesh)
			throw System::Error::SystemException(L"Can't created skinned mesh from NULL mesh descriptor");
		if (!mesh->HasVertexPositions())
			throw System::Error::SystemException(L"Can't create skinned mesh from empty vertex list in mesh descriptor");
		if (!mesh->HasFaceTextureCoordinates())
			throw System::Error::SystemException(L"Can't create skinned mesh from mesh descriptor with empty texture coordinates list");
		if (!mesh->HasVertexNormals())
			throw System::Error::SystemException(L"Can't create skinned mesh from mesh descriptor with empty normals list");
		if (!mesh->HasVertexBoneWeights())
			throw System::Error::SystemException(L"Can't create skinned mesh from mesh descriptor with empty bones weights list");

		std::vector<unsigned> ib;
		if (mesh->IsIndexed()) {
			int index = 0;
			ib.resize(mesh->GetTrianglesCount() * 3);
			for (unsigned i = 0; i < mesh->GetTrianglesCount(); i++) {
				const Math::ivec3* t = mesh->GetTriangle(i);
				ib[3 * i + 0] = index++;
				ib[3 * i + 1] = index++;
				ib[3 * i + 2] = index++;
			}
		}

		std::vector<CurrentVertex> vb(mesh->GetTrianglesCount() * 3);

		std::vector<int> base_index;		/// contains vertex index in the source array
		int index = 0;
		for (unsigned i = 0, max_i = mesh->GetTrianglesCount(); i < max_i; i++)
		{
			const Math::ivec3* f = mesh->GetTriangle(i);
			const Math::vec3* position[3] = { mesh->GetVertexPosition(f->X()), mesh->GetVertexPosition(f->Y()), mesh->GetVertexPosition(f->Z()) };
			const Math::vec2* texture[3] = { mesh->GetFaceTextureCoordinate(0, i, 0), mesh->GetFaceTextureCoordinate(0, i, 1), mesh->GetFaceTextureCoordinate(0, i, 2) };
			const Math::vec3* normal[3] = { mesh->GetVertexNormal(f->X()), mesh->GetVertexNormal(f->Y()), mesh->GetVertexNormal(f->Z()) };

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

				CookOneVertexWithBone(mesh, (*f)[j], vb[index].m_bone_id, vb[index].m_bone_weight);

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

			Math::Matrix<float> m(3, 3);
			m.At(0, 0) = tang[0]; m.At(0, 1) = tang[1]; m.At(0, 2) = tang[2];
			m.At(1, 0) = btan[0]; m.At(1, 1) = btan[1]; m.At(1, 2) = btan[2];
			m.At(2, 0) = norm[0]; m.At(2, 1) = norm[1]; m.At(2, 2) = norm[2];
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

		_vb = new VertexArray<CurrentVertex>(vb);
		if (mesh->IsIndexed())
			_ib = new IndexArray<unsigned>(ib);

	}

	void GeometryCooker::CookPositionNormalBonesWeights(IGeometry* mesh, 
		Graphics::IVertexArray*& _vb, 
		Graphics::IIndexArray*& _ib)
	{
		using namespace Graphics;
		using CurrentVertex = Vertex<VertexComponent::Position,
			VertexComponent::Normal,
			VertexComponent::BoneID,
			VertexComponent::BoneWeight>;

		if (!mesh)
			throw System::Error::SystemException(L"Can't created skinned mesh from NULL mesh descriptor");
		if (!mesh->HasVertexPositions())
			throw System::Error::SystemException(L"Can't create skinned mesh from empty vertex list in mesh descriptor");
		if (!mesh->HasVertexNormals())
			throw System::Error::SystemException(L"Can't create skinned mesh from mesh descriptor with empty normals list");
		if (!mesh->HasVertexBoneWeights())
			throw System::Error::SystemException(L"Can't create skinned mesh from mesh descriptor with empty bones weights list");

		std::vector<unsigned> ib;
		if (mesh->IsIndexed()) {
			int index = 0;
			ib.resize(mesh->GetTrianglesCount() * 3);
			for (unsigned i = 0; i < mesh->GetTrianglesCount(); i++) {
				const Math::ivec3* t = mesh->GetTriangle(i);
				ib[3 * i + 0] = index++;
				ib[3 * i + 1] = index++;
				ib[3 * i + 2] = index++;
			}
		}

		std::vector<CurrentVertex> vb(mesh->GetTrianglesCount() * 3);

		std::vector<int> base_index;		/// contains vertex index in the source array
		int index = 0;
		for (unsigned i = 0, max_i = mesh->GetTrianglesCount(); i < max_i; i++)
		{
			const Math::ivec3* f = mesh->GetTriangle(i);
			const Math::vec3* position[3] = { mesh->GetVertexPosition(f->X()), mesh->GetVertexPosition(f->Y()), mesh->GetVertexPosition(f->Z()) };
			const Math::vec3* normal[3] = { mesh->GetVertexNormal(f->X()), mesh->GetVertexNormal(f->Y()), mesh->GetVertexNormal(f->Z()) };

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

				CookOneVertexWithBone(mesh, (*f)[j], vb[index].m_bone_id, vb[index].m_bone_weight);

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

		_vb = new VertexArray<CurrentVertex>(vb);
		if (mesh->IsIndexed())
			_ib = new IndexArray<unsigned>(ib);

	}

	PUNK_REGISTER_CREATOR(IID_IGeometryCooker, (System::CreateInstance<GeometryCooker, IGeometryCooker>));
}
PUNK_ENGINE_END
