#ifndef _H_ICOMPONENT_TEXTURE
#define _H_ICOMPONENT_TEXTURE

#include <config.h>
#include <cstdint>
#include <math/vec4.h>

PUNK_ENGINE_BEGIN
namespace Attributes {
	class ITextureComponent {
	public:
		virtual std::uint32_t GetVertexTextureCoordinatesSetCount() const = 0;
		virtual std::uint32_t GetVertexTextureCoordinatesCount(std::uint32_t set_index) const = 0;
		virtual const Math::vec4* GetVertexTextureCoordinate(std::uint32_t set_index, std::uint32_t vertex_index) const = 0;
		virtual void SetVertexTextureCoordinatesSetCount(std::uint32_t value) = 0;
		virtual void SetVertexTextureCoordinate(std::uint32_t set_index, std::uint32_t vertex_index, const Math::vec4& value) = 0;
		virtual void SetVertexTextureCoordinates(std::uint32_t set_index, const Math::vec4v& value) = 0;
		virtual bool HasVertexTextureCoordinates() const = 0;
		virtual bool HasVertexTextureCoordinateSet(std::uint32_t set_index) const = 0;
	};
}
PUNK_ENGINE_END

#endif	//	_H_ICOMPONENT_NORMAL