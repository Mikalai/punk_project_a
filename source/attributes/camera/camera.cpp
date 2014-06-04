#include <config.h>
#include <core/ifactory.h>
#include <core/iobject.h>
#include <math/mat4.h>
#include <math/line3d.h>
#include <math/frustum.h>
#include <math/constants.h>
#include <math/rect.h>
#include <math/helper.h>
#include <math/frustum.h>
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

	class PUNK_ENGINE_LOCAL Camera : public IPerspectiveCamera
	{
	public:
		Camera();
		virtual ~Camera();

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override;
		std::uint32_t AddRef() override;
		std::uint32_t Release() override;

		//	ICamera
		void SetName(const Core::String& value) override;
		const Core::String GetName() const override;
		const Math::mat4 GetProjectionMatrix() const override;
		const Math::vec3 GetDirection() const override;
		void SetDirection(const Math::vec3& value) override;
		const Math::vec3 GetUpVector() const override;
		void SetUpVector(const Math::vec3& value) override;
		const Math::ClipSpace GetClipSpace() const override;
		void BindToWindow(System::IWindow* window) override;
		System::IWindow* GetWindow() const override;
		const Math::vec2 GetZRange(const Math::mat4& view) const override;

		//	IPerspectiveCamera
		void SetFieldOfView(float angle) override;
		void SetNearClipPlane(float value) override;
		void SetFarClipPlane(float value) override;
		float GetFieldOfView() const override;
		float GetNearClipPlane() const override;
		float GetFarClipPlane() const override;
		const Math::Frustum GetFrustum() const override;

	private:
		//	IObject
		std::atomic<std::uint32_t> m_ref_count{ 1 };

		//	ICamera
		Core::String m_name;
		Math::vec3 m_direction{ 0, 0, -1 };
		Math::vec3 m_up{ 0, 1, 0 };
		System::IWindow* m_window{ nullptr };

		//	IPerspectiveCamera
		Math::Frustum m_frustum;
	};

	Camera::Camera() {}

	Camera::~Camera() {}

	void Camera::QueryInterface(const Core::Guid& type, void** object) {
		if (!object)
			return;

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
		else
			*object = nullptr;
	}

	std::uint32_t Camera::AddRef() {
		m_ref_count.fetch_add(1);
		return m_ref_count;
	}

	std::uint32_t Camera::Release() {
		auto v = m_ref_count.fetch_sub(1) - 1;
		if (!v)
			delete this;
		return v;
	}

	//	ICamera
	void Camera::SetName(const Core::String& value) {
		m_name = value;
	}

	const Core::String Camera::GetName() const {
		return m_name;
	}

	const Math::mat4 Camera::GetProjectionMatrix() const {
		return m_frustum.GetPerspectiveProjectionMatrix();
	}

	const Math::vec3 Camera::GetDirection() const {
		return m_direction;
	}

	void Camera::SetDirection(const Math::vec3& value) {
		m_direction = value;
	}

	const Math::vec3 Camera::GetUpVector() const {
		return m_up;
	}

	void Camera::SetUpVector(const Math::vec3& value) {
		m_up = value;
	}

	const Math::ClipSpace Camera::GetClipSpace() const {
		return m_frustum.GetClipSpace();
	}

	void Camera::BindToWindow(System::IWindow* window) {
		m_window = window;
		m_frustum.SetAspectRatio(m_window->GetWidth(), m_window->GetHeight());
	}

	System::IWindow* Camera::GetWindow() const {
		return m_window;
	}

	//	IPerspectiveCamera
	void Camera::SetFieldOfView(float angle) {
		m_frustum.SetFov(angle);
	}

	void Camera::SetNearClipPlane(float value) {
		m_frustum.SetNearDistance(value);
	}

	void Camera::SetFarClipPlane(float value) {
		m_frustum.SetFarDistance(value);
	}

	const Math::Frustum Camera::GetFrustum() const {
		return m_frustum;
	}

	float Camera::GetFieldOfView() const {
		return m_frustum.GetFov();
	}

	float Camera::GetNearClipPlane() const {
		return m_frustum.GetNearDistance();
	}

	float Camera::GetFarClipPlane() const {
		return m_frustum.GetFarDistance();
	}

	const Math::vec2 Camera::GetZRange(const Math::mat4& view) const {
		return m_frustum.GetZRange(view);
	}

	PUNK_REGISTER_CREATOR(IID_IPerspectiveCamera, (Core::CreateInstance<Camera, IPerspectiveCamera>));

	/*const Math::ClipSpace Camera::ToClipSpace() const
	{
	return m_frustum.GetClipSpace();
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
	//       Math::vec3 mouse_in_view(proj_x, proj_y, -1.0f / tan(m_frustum.fov/2.0f));
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
}
PUNK_ENGINE_END
