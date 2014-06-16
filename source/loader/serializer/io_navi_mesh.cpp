//#include <ai/navi_mesh.h>
//#include "io_vector.h"
//#include "io_matrix.h"
//#include "io_object.h"
//#include "io_string.h"
//#include "io_navi_mesh.h"
//
//PUNK_ENGINE_BEGIN
//namespace IoModule {
//    void SaveNaviMesh(Core::Buffer *buffer, const Core::IObject *o)
//    {
//        SaveObject(buffer, o);
//        const AI::NaviMesh* m = Cast<const AI::NaviMesh*>(o);
//        SaveString(buffer, m->GetName());
//        SaveMatrix4f(buffer, m->GetTranform());
//        unsigned size = m->GetPoints().size();
//        buffer->WriteUnsigned32(size);
//        for (auto& p : m->GetPoints())
//        {
//            SaveVector3f(buffer, p);
//        }
//
//        size = m->GetNormals().size();
//        buffer->WriteUnsigned32(size);
//        for (auto& p : m->GetNormals())
//        {
//            SaveVector3f(buffer, p);
//        }
//
//        size = m->GetFaces().size();
//        buffer->WriteUnsigned32(size);
//        for (auto& p : m->GetFaces())
//        {
//            SaveVector3i(buffer, p);
//        }
//    }
//
//    void LoadNaviMesh(Core::Buffer *buffer, Core::IObject *o) {
//        LoadObject(buffer, o);
//        AI::NaviMesh* m = Cast<AI::NaviMesh*>(o);
//        Core::String str;
//        LoadString(buffer, str);
//        m->SetName(str);
//
//        Math::mat4 matrix;
//        LoadMatrix4f(buffer, matrix);
//        m->SetTransform(matrix);
//
//        unsigned size = buffer->ReadUnsigned32();
//        AI::NaviMesh::Points points(size);
//        for (auto& p : points)
//        {
//            LoadVector3f(buffer, p);
//        }
//        m->SetPoints(points);
//
//        size = buffer->ReadUnsigned32();
//        AI::NaviMesh::Normals normals(size);
//        for (auto& p : normals)
//        {
//            LoadVector3f(buffer, p);
//        }
//        m->SetNormals(normals);
//
//        size = buffer->ReadUnsigned32();
//        AI::NaviMesh::Faces faces(size);
//        for (auto& p : faces)
//        {
//            LoadVector3i(buffer, p);
//        }
//        m->SetFaces(faces);
//    }
//}
//PUNK_ENGINE_END
