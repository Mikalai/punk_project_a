#include <config.h>
#include <system/factory/module.h>
#include <core/iobject.h>
#include <core/iserializable.h>
#include <string/module.h>
#include <math/mat4.h>
#include <math/line3d.h>
#include <math/ifrustum.h>
#include <math/constants.h>
#include <math/rect.h>
#include <math/helper.h>
#include <math/line3d.h>
#include <math/matrix_helper.h>
#include <math/clip_space.h>
#include <system/window/module.h>
#include "iperspective_camera.h"

PUNK_ENGINE_BEGIN
namespace Attributes
{
	struct PUNK_ENGINE_API CameraOptions
	{
		float m_near;
		float m_far;
		float m_fov;
		float m_aspect;

		CameraOptions()
			: m_near(1.0f)
			, m_far(1000.0f)
			, m_fov(Math::PI / 4.0f)
			, m_aspect(1.6f)
		{}
	};

	class PUNK_ENGINE_LOCAL Camera :
		public IPerspectiveCamera,
		public Core::ISerializable
	{
	public:
		Camera()
			: m_frustum{ System::CreateInstancePtr<Math::IFrustum>(Math::CLSID_Frustum, Math::IID_IFrustum) }
		{}

		virtual ~Camera() {}

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override {
			if (!object)
				return;

			*object = nullptr;

			if (type == IID_ICamera) {
				*object = (ICamera*)(IPerspectiveCamera*)this;
				AddRef();
			}
			else if (type == IID_IPerspectiveCamera) {
				*object = (IPerspectiveCamera*)this;
				AddRef();
			}
			else if (type == Core::IID_IObject) {
				*object = (Core::IObject*)(IPerspectiveCamera*)this;
				AddRef();
			}				
			else if (type == Core::IID_ISerializable) {
				*object = (Core::ISerializable*)this;
				AddRef();
			}
		}

		std::uint32_t AddRef() override {
			m_ref_count.fetch_add(1);
			return m_ref_count;
		}

		std::uint32_t Release() override {
			auto v = m_ref_count.fetch_sub(1) - 1;
			if (!v)
				delete this;
			return v;
		}


		//	ICamera
		void SetName(const Core::String& value) override {
			m_name = value;
		}

		const Core::String GetName() const override {
			return m_name;
		}

		const Math::mat4 GetProjectionMatrix() const override {
			return m_frustum->GetPerspectiveProjectionMatrix();
		}

		const Math::vec3 GetDirection() const override {
			return m_direction;
		}

		void SetDirection(const Math::vec3& value) override {
			m_direction = value;
		}

		const Math::vec3 GetUpVector() const override {
			return m_up;
		}

		void SetUpVector(const Math::vec3& value) override {
			m_up = value;
		}

		const Math::ClipSpace GetClipSpace() const override {
			return m_frustum->GetClipSpace();
		}

		void BindToWindow(System::IWindow* window) override {
			m_window = window;
			m_frustum->SetAspectRatio((float)m_window->GetWidth(), (float)m_window->GetHeight());
		}

		System::IWindow* GetWindow() const override {
			return m_window;
		}

		//	IPerspectiveCamera
		void SetFieldOfView(float angle) override {
			m_frustum->SetFov(angle);
		}

		void SetNearClipPlane(float value) override {
			m_frustum->SetNearDistance(value);
		}

		void SetFarClipPlane(float value) override {
			m_frustum->SetFarDistance(value);
		}

		const Core::Pointer<Math::IFrustum> GetFrustum() const override {
			return m_frustum;
		}

		float GetFieldOfView() const override {
			return m_frustum->GetFov();
		}

		float GetNearClipPlane() const override {
			return m_frustum->GetNearDistance();
		}

		float GetFarClipPlane() const override {
			return m_frustum->GetFarDistance();
		}

		const Math::vec2 GetZRange(const Math::mat4& view) const override {
			return m_frustum->GetZRange(view);
		}

		//	ISerializable
		void Serialize(Core::Buffer& buffer) override {
			//	IObject
			buffer.WritePod(CLSID_PerspectiveCamera);

			//	ICamera
			buffer.WriteString(m_name);
			buffer.WritePod(m_direction);
			buffer.WritePod(m_up);

			//	IPerspectiveCamera
			auto serializable = Core::QueryInterfacePtr<Core::ISerializable>(m_frustum, Core::IID_ISerializable);
			auto flag = serializable.get() != nullptr;
			buffer.WriteBoolean(flag);
			if (flag) {
				serializable->Serialize(buffer);
			}
		}

		void Deserialize(Core::Buffer& buffer) override {
			//	ICamera
			buffer.WriteString(m_name);
			buffer.WritePod(m_direction);
			buffer.WritePod(m_up);

			//	IPerspectiveCamera			
			auto flag = buffer.ReadBoolean();
			if (flag) {
				Core::Guid clsid;
				buffer.ReadPod(clsid);
				auto serializable = System::CreateInstancePtr<Core::ISerializable>(clsid, Core::IID_ISerializable);
				if (serializable)
					serializable->Deserialize(buffer);
				m_frustum = Core::QueryInterfacePtr<Math::IFrustum>(serializable, Math::IID_IFrustum);
			}
		}

	private:
		//	IObject
		std::atomic<std::uint32_t> m_ref_count{ 0 };

		//	ICamera
		Core::String m_name;
		Math::vec3 m_direction{ 0, 0, -1 };
		Math::vec3 m_up{ 0, 1, 0 };
		System::IWindow* m_window{ nullptr };

		//	IPerspectiveCamera
		Core::Pointer<Math::IFrustum> m_frustum{ nullptr, Core::DestroyObject };
	};
	
	PUNK_REGISTER_CREATOR(CLSID_PerspectiveCamera, (System::CreateInstance<Camera, IPerspectiveCamera>));

	/*const Math::ClipSpace Camera::ToClipSpace() const
	{
	return m_frustum->GetClipSpace();
	}*/

	/*void Camera::SetPosition(const Math::vec3& pos)
	{
	m_position = pos;
	UpdateInternals();
	}

	void Camera::SetPosition(float x, float y, float z)
	{
	m_position.Set(x, y, z);
	UpdateInternals();;
	}

	void Camera::UpdateInternals()
	{
	Math::YawPitchRollToUpDirection(m_yrp[0], m_yrp[1], m_yrp[2], m_up, m_direction);
	m_right = m_direction.Cross(m_up);
	m_view_matrix = Math::CreateTargetCameraMatrix(m_position, m_position + m_direction, m_up);
	}
	*/
	//	Camera* Camera::CreateFromFile(const Core::String& path)
	//	{
	//		std::ifstream stream(path.ToStdString().c_str(), std::ios::binary);
	//		if (!stream.is_open())
	//			throw System::PunkInvalidArgumentException(L"Can't open file " + path);
	//		return CreateFromStream(stream);
	//	}

	//const Math::Line3D Camera::GetWorldRay(float x, float y)
	//{
	//	//	aspect ratio as used in opengl
	//	float aspect = m_viewport.GetWidth() / m_viewport.GetHeight();
	//	//	translate x and y to projection plane
	//	float proj_x = aspect*(-1.0f + 2.0f * (float)x / m_viewport.GetWidth());
	//	float proj_y = -1.0f + 2.0f * (float)(m_viewport.GetHeight() - y) / m_viewport.GetHeight();


	//	//	find mouse point in the view space
	//       Math::vec3 mouse_in_view(proj_x, proj_y, -1.0f / tan(m_frustum->fov/2.0f));
	//	//	translate mouse point to the world space
	//	Math::vec4 mouse_in_world_4 = (m_view_matrix.Inversed() * Math::vec4(mouse_in_view, 1.0f));
	//	mouse_in_world_4 /= mouse_in_world_4[3];
	//	Math::vec3 mouse_in_world = mouse_in_world_4.XYZ();
	//	//m_mouse_world = mouse_in_world;
	//	//	translate view center to the world
	//	Math::vec3 view_pos((m_view_matrix.Inversed() * Math::vec4(0,0,0, 1.0f)).XYZ());

	//	//	create a ray to intersect everything with it
	//	Math::Line3D ray;
	//	ray.SetOriginDestination(view_pos, mouse_in_world);
	//	return ray;
	//}    

	class Camera2 : public ICamera2 {
	public:
		// IObject		
		void QueryInterface(const Core::Guid& type, void** object) override {
			if (!object)
				return;
			*object = nullptr;

			if (type == Core::IID_IObject) {
				*object = (IOptics*)this;
				AddRef();
			}
			else if (type == IID_IOptics) {
				*object = (IOptics*)this;
				AddRef();
			}
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

		//	ICamera2
		void SetId(const Core::String& value) override {
			m_id = value;
		}

		const Core::String GetId() const override {
			return m_id;
		}

		void SetName(const Core::String& value) override {
			m_name = value;
		}

		const Core::String GetName() const override {
			return m_name;
		}

		void SetOptics(IOpticsPtr value) override {
			m_optics = value;
		}

		IOpticsPtr GetOptics() const override {
			return m_optics;
		}
	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		Core::String m_id;
		Core::String m_name;
		IOpticsPtr m_optics;
	};

	PUNK_REGISTER_CREATOR(CLSID_Camera2, (System::CreateInstance<Camera2, ICamera2>));

}
PUNK_ENGINE_END
