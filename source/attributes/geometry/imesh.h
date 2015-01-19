#ifndef _H_IMESH
#define _H_IMESH

#include <config.h>
#include <system/factory/interface.h>
#include <attributes/data_flow/isource.h>
#include "ivertices.h"
#include "ipolylist.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	DECLARE_PUNK_GUID(IID_IMesh, "31707674-6141-4A9D-9B22-7FDC9CA47E01");
	DECLARE_PUNK_GUID(CLSID_Mesh, "D465C252-D9AC-4722-83F8-62963A21F73D");

	class IMesh : public Core::IObject {
	public:
		virtual void AddSource(ISourcePtr value) = 0;
		virtual std::uint32_t GetSourcesCount() const = 0;
		virtual ISourcePtr GetSource(std::uint32_t value) = 0;

		virtual void SetVertices(IVerticesPtr value) = 0;
		virtual IVerticesPtr GetVerices() const = 0;

		virtual void AddPolylist(IPolyListPtr value) = 0;
		virtual std::uint32_t GetPolylistsCount() = 0;
		virtual IPolyListPtr GetPolylist(std::uint32_t value) = 0;
	};

	using IMeshPtr = Core::Pointer < IMesh > ;

	inline IMeshPtr NewMesh() {
		return System::CreateInstancePtr<IMesh>(CLSID_Mesh, IID_IMesh);
	}
}
PUNK_ENGINE_END

#endif	//	_H_IMESH