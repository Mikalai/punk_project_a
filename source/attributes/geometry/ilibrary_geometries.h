#ifndef _H_ILIRARY_GEOMETRIES
#define _H_ILIRARY_GEOMETRIES

#include <config.h>
#include <system/factory/interface.h>
#include "igeometry.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	DECLARE_PUNK_GUID(IID_ILibraryGeometries, "37B022F9-C16E-400C-A5D0-ACBA61F61E31");
	DECLARE_PUNK_GUID(CLSID_LibraryGeometries, "7C705679-3067-4966-890E-CB1F46C3CFE9");

	class ILibraryGeometries : public Core::IObject {
	public:
		virtual void SetName(const Core::String& value) = 0;
		virtual const Core::String GetName() const = 0;
		virtual void SetId(const Core::String& value) = 0;
		virtual const Core::String GetId() const = 0;
		virtual void AddGeometry(IGeometry2Ptr value) = 0;
		virtual std::uint32_t GetGeometriesCount() const = 0;
		virtual IGeometry2Ptr GetGeometry(std::uint32_t index) = 0;
	};

	using ILibraryGeometriesPtr = Core::Pointer < ILibraryGeometries > ;

	inline ILibraryGeometriesPtr NewLibraryGeometry() {
		return System::CreateInstancePtr<ILibraryGeometries>(CLSID_LibraryGeometries, IID_ILibraryGeometries);
	}
}
PUNK_ENGINE_END

#endif	//	_H_ILIRARY_GEOMETRIES