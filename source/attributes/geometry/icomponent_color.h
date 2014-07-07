#ifndef _H_ICOMPONENT_COLOR
#define _H_ICOMPONENT_COLOR

#include <config.h>
#include <cstdint>
#include <core/iobject.h>
#include <math/vec4.h>

PUNK_ENGINE_BEGIN
namespace Attributes {

	DECLARE_PUNK_GUID(IID_IVertexColorStream, "D9398BC3-6B91-4883-A591-026BD14617A5");
	
	class IVertexColorStream : public Core::IObject {
	public:
		virtual const Math::vec4* GetVertexColor(std::uint32_t index) const = 0;
		virtual void SetVertexColor(std::uint32_t index, const Math::vec4& value) = 0;
		virtual void SetVertexColors(const Math::vec4v& value) = 0;
		virtual bool HasVertexColors() const = 0;
	};
}
PUNK_ENGINE_END

#endif	//	_H_ICOMPONENT_NORMAL