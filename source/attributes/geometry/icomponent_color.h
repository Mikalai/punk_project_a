#ifndef _H_ICOMPONENT_COLOR
#define _H_ICOMPONENT_COLOR

#include <config.h>
#include <cstdint>
#include <math/vec4.h>

PUNK_ENGINE_BEGIN
namespace Attributes {
	class IColorComponent {
	public:
		virtual const Math::vec4* GetVertexColor(std::uint32_t index) const = 0;
		virtual void SetVertexColor(std::uint32_t index, const Math::vec4& value) = 0;
		virtual void SetVertexColors(const Math::vec4v& value) = 0;
		virtual bool HasVertexColors() const = 0;
	};
}
PUNK_ENGINE_END

#endif	//	_H_ICOMPONENT_NORMAL