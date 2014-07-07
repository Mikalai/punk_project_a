#ifndef _H_ITEXTURE_FACE_COMPONENT
#define _H_ITEXTURE_FACE_COMPONENT

#include <config.h>
#include <math/vec2.h>

PUNK_ENGINE_BEGIN
namespace Attributes {

	DECLARE_PUNK_GUID(IID_IFaceTextureStream, "3BF6C838-10CD-4D2E-9D89-6B2058AA2353");

	class IFaceTextureStream {
	public:
		virtual std::uint32_t GetFaceTextureCoordinatesSlotsCount() const = 0;
		virtual void SetFaceTextureCoordinates(const std::vector<std::vector<std::array<Math::vec2, 3>>>& value) = 0;
		virtual void SetFaceTextureCoordinates(std::uint32_t slot, const std::vector<std::array<Math::vec2, 3>>& value) = 0;
		virtual void SetFaceTextureCoordinate(std::uint32_t  slot, std::uint32_t triangle_index, std::uint32_t vertex_index, const Math::vec2& t) = 0;
		virtual const Math::vec2* GetFaceTextureCoordinate(std::uint32_t  slot, std::uint32_t triangle_index, int vertex_index) const = 0;
		virtual bool HasFaceTextureCoordinates() const = 0;
	};
}
PUNK_ENGINE_END

#endif	//	_H_ITEXTURE_FACE_COMPONENT
