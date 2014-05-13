#ifndef _H_ITEXTURE_FACE_COMPONENT
#define _H_ITEXTURE_FACE_COMPONENT

#include <config.h>
#include <math/vec2.h>

PUNK_ENGINE_BEGIN
namespace Attributes {
	class ITextureFaceComponent {
	public:
		virtual std::uint32_t GetFaceTextureCoordinatesSlotsCount() const = 0;
		virtual void SetFaceTextureCoordinates(std::uint32_t slot, const std::vector<std::array<Math::vec2, 3>>& value) = 0;
		virtual void SetFaceTextureCoordinate(std::uint32_t  slot, std::uint32_t triangle_index, std::uint32_t vertex_index, const Math::vec2& t) = 0;
		virtual const Math::vec2* GetFaceTextureCoordinate(std::uint32_t  slot, std::uint32_t triangle_index, int vertex_index) const = 0;
		virtual bool HasFaceTextureCoordinates() const = 0;
	};
}
PUNK_ENGINE_END

#endif	//	_H_ITEXTURE_FACE_COMPONENT
