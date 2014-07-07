#ifndef _H_ICOMPONENT_POSITION
#define _H_ICOMPONENT_POSITION

#include <config.h>
#include <math/vec3.h>
#include <cstdint>

PUNK_ENGINE_BEGIN
namespace Attributes {

	DECLARE_PUNK_GUID(IID_IVertexPositionStream, "DA2D0417-B626-4B2A-8D85-C86D7DAA9C83");
	class IVertexPositionStream : public Core::IObject {
	public:
		virtual const Math::vec3* GetVertexPosition(std::uint32_t index) const = 0;
		virtual void SetVertexPosition(std::uint32_t index, const Math::vec3& value) = 0;
		virtual void SetVertexPositions(const Math::vec3v& value) = 0;
		virtual bool HasVertexPositions() const = 0;
	};
}
PUNK_ENGINE_END

#endif	//	_H_ICOMPONENT_POSITION