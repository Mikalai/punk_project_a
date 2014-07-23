#ifndef _H_MATH_BOUNDING_VOLUMES
#define _H_MATH_BOUNDING_VOLUMES

#include <config.h>
#include <core/iobject.h>
#include <math/line3d.h>
#include <math/rect.h>
#include <math/ellipsoid.h>
#include <math/polygon3d.h>
#include <math/bounding_box.h>
#include <math/bounding_sphere.h>
#include <math/mat4.h>
#include <math/ifrustum.h>

PUNK_ENGINE_BEGIN
namespace Math {

	class IIntersectionResult;
	enum class IntersectionHint : std::uint64_t;

	DECLARE_PUNK_GUID(IID_IBoundingVolume, "5E31208A-644C-4BCC-A79D-D43D524AC3EA");
	class IBoundingVolume : public Core::IObject {
	public:

	};

	DECLARE_PUNK_GUID(IID_IBoundingVolume2D, "7C759949-5DE4-4F18-8E23-9203E4631CD7");
	class IBoundingVolume2D : public IBoundingVolume {
	public:
		virtual bool IsPointInside(const Math::vec2& value) = 0;
		virtual bool IsPointInside(const Math::vec2& value, Math::IntersectionHint& hint) = 0;
	};

	DECLARE_PUNK_GUID(IID_IBoundingRectangle, "3F6C41B7-C958-4FB0-8863-C964B517773B");
	class IBoundingRectangle : public IBoundingVolume2D {
	public:
		virtual const Math::Rectangle& GetRectangle() = 0;
	};

	DECLARE_PUNK_GUID(IID_IBoundingEllipse, "FBFCD138-751C-42D8-ACC3-BD7274190675");
	class IBoundingEllipse : public IBoundingVolume2D {
	public:
		//virtual const Math::Ellipse& GetEllipse() = 0;
	};

	DECLARE_PUNK_GUID(IID_IBoundingConvexPolygon, "A1185095-3525-410F-A6E5-3868679DB209");
	class IBoundingConvexPolygon : public IBoundingVolume2D {
	public:
		//virtual const Math::Polygon& GetPolygon() = 0;
	};

	DECLARE_PUNK_GUID(IID_IBoundingVolume3D, "FE54F3F5-C00F-405D-8841-545C67A4962F");
	class IBoundingVolume3D : public IBoundingVolume {
	public:
		virtual bool IsPointInside(const Math::point3d& value) = 0;
		virtual bool IsPointInside(const Math::point3d& value, Math::IntersectionHint& hint) = 0;
		virtual Core::Pointer<IIntersectionResult> CrossLine(const Math::Line3D& line) = 0;
		virtual bool CrossFrustum(const Core::Pointer<Math::IFrustum> frust, const Math::mat4& to_frustum_space) = 0;
	};

	DECLARE_PUNK_GUID(IID_IBoundingBox, "6A7CE36E-F404-424C-82FA-8FB5EBECA9D3");
	class IBoundingBox : public IBoundingVolume3D {
	public:
		virtual const Math::BoundingBox& GetBox() const = 0;
		virtual void SetBox(const Math::BoundingBox& value) = 0;
	};

	DECLARE_PUNK_GUID(IID_IBoundingSphere, "A0AC474E-7B2A-4705-9D3A-C52C078616F6");
	class IBoundingSphere : public IBoundingVolume3D {
	public:
		virtual const Math::BoundingSphere& GetSphere() const = 0;
		virtual void SetSphere(const Math::BoundingSphere& value) = 0;
	};
	
	DECLARE_PUNK_GUID(IID_IBoundingConvexMesh, "706E143C-6AAE-4ADA-9A00-DBD4ECBF20DA");
	class IBoundingConvexMesh : public IBoundingVolume3D {
	public:
	};
}
PUNK_ENGINE_END

#endif