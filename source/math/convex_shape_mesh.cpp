//#include <vector>
//#include "convex_shape_mesh.h"
//#include "vec3.h"
//#include "bounding_box.h"
//#include "bounding_sphere.h"


//PUNK_ENGINE_BEGIN
//namespace Math {

//	namespace __private {
//		struct ConvexShapeMeshImpl {

//		};
//	}

//	ConvexShapeMesh::ConvexShapeMesh()
//		: impl(new __private::ConvexShapeMeshImpl) {}

//	ConvexShapeMesh::ConvexShapeMesh(const ConvexShapeMesh &value)
//		: impl(new __private::ConvexShapeMeshImpl(*value.impl)) {}

//	ConvexShapeMesh& ConvexShapeMesh::operator = (const ConvexShapeMesh& value) {
//		ConvexShapeMesh temp(value);
//		std::swap(impl, temp.impl);
//		return *this;
//	}

//	ConvexShapeMesh::~ConvexShapeMesh() {
//		delete impl;
//		impl = nullptr;
//	}



//	//    void SaveBoundingBox(Core::Buffer* buffer, const ConvexShapeMesh& value)
//	//    {
//	//        if (value.m_points.empty() || value.m_faces.empty() || value.m_normals.empty())
//	//            throw System::PunkException("Unable to save convex shape");

//	//        int size = (int)value.m_points.size();
//	//        buffer->WriteSigned32(size);
//	//        for (auto& p : value.m_points)
//	//            SaveVector3f(buffer, p);

//	//        size = (int)value.m_faces.size();
//	//        buffer->WriteSigned32(size);
//	//        for (auto& p : value.m_faces)
//	//            SaveVector3i(buffer, p);

//	//        size = (int)value.m_normals.size();
//	//        buffer->WriteSigned32(size);
//	//        for (auto& p : value.m_normals)
//	//            SaveVector3f(buffer, p);
//	//    }

//	//    void LoadBoundingBox(Core::Buffer* buffer, ConvexShapeMesh& value)
//	//    {
//	//        int size = buffer->ReadSigned32();
//	//        value.m_points.resize(size);
//	//        for (auto& p : value.m_points)
//	//            LoadVector3f(buffer, p);

//	//        size = buffer->ReadSigned32();
//	//        value.m_faces.resize(size);
//	//        for (auto& p : value.m_faces)
//	//            SaveVector3i(buffer, p);

//	//        size = buffer->ReadSigned32();
//	//        value.m_normals.resize(size);
//	//        for (auto& p : value.m_normals)
//	//            LoadVector3f(buffer, p);

//	//    }
//}
//PUNK_ENGINE_END
