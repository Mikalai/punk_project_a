#include <vector>
#include "convex_shape_mesh.h"
#include "vec3.h"
#include "bounding_box.h"
#include "bounding_sphere.h"


namespace Punk {
    namespace Engine {
        namespace Math {

            namespace __private {
                struct ConvexShapeMeshImpl {
                    typedef std::vector<Math::vec3> PointsCollection;
                    typedef std::vector<Math::ivec3> FacesCollection;
                    typedef std::vector<Math::vec3> NormalsCollection;
                    Math::BoundingBox m_bbox;
                    Math::BoundingSphere m_bsphere;

                    PointsCollection m_points;
                    FacesCollection m_faces;
                    NormalsCollection m_normals;

                    void UpdateBoundingVolumes() {
                        m_bbox.Create(&m_points[0], m_points.size());
                        m_bsphere.Create(&m_points[0], m_points.size());
                    }
                };
            }

            ConvexShapeMesh::ConvexShapeMesh()
                : impl(new __private::ConvexShapeMeshImpl) {}

            ConvexShapeMesh::ConvexShapeMesh(const ConvexShapeMesh &value)
                : impl(new __private::ConvexShapeMeshImpl(*value.impl)) {}

            ConvexShapeMesh& ConvexShapeMesh::operator = (const ConvexShapeMesh& value) {
                ConvexShapeMesh temp(value);
                std::swap(impl, temp.impl);
                return *this;
            }

            ConvexShapeMesh::~ConvexShapeMesh() {
                delete impl;
                impl = nullptr;
            }

            void ConvexShapeMesh::SetPoints(const vec3* points, std::size_t count) {
                impl->m_points.resize(count);
                for (auto i = 0u; i < count; ++i) {
                    impl->m_points[i] = points[i];
                }
                impl->UpdateBoundingVolumes();
            }

            void ConvexShapeMesh::SetFaces(const ivec3 *faces, std::size_t count) {
                impl->m_faces.resize(count);
                for (auto i = 0u; i < count; ++i) {
                    impl->m_faces[i] = faces[i];
                }
            }

            void ConvexShapeMesh::SetNormals(const vec3 *normals, std::size_t count) {
                impl->m_normals.resize(count);
                for (auto i = 0u; i < count; ++i) {
                    impl->m_normals[i] = normals[i];
                }
            }

            const vec3& ConvexShapeMesh::GetPoint(std::size_t index) const {
                return impl->m_points[index];
            }

            const ivec3& ConvexShapeMesh::GetFace(std::size_t index) const {
                return impl->m_faces[index];
            }

            const vec3& ConvexShapeMesh::GetNormal(std::size_t index) const {
                return impl->m_normals[index];
            }

            void ConvexShapeMesh::UpdateBoundingVolumes() {
                impl->UpdateBoundingVolumes();
            }

            const BoundingBox& ConvexShapeMesh::GetBoundingBox() const {
                return impl->m_bbox;
            }

            const BoundingSphere& ConvexShapeMesh::GetBoundingSphere() const {
                return impl->m_bsphere;
            }

            std::size_t ConvexShapeMesh::GetFaceCount() const {
                return impl->m_faces.size();
            }

            std::size_t ConvexShapeMesh::GetPointsCount() const {
                return impl->m_points.size();
            }

            std::size_t ConvexShapeMesh::GetNormalsCount() const {
                return impl->m_normals.size();
            }

            //    void SaveBoundingBox(System::Buffer* buffer, const ConvexShapeMesh& value)
            //    {
            //        if (value.m_points.empty() || value.m_faces.empty() || value.m_normals.empty())
            //            throw System::PunkException("Unable to save convex shape");

            //        int size = (int)value.m_points.size();
            //        buffer->WriteSigned32(size);
            //        for (auto& p : value.m_points)
            //            SaveVector3f(buffer, p);

            //        size = (int)value.m_faces.size();
            //        buffer->WriteSigned32(size);
            //        for (auto& p : value.m_faces)
            //            SaveVector3i(buffer, p);

            //        size = (int)value.m_normals.size();
            //        buffer->WriteSigned32(size);
            //        for (auto& p : value.m_normals)
            //            SaveVector3f(buffer, p);
            //    }

            //    void LoadBoundingBox(System::Buffer* buffer, ConvexShapeMesh& value)
            //    {
            //        int size = buffer->ReadSigned32();
            //        value.m_points.resize(size);
            //        for (auto& p : value.m_points)
            //            LoadVector3f(buffer, p);

            //        size = buffer->ReadSigned32();
            //        value.m_faces.resize(size);
            //        for (auto& p : value.m_faces)
            //            SaveVector3i(buffer, p);

            //        size = buffer->ReadSigned32();
            //        value.m_normals.resize(size);
            //        for (auto& p : value.m_normals)
            //            LoadVector3f(buffer, p);

            //    }
        }
    }
}
