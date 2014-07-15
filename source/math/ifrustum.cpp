#include <system/factory/module.h>
#include <core/iserializable.h>
#include <string/module.h>
#include "mat4.h"
#include "vec2.h"
#include "line3d.h"
#include "plane.h"
#include "aabb.h"
#include "clip_space.h"
#include "frustum_plane.h"
#include "frustum_points.h"
#include "ifrustum.h"
#include "relations.h"
#include "perspective_decoder.h"
#include "frustum_plane.h"
#include "frustum_points.h"
#include "trigonometry.h"
#include "matrix_helper.h"
#include "frustum_core.h"

namespace Punk {
    namespace Engine {
        namespace Math {
			
			class PUNK_ENGINE_LOCAL Frustum : public IFrustum, Core::ISerializable {
			public:
				Frustum() {}
				virtual ~Frustum() {}

				//	IObject
				void QueryInterface(const Core::Guid& type, void** object) override {
					if (!object)
						return;

					*object = nullptr;
					
					if (type == Core::IID_IObject) {
						*object = (IFrustum*)this;
					}
					else if (type == IID_IFrustum) {
						*object = (IFrustum*)this;
					}
					else if (type == Core::IID_ISerializable) {
						*object = (Core::ISerializable*)this;
					}
					AddRef();
				}

				std::uint32_t AddRef() override {
					return m_ref_count.fetch_add(1);
				}

				std::uint32_t Release() override {
					auto v = m_ref_count.fetch_sub(1) - 1;
					if (!v)
						delete this;
					return v;
				}

				//	IFrustum
				const ClipSpace GetClipSpaceFromPoint(const Math::vec3& p) const override {
					return FrustumBuildClipSpaceFromPoint(m_core, p);
				}

				const ClipSpace GetClipSpace() const override {
					return FrustumToClipSpace(m_core);
				}

				void SetPerspectiveProjectionMatrix(const Math::mat4& value) override {
					m_core = FrustumCreateFromProjectionMatrix(value);
				}

				const Math::mat4 GetPerspectiveProjectionMatrix() const override {
					return FrustumCreatePerspectiveProjectionMatrix(m_core);
				}

				const vec2 GetZRange(const Math::mat4& view) const override {
					return FrustumFindZRange(m_core, view);
				}

				void Transform(const vec3 &center, const vec3 &view_dir, const vec3 &_up) override {
					FrustumTransform(m_core, center, view_dir, _up);
				}

				void SetNearDistance(float znear) override {
					m_core.neard = znear;
				}

				void SetFarDistance(float zfar) override {
					m_core.fard = zfar;
				}

				void SetFov(float fov) {
					m_core.fov = fov;
				}

				void SetAspectRatio(float width, float height) override {
					m_core.ratio = width / height;
				}

				void SetAspectRatio(float aspect) override {
					m_core.ratio = aspect;
				}

				float GetFov() const override {
					return m_core.fov;
				}

				float GetFarDistance() const override {
					return m_core.fard;
				}

				float GetAspectRation() const override {
					return m_core.ratio;
				}

				float GetNearDistance() const override {
					return m_core.neard;
				}

				//	ISerializable
				void Serialize(Core::Buffer& buffer) {
					buffer.WritePod(CLSID_Frustum);
					buffer.WritePod(m_core);

				}
				void Deserialize(Core::Buffer& buffer) {
					buffer.ReadPod(m_core);
				}

			private:
				std::atomic<std::uint32_t> m_ref_count{ 0 };
				FrustumCore m_core;
			};


			PUNK_REGISTER_CREATOR(CLSID_Frustum, (System::CreateInstance < Frustum, IFrustum>));

        }
    }
}
