#ifndef _H_ICOMPONENT_POSITION
#define _H_ICOMPONENT_POSITION

#include <config.h>
#include <math/vec3.h>
#include <cstdint>

PUNK_ENGINE_BEGIN
namespace Attributes {
	class IPositionComponent {
	public:
		virtual const Math::vec3* GetVertexPosition(std::uint32_t index) const = 0;
		virtual void SetVertexPosition(std::uint32_t index, const Math::vec3& value) = 0;
		virtual void SetVertexPositions(const Math::vec3v& value) = 0;
		virtual bool HasVertexPositions() const = 0;
	};
}
PUNK_ENGINE_END

#endif	//	_H_ICOMPONENT_POSITION