#ifndef _H_IGEOMETRY
#define _H_IGEOMETRY

#include <config.h>
#include <memory>
#include <cstdint>
#include <vector>
#include <core/iobject.h>
#include <math/forward.h>
#include "igeometry_element.h"
#include "imesh.h"

PUNK_ENGINE_BEGIN
namespace Graphics {
	class IVertexArray;
	class IIndexArray;
}

namespace Attributes {

	DECLARE_PUNK_GUID(IID_IGeometry, "3B04856F-622F-4AAD-984D-0A0FA5C34B27");
	DECLARE_PUNK_GUID(CLSID_Geometry3D, "929E04D3-D2B3-456E-9876-5279EE80AA1C");

	DECLARE_PUNK_GUID(IID_IGeometry2, "EF2DED37-6D47-45D7-94B0-41A1B9A88794");
	DECLARE_PUNK_GUID(CLSID_Geometry2, "8D9D6C99-DEB0-431D-8956-F923CF016D84");

	class IGeometry
		: public Core::IObject
	{
	public:
		virtual bool IsIndexed() const = 0;
		virtual bool Validate() = 0;
		virtual std::uint32_t GetVertexCount() = 0;
		virtual void SetName(const Core::String& name) = 0;
		virtual const Core::String& GetName() const = 0;
	};

	class IGeometry2 : public Core::IObject {
	public:
		virtual void SetId(const Core::String& value) = 0;
		virtual const Core::String GetId() const = 0;
		virtual void SetName(const Core::String& value) = 0;
		virtual const Core::String GetName() const = 0;
		virtual void SetGeometryElement(IGeometryElementPtr value) = 0;
		virtual IGeometryElementPtr GetGeometryElement() = 0;
	};

	using IGeometry2Ptr = Core::Pointer < IGeometry2 > ;

	class GeometryAccessor {
	public:
		GeometryAccessor(IGeometry2Ptr value)
			: m_value{ value }
		{}

		IMeshPtr AsMesh() {
			return Core::QueryInterfacePtr<IMesh>(m_value->GetGeometryElement(), IID_IMesh);
		}

		void SetMesh(IMeshPtr value) {
			m_value->SetGeometryElement(Core::QueryInterfacePtr<IGeometryElement>(value, IID_IGeometryElement));
		}

	private:
		IGeometry2Ptr m_value;
	};

	inline IGeometry2Ptr NewGeometry2() {
		return System::CreateInstancePtr<IMesh>(CLSID_Geometry2, IID_IGeometry2);
	}
}
PUNK_ENGINE_END

#endif	//	_H_IGEOMETRY